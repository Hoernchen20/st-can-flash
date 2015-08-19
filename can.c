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

#define ACK 0x79
#define NACK 0x1F

#define GET_COMMAND 0x00
#define GET_VER_RP_STATUS_COMMAND 0x01
#define GET_ID_COMMAND 0x02
#define SPEED_COMMAND 0x03
#define READ_MEM_COMMAND 0x11
#define GO_COMMAND 0x21
#define WRITE_MEM_COMMAND 0x31
#define ERASE_COMMAND 0x43
#define WRITE_PROTECT_COMMAND 0x63
#define WRITE_UNPROTECT_COMMAND 0x73
#define READOUT_PROTECT_COMMAND 0x82
#define READOUT_UNPROTECT_COMMAND 0x92

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
  unsigned int i;
  
  /*
   * mehrmals prüfen, ob eine Nachricht vorliegt */
  for (i=0; i<65000; i++) {
    if (can_read_message(&message)) {
      if(message.id == id) {
        if (message.data[0] == ACK) {
          //printf("ACK\n");
          return 1;
        }
        if (message.data[0] == NACK) {
          //printf("NACK\n");
          return 2;
        }
      }
    }
  }
  //printf("No answer\n");
  return 0;
}

void enter_bootloader(void) {
  printf("Start bootloader: ");
  char tmp;
  struct can_message message;
  message.id = ACK;
  message.rtr = 0;
  message.length = 0;
  can_send_message(&message);
  
  tmp = check_ack(message.id);
  
  if (tmp == 0) {
    printf("No answer\n");
  } else if (tmp == 1) {
    printf("ACK\n");
  } else if (tmp == 2) {
    printf("NACK\n");
  } else {
    printf("Error\n");
  }
}

void get_command(void) {
  printf("Get version and commands: ");
  struct can_message message;
  unsigned int i, command_number = 0;
  message.id = GET_COMMAND;
  message.rtr = 0;
  message.length = 0;
  can_send_message(&message);
  
  if (check_ack(GET_COMMAND) != 1) {
    return;
  }
  
  for (i=0; i<65000; i++) {
    if (can_read_message(&message) == 1) {
    switch(command_number) {
      case 0: {
        printf("  -Bytes to be sent: %d\n", message.data[0]);
        break;
      }
      case 1: {
        printf("  -Bootloader Version: %d\n", message.data[0]);
        break;
      }
      case 2: {
        printf("  -Get command: %02X\n", message.data[0]);
        break;
      }
      case 3: {
        printf("  -Get Version & Read Protaction: %02X\n", message.data[0]);
        break;
      }
      case 4: {
        printf("  -Get ID command: %02X\n", message.data[0]);
        break;
      }
      case 5: {
        printf("  -Speed command: %02X\n", message.data[0]);
        break;
      }
      case 6: {
        printf("  -Read memory command: %02X\n", message.data[0]);
        break;
      }
      case 7: {
        printf("  -Go command: %d\n", message.data[0]);
        break;
      }
      case 8: {
        printf("  -Write memory command: %d\n", message.data[0]);
        break;
      }
      case 9: {
        printf("  -Erase memory command: %02X\n", message.data[0]);
        break;
      }
      case 10: {
        printf("  -Write Protect command: %02X\n", message.data[0]);
        break;
      }
      case 11: {
        printf("  -Write Unprotect command: %02X\n", message.data[0]);
        break;
      }
      case 12: {
        printf("  -Readout Protect command: %02X\n", message.data[0]);
        break;
      }
      case 13: {
        printf("  -Readout Unprotect command: %02X\n", message.data[0]);
        break;
      }
    }
    command_number++;
    }
  }
  printf("  -Get version and commands end: ");
  check_ack(GET_COMMAND);
}

void get_id_command(void) {
  printf("Get ID: ");
  unsigned int i;
  struct can_message message;
  message.id = GET_ID_COMMAND;
  message.rtr = 0;
  message.length = 0;
  
  can_send_message(&message);
  
  if (check_ack(GET_ID_COMMAND) != 1) {
    return;
  }
  
  for (i=0; i<65000; i++) {
    if (can_read_message(&message) == 1) {
      printf("  -ID: %02X%02X\n  -Get ID end: ", message.data[0], message.data[1]);
      break;
    }  
  }
  
  check_ack(GET_ID_COMMAND);
}

int read_mem_row(int adress, unsigned char *app_code) {
  int i = 5000;
  struct can_message message;
  message.id = READ_MEM_COMMAND;
  message.rtr = 0;
  message.length = 5;
  message.data[4] = 5;
  message.data[3] = adress;
  message.data[2] = adress>>8;
  message.data[1] = adress>>16;
  message.data[0] = adress>>24;
  can_send_message(&message);
  
  if (check_ack(READ_MEM_COMMAND) != 1) return 0;

  while (can_read_message(&message) != 1) {
    i--;
    if (i == 0) return 0;
  }
  
  for (i=0; i<6; i++) {
    *app_code = message.data[i];
    app_code++;
  }
  
  if (check_ack(READ_MEM_COMMAND) != 1) return 0;
  
  return 1;
}

void read_mem_command(int memory_size) {
  printf("Read Memory:\n");
  
  unsigned char app_code[7];
  
  int loop_counter, adress;
  FILE *fp = fopen("read_memory.txt", "w");
  
  switch (memory_size) {
    case 4:
      loop_counter = 1024;
      break;
    case 8:
      loop_counter = 2048;
      break;
    case 16:
      loop_counter = 4096;
      break;
    case 32:
      loop_counter = 8192;
      break;
    case 64:
      loop_counter = 16384;
      break;
    case 128:
      loop_counter = 32768;
      break;
    default:
      printf("Wrong memory size\n");
      return;
  }
  
  memory_size = loop_counter;

  for (loop_counter = 1; loop_counter <= memory_size; loop_counter++) {
    adress = 0x07FFFFFC + loop_counter * 4;
    printf("Read Block %d of %d\n", loop_counter, memory_size);
    read_mem_row(adress, app_code);
    
    /*printf("%02x%02x %02x%02x ", app_code[1], app_code[0],
      app_code[3], app_code[2]);*/
    
    fprintf(fp, "%02x%02x %02x%02x ", app_code[1], app_code[0],
      app_code[3], app_code[2]);
    
    if (!(loop_counter % 4)) {
      printf("\n");
      fprintf(fp, "\n");
    }
  }
  fclose(fp);
}

void go_command(void) {
  printf("Start user application: ");
  struct can_message message;
  message.id = GO_COMMAND;
  message.rtr = 0;
  message.length = 4;
  message.data[0] = 0x08;
  message.data[1] = 0x00;
  message.data[2] = 0x00;
  message.data[3] = 0x00;
  
  can_send_message(&message);
  
  if (check_ack(GO_COMMAND) != 1) {
    return;
  }
}

