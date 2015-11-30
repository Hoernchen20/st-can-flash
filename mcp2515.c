/*
 * mcp2515.c
 * 
 * Copyright 2015  Felix Horn
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <string.h>
#include <bcm2835.h>
#include "mcp2515.h"

void mcp2515_init(void) {
    //BCM2835-Lib initialisieren
    bcm2835_init();

    //SPI Interface initalisieren
    bcm2835_spi_begin();
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_32);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);

    //MCP2515 resetten, um ihn in den Konfigurationsmodus zu versetzen
    bcm2835_spi_transfer(RESET);
    delay(100);

    //CNF1..3 konfigurieren
    char buf_1[5] = {WRITE, CNF3, 0x07, 0x9a, 0x01};
    bcm2835_spi_transfern(buf_1, 5);

    //Receive Buffer 0 Control
    char buf_2[3] = {WRITE, RXB0CTRL, (1<<RXM1)|(1<<RXM0)};
    bcm2835_spi_transfern(buf_2, 3);

    //MCP2515 in den Normalen Modus versetzen
    char buf_3[3] = {WRITE, CANCTRL, (1<<CLKEN)/*|(1<<REQOP1)*/};
    bcm2835_spi_transfern(buf_3, 3);
    
    #if MCP2515_Ausgabe
    printf("Initialisierung MCP2515: OK\n");

    //Konfiguration fÃ¼r Ausgabe auslesen
    char buf_10[5] = {READ, CNF3, 0, 0, 0};
    bcm2835_spi_transfern(buf_10, 5);
    char buf_11[3] = {READ, RXB0CTRL, 0};
    bcm2835_spi_transfern(buf_11, 3);
    char buf_12[3] = {READ, CANCTRL, 0};
    bcm2835_spi_transfern(buf_12, 3);

    //Konfiguration auf Bildschirm ausgeben
    printf("MCP2515 Konfiguration \n");
    printf("CNF1: %02x\nCNF2: %02x\nCNF3: %02x\n", buf_10[4], buf_10[3], buf_10[2]);
    printf("RXB0CTRL: %02x\n", buf_11[2]);
    printf("CANCTRL: %02x\n", buf_12[2]);
    #endif
}

//Statusregister des MCP2515 auslesen
uint8_t mcp2515_status(void) {
    char buf[2] = {Read_Status, 0};
    bcm2835_spi_transfern(buf, 2);
    return (uint8_t)buf[1];
}

char txb0ctrl_status(void) {
    char buf[3] = {READ, TXB0CTRL, 0};
    bcm2835_spi_transfern(buf, 3);
    return buf[2];
}

char rx_status(void) {
    char buf[2] = {RX_Status, 0};
    bcm2835_spi_transfern(buf, 2);
    return buf[1];
}

bool mcp2515_read_message (can_message *Msg) {
    char ReceiveData[14] = {0};
    char DeleteInterrupt[4] = {Bit_Modify, CANINTF, 0, 0};
    
    /* check if new message in one of the fifos exist */
    uint8_t Status = mcp2515_status();
    if (Status & (1<<CANINTF_RX0IF)) {
        ReceiveData[0] = Read_RX0;
        DeleteInterrupt[2] = (1<<RX0IF);
    }
    else if (Status & (1<<CANINTF_RX1IF)) {
        ReceiveData[0] = Read_RX1;
        DeleteInterrupt[2] = (1<<RX1IF);
    }
    else {
        return FALSE;
    }
    
    /* read out message */    
    bcm2835_spi_transfern(ReceiveData, sizeof(ReceiveData));
    
    /* delete interrupt flag */
    bcm2835_spi_transfern(DeleteInterrupt, sizeof(DeleteInterrupt));
    
    #if MCP2515_Ausgabe
        unsigned char j;
        printf("Neue Nachricht\n");
        printf("SIDH: %02X  SIDL: %02X  EID8: %02X  EID0: %02X  DLC: %02X  Daten: ",
            ReceiveData[1], ReceiveData[2], ReceiveData[3], ReceiveData[4], ReceiveData[5]);
            
        for(j=1; j<=buf[5]; j++) {
            printf("%02X ", ReceiveData[j+5]);
            }
        printf("\n");
    #endif
    
    /* sort receive data */
    Msg->Id = ReceiveData[1];
    Msg->Id = Msg->Id<<3;
    Msg->Id = (Msg->Id|(ReceiveData[2]>>5));
    Msg->DataLength = (ReceiveData[5]&((1<<DLC3)|(1<<DLC2)|(1<<DLC1)|(1<<DLC0)));
    
    for(uint8_t i=0; i < Msg->DataLength; i++) {
        Msg->Data[i] = ReceiveData[i+6];
        }
    
    /* check data length */
    if(Msg->DataLength > 8) {
        return FALSE;
    }

    return TRUE;
}
    
void tx_buffer_0_write(void) {
    //Daten laden
    char buf_3[10] = {0b01000000, 0b11111101, 0b11001011, 0b11111111, 0b11111101, 0b00000100, 170, 35, 20, 5};
    bcm2835_spi_transfern(buf_3, 10);
    
    //Übertragung starten
    bcm2835_spi_transfer(0b10000001);
}

char mcp2515_send_message (can_message *message) {
    /*
     * Freien Puffer auswählen */
    char status = 0;
    char buffer_adress = 0;
    char rts_txx = 0;

    while (buffer_adress == 0) {
        status = mcp2515_status();
        if ((~status) & (1<<TXB0CNTRL_TXREQ)) {
            buffer_adress = Load_TX0;
            rts_txx = RTS_TX0;
        }
        else if ((~status) & (1<<TXB1CNTRL_TXREQ)) {
            buffer_adress = Load_TX1;
            rts_txx = RTS_TX1;
        }
        else if ((~status) & (1<<TXB2CNTRL_TXREQ)) {
            buffer_adress = Load_TX2;
            rts_txx = RTS_TX2;
        }
    }
    
    /*
     * Temporäres Array erzeugen und die CAN-Nachricht dort hinein sortieren */
    char temp_msg[14];
    temp_msg[0] = buffer_adress;
    temp_msg[1] = message->Id>>3;
    temp_msg[2] = ((char)message->Id<<5)|0;
    temp_msg[3] = 0;
    temp_msg[4] = 0;
    temp_msg[5] = message->DataLength;
	unsigned char i;
    for (i=0; i<message->DataLength; i++)
	{
    	temp_msg[6+i] = (message->Data[i]);
	}
	
	/*
	 * Daten in den TX-Buffer schreiben */
	bcm2835_spi_transfern(temp_msg, 14);
	
	/*
	 * Nachricht abschicken */
	bcm2835_spi_transfer(rts_txx);
	
	return 1;
}
