/*
 * can.c
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


/* Includes ----------------------------------------------------------*/
#include "can.h"

/* Private typedef ---------------------------------------------------*/
/* Private define ----------------------------------------------------*/
/* Private macro -----------------------------------------------------*/
/* Private variables -------------------------------------------------*/
/* Private function prototypes ---------------------------------------*/
/* Private functions -------------------------------------------------*/
void configCanBus(void) {
    mcp2515_init();
}

void sendCanMsg (can_message *Msg) {
    #if CAN_DEBUG
    printf("Send Id: %02X  Length: %d Data: ", Msg->Id, Msg->DataLength);
    for(uint8_t i=0; i<Msg->DataLength; i++) {
            printf("%02X ", Msg->Data[i]);
    }
    printf("\n");
    #endif
    
    mcp2515_send_message(Msg);
}

bool receiveCanMsg(can_message *Msg) {
    /*
     * Prüfen ob es eine neue CAN-Nachricht gibt,
     * wenn nicht, dann Funktion beenden und "0" zurückgeben */
    if (mcp2515_read_message(Msg) == TRUE) {
        #if CAN_DEBUG
        printf("Receive Id: %02X  Length: %d Data: ", Msg->Id, Msg->DataLength);
        for(uint8_t i=0; i<Msg->DataLength; i++) {
            printf("%02X ", Msg->Data[i]);
        }
        printf("\n");
        #endif
        
        return TRUE;
    } else {
        return FALSE;
    }
}


