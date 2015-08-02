/*
 * mcp2515.c
 * 
 * Copyright 2014  Felix Horn
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
    
    printf("Initialisierung MCP2515: OK\n");

    #if MCP2515_Ausgabe
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
char mcp2515_status(void) {
    char buf[2] = {Read_Status, 0};
    bcm2835_spi_transfern(buf, 2);
    return buf[1];
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

char mcp2515_read_message (char *p_data) {
    /*
     * Prüfen, ob neue Nachricht da, wenn ja,
     * auszulesende Bufferadresse zuweisen */
    char temp = mcp2515_status();
    if (temp & (1<<CANINTF_RX0IF)) {
        temp = Read_RX0;
    }
    else if (temp & (1<<CANINTF_RX1IF)) {
        temp = Read_RX1;
    }
    else {
        return 0;
    }
    
    /*
     * Bufferadresse an den Anfang des temporären Arrays schreiben
     * und Daten vom MCP2515 abholen */
    char buf[14];
    buf[0] = temp;
    bcm2835_spi_transfern(buf, 14);
    
    /*
     * Ensprechendes Interrupt-Flag löschen */
    char buf_2[4];
    buf_2[0] = Bit_Modify;
    buf_2[1] = CANINTF;
    buf_2[3] = 0;
    if (temp == Read_RX0) {
        buf_2[2] = (1<<RX0IF);
    }
    else {
        buf_2[2] = (1<<RX1IF);
    }
    bcm2835_spi_transfern(buf_2, sizeof(buf_2));
    
    #if MCP2515_Ausgabe
        unsigned char j;
        printf("Neue Nachricht\n");
        printf("SIDH: %02X  SIDL: %02X  EID8: %02X  EID0: %02X  DLC: %02X  Daten: ",buf[1], buf[2], buf[3], buf[4], buf[5]);
        for(j=1; j<=buf[5]; j++) {
            printf("%02X ", buf[j+5]);
            }
        printf("\n");
    #endif
    
    /* Temporäres Array um ein Byte zurückschieben,
     * um Bufferadresse zu löschen */
    unsigned char i;
    for (i=0; i<13; i++) {
        *p_data = buf[i+1];
        p_data++;
    }

    return 1;
}
    
void tx_buffer_0_write(void) {
    //Daten laden
    char buf_3[10] = {0b01000000, 0b11111101, 0b11001011, 0b11111111, 0b11111101, 0b00000100, 170, 35, 20, 5};
    bcm2835_spi_transfern(buf_3, 10);
    
    //Übertragung starten
    bcm2835_spi_transfer(0b10000001);
}

char mcp2515_send_message (struct can_message *message) {
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
    temp_msg[1] = message->id>>3;
    temp_msg[2] = ((char)message->id<<5)|0;
    temp_msg[3] = 0;
    temp_msg[4] = 0;
    temp_msg[5] = ((char)(message->rtr<<6)|(message->length));
	unsigned char i;
    for (i=0; i<message->length; i++)
	{
    	temp_msg[6+i] = (message->data[i]);
	}
	
	/*
	 * Daten in den TX-Buffer schreiben */
	bcm2835_spi_transfern(temp_msg, 14);
	
	/*
	 * Nachricht abschicken */
	bcm2835_spi_transfer(rts_txx);
	
	return 1;
}
