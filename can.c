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


#include <stdio.h>
#include <unistd.h>
#include "can.h"
#include "mcp2515.h"

char can_read_message (struct can_message *message) {
    /*
     * Prüfen ob es eine neue CAN-Nachricht gibt,
     * wenn nicht, dann Funktion beenden und "0" zurückgeben */
    char raw_message[13];
    if (mcp2515_read_message(raw_message) != 1) {
        return 0;
    }

    /*
     * Neue CAN-Nachricht vorhanden ->
     * Daten in Struktur "can_message" sortieren */
    unsigned char i;
    message->id = raw_message[0];
    message->id = message->id<<3;
    message->id = (message->id|(raw_message[1]>>5));
    message->rtr = (raw_message[4]&(1<<RTR));
    message->length = (raw_message[4]&((1<<DLC3)|(1<<DLC2)|(1<<DLC1)|(1<<DLC0)));
    for(i=0; i<message->length; i++) {
        message->data[i] = raw_message[i+5];
        }
    
    /*
     * Nachrichtenlänge prüfen und bei Fehler Nachricht verwerfen */
    if(message->length > 8) {
        return 0;
        }
    
    #if CAN_AUSGABE
        printf("ID: %d  Länge: %d Daten: ", message->id, message->length);
        for(i=0; i<message->length; i++) {
            printf("%02X ", message->data[i]);
        }
    #endif
    return 1;
}

void can_send_message (struct can_message *message) {
    mcp2515_send_message(message);
}

char check_ack(unsigned int id) {
  struct can_message message;
  unsigned char i;
  
  /*
   * mehrmals prüfen, ob eine Nachricht vorliegt */
  for (i=0; i<255; i++) {
    usleep(5);
    if (can_read_message(&message) && message.id == id) {
      if (message.data[0] == 0x79) {
        printf("ACK erhalten\n");
        return 1;
      }
      if (message.data[0] == 0x1F) {
        printf("NACK erhalten\n");
        return 2;
      }
    }
  }
  printf("Keine Antwort\n");
  return 0;
}

void enter_bootloader(void) {
  printf("Starte Bootloader: ");
  struct can_message message;
  message.id = 0x79;
  message.rtr = 0;
  message.length = 0;
  can_send_message(&message);
  
  check_ack(message.id);
}

void get_command(void) {
  printf("Get version and commands: ");
  struct can_message message;
  message.id = 0x00;
  message.rtr = 0;
  message.length = 0;
  can_send_message(&message);
  
  if (check_ack(0x00) != 1) {
    return;
  }
  
  int i = 0;
  while(i < 14) {
    usleep(100);
    if (can_read_message(&message) == 1) {
      switch(i) {
        case 0: {
          printf("-Bytes to be sent: %d\n", message.data[0]);
          break;
        }
        case 1: {
          printf("-Bootloader Version: %d\n", message.data[0]);
          break;
        }
        case 2: {
          printf("-Get command: %02X\n", message.data[0]);
          break;
        }
        case 3: {
          printf("-Get Version & Read Protaction: %02X\n", message.data[0]);
          break;
        }
        case 4: {
          printf("-Get ID command: %02X\n", message.data[0]);
          break;
        }
        case 5: {
          printf("-Speed command: %02X\n", message.data[0]);
          break;
        }
        case 6: {
          printf("-Read memory command: %02X\n", message.data[0]);
          break;
        }
        case 7: {
          printf("-Go command: %d\n", message.data[0]);
          break;
        }
        case 8: {
          printf("-Write memory command: %d\n", message.data[0]);
          break;
        }
        case 9: {
          printf("-Erase memory command: %02X\n", message.data[0]);
          break;
        }
        case 10: {
          printf("-Write Protect command: %02X\n", message.data[0]);
          break;
        }
        case 11: {
          printf("-Write Unprotect command: %02X\n", message.data[0]);
          break;
        }
        case 12: {
          printf("-Readout Protect command: %02X\n", message.data[0]);
          break;
        }
        case 13: {
          printf("-Readout Unprotect command: %02X\n", message.data[0]);
          break;
        }
      }
      i++;
    }
  }
  if (check_ack(0x00) != 1) {
    return;
  }
}
