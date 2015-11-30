/*
 * bootloader_communication.c
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
#include "bootloader_communication.h"

/* Private typedef ---------------------------------------------------*/
/* Private define ----------------------------------------------------*/
#define NO_ANSWER   0
#define ACK         0x79
#define NACK        0x1F

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

/* Private macro -----------------------------------------------------*/
/* Private variables -------------------------------------------------*/
/* Private function prototypes ---------------------------------------*/
uint8_t getChipAnswer(uint16_t Id);
int read_mem_row(int adress, unsigned char *app_code, int n_bytes);
int write_mem_row(int adress, unsigned char *app_code, unsigned char n_bytes);

/* Private functions -------------------------------------------------*/

/**
  * @brief  Start the configuration of can bus and start bootloader on 
  *         device
  * @param  None
  * @retval Is TRUE if the device answer or FALSE if there is no communication
  */
bool startBootloader(void) {
    configCanBus();
    
    /* enter bootloader */
    can_message Msg = { ACK, 0, {0} };
    sendCanMsg(&Msg);    
    int8_t DeviceAnswer = getChipAnswer(ACK);

    /* print data */
    printf("Start bootloader: ");
    
    if (DeviceAnswer == NO_ANSWER) {
        printf("No answer\n");
        return FALSE;
    } else if (DeviceAnswer == ACK) {
        printf("ACK\n");
        return TRUE;
    } else if (DeviceAnswer == NACK) {
        printf("NACK\n");
        return TRUE;
    } else {
        printf("Error\n");
        return FALSE;
    }
}

void printVersionAndCommands(void) {
    /* send command */
    can_message Msg = { GET_COMMAND, 0, {0} };
    sendCanMsg(&Msg);
    if (getChipAnswer(GET_COMMAND) == FALSE) {
        return;
    }
    
    printf("Get version and commands: ");
    
  uint8_t command_number = 0;
  for ( uint16_t i=0; i<65000; i++) {
    if (receiveCanMsg(&Msg) == TRUE) {
    switch(command_number) {
      case 0: {
        printf("  -Bytes to be sent: %d\n", Msg.Data[0]);
        break;
      }
      case 1: {
        printf("  -Bootloader Version: %d\n", Msg.Data[0]);
        break;
      }
      case 2: {
        printf("  -Get command: %02X\n", Msg.Data[0]);
        break;
      }
      case 3: {
        printf("  -Get Version & Read Protaction: %02X\n", Msg.Data[0]);
        break;
      }
      case 4: {
        printf("  -Get ID command: %02X\n", Msg.Data[0]);
        break;
      }
      case 5: {
        printf("  -Speed command: %02X\n", Msg.Data[0]);
        break;
      }
      case 6: {
        printf("  -Read memory command: %02X\n", Msg.Data[0]);
        break;
      }
      case 7: {
        printf("  -Go command: %d\n", Msg.Data[0]);
        break;
      }
      case 8: {
        printf("  -Write memory command: %d\n", Msg.Data[0]);
        break;
      }
      case 9: {
        printf("  -Erase memory command: %02X\n", Msg.Data[0]);
        break;
      }
      case 10: {
        printf("  -Write Protect command: %02X\n", Msg.Data[0]);
        break;
      }
      case 11: {
        printf("  -Write Unprotect command: %02X\n", Msg.Data[0]);
        break;
      }
      case 12: {
        printf("  -Readout Protect command: %02X\n", Msg.Data[0]);
        break;
      }
      case 13: {
        printf("  -Readout Unprotect command: %02X\n", Msg.Data[0]);
        break;
      }
    }
    command_number++;
    }
  }
  printf("  -Get version and commands end: ");
  getChipAnswer(GET_COMMAND);
}

/**
  * @brief  Read out the chip identification
  * @param  None
  * @retval None
  */
void printChipId(void) {
    /* send command */
    can_message Msg = { GET_ID_COMMAND, 0, {0} };
    sendCanMsg(&Msg);
    
    /* receive answer */
    if (getChipAnswer(GET_ID_COMMAND) == ACK) {
        for (uint16_t i=0; i<65000; i++) {
            if (receiveCanMsg(&Msg) == TRUE) {
                printf("Chip ID: %02X%02X\n", Msg.Data[0], Msg.Data[1]);
                break;
            }
        }
        getChipAnswer(GET_ID_COMMAND);
    } else {
        printf("Chip ID: NACK\n");
    }
}

int read_mem_row(int adress, unsigned char *app_code, int n_bytes) {
  int i = 5000;
  can_message message;
  message.Id = READ_MEM_COMMAND;
  message.DataLength = 5;
  message.Data[4] = n_bytes+1;
  message.Data[3] = adress;
  message.Data[2] = adress>>8;
  message.Data[1] = adress>>16;
  message.Data[0] = adress>>24;
  sendCanMsg(&message);
  
  if (getChipAnswer(READ_MEM_COMMAND) != 1) return 0;

  while (receiveCanMsg(&message) != 1) {
    i--;
    if (i == 0) return 0;
  }
  
  for (i=0; i<=(n_bytes+1); i++) {
    *app_code = message.Data[i];
    app_code++;
  }
  
  if (getChipAnswer(READ_MEM_COMMAND) != 1) return 0;
  
  return 1;
}

void readMemory(int memory_size) {
  printf("Read Memory:\n");
  
  unsigned char app_code[7];
  
  int loop_counter, adress;
  FILE *fp = fopen("read_memory.txt", "w");
  
  switch (memory_size) {
    case 0:
      loop_counter = 2;
      break;
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
    printf("Read Block %d of %d\r", loop_counter, memory_size);
    read_mem_row(adress, app_code, 4);
    
    /*printf("%02x%02x %02x%02x ", app_code[1], app_code[0],
      app_code[3], app_code[2]);*/
    
    fprintf(fp, "%02x%02x %02x%02x ", app_code[1], app_code[0],
      app_code[3], app_code[2]);
    
    if (!(loop_counter % 4)) {
      //printf("\n");
      fprintf(fp, "\n");
    }
  }
  fclose(fp);
}

/**
  * @brief  Start the user application on chip
  * @param  None
  * @retval None
  */
void startMicrocontroller(void) {
    /* send command */
    can_message Msg = { GO_COMMAND, 4, {0x08, 0x00, 0x00, 0x00} };
    sendCanMsg(&Msg);
    
    /* print data */
    printf("Start user application: ");
  
    if (getChipAnswer(GO_COMMAND) == ACK) {
        printf("started\n");
    } else {
        printf("failed\n");
    }
}

int write_mem_row(int adress, unsigned char *app_code, unsigned char n_bytes) {
  can_message msg_command, msg_data;
  
  msg_command.Id = WRITE_MEM_COMMAND;
  msg_command.DataLength = 5;
  msg_command.Data[4] = n_bytes-1;
  msg_command.Data[3] = adress;
  msg_command.Data[2] = adress>>8;
  msg_command.Data[1] = adress>>16;
  msg_command.Data[0] = adress>>24;
  
  msg_data.Id = 0x04;
  msg_data.DataLength = n_bytes;
  memcpy(msg_data.Data, app_code, n_bytes);

  sendCanMsg(&msg_command);
  
  switch(getChipAnswer(WRITE_MEM_COMMAND)) {
    case 0:
      printf("No answer\n");
      break;
    case 1:
      printf("ACK\n");
      break;
    case 2:
      printf("NACK\n");
      break;
    default:
      printf("Error\n");
  }
  
  sendCanMsg(&msg_data);
  
  switch(getChipAnswer(WRITE_MEM_COMMAND)) {
    case NO_ANSWER:
      printf("No answer\n");
      break;
    case ACK:
      printf("ACK\n");
      break;
    case NACK:
      printf("NACK\n");
      break;
    default:
      printf("Error\n");
  }

  return 0;
}

int writeMemory(unsigned int adress, char *file_name) {
  printf("Write Memory:\n");
  /*
   * Open binary file */
  char needle[] = ".bin";
  if (strstr(file_name, needle) == NULL) {
    printf("\tFile is not a binary file\n");
    return 0;
  }
  FILE *fp = fopen(file_name, "r");
  if (fp == NULL) {
    printf("\tFile cannot read\n");
   return 0;
  }
  
  /*
   * Variables */
  int get_byte = 0;
  int byte_counter = 0;
  int error_counter = 0;
  int end_of_file = 0;
  static unsigned char write_bytes[8] = {0, 0, 0, 0};
  unsigned char read_bytes[8] = {0, 0, 0, 0};

  /*
   * Read bytes from file, save EOF and increase byte_counter */
  do {
    if ((get_byte = fgetc(fp)) == EOF) {
      end_of_file = TRUE;
      if (byte_counter == 0) {
        break;
      }
    }
    
    write_bytes[byte_counter] = get_byte;
    byte_counter++;    
    
    /*
     * Eight byte read or EOF is set -> write bytes to flash */
    if ( (byte_counter >= 8) | ((end_of_file) & (byte_counter > 0))) {
      printf("adress: %08X ", adress);
      printf("data: %02x%02x %02x%02x %02x%02x %02x%02x\n", write_bytes[0], write_bytes[1], write_bytes[2], write_bytes[3],
        write_bytes[4], write_bytes[5], write_bytes[6], write_bytes[7]);
    
      /*
       * Write bytes to flash, wait a moment, than read this byte from flash */
      while (1) {
        write_mem_row(adress, write_bytes, byte_counter);
        read_mem_row(adress, read_bytes, byte_counter/2);
        read_mem_row(adress+4, read_bytes+4, byte_counter/2);
        
        /*
         * After 10 tries of verify bytes exit program */
        if (error_counter > 9) {
          printf("Verify error !\n");
          fclose(fp);
          return 0;
        }
        
        error_counter++;
        
        /*
         * Compare write and read bytes and go to the next bytes if they are the same */
        if ( memcmp(write_bytes, read_bytes, sizeof(write_bytes)) == 0 ) {
          break;
        }
      }
      adress = adress + 8;
      byte_counter = 0;
      error_counter = 0;
      
    }
  } while (end_of_file != TRUE);
  
  printf("All datas are write\n");
  fclose(fp);
  return 1;
}

void eraseMemory(void) {
  printf("Erase Memory: ");
  char tmp = -1;
  can_message message;
  message.Id = ERASE_COMMAND;
  message.DataLength = 1;
  message.Data[0] = 0xFF;
  sendCanMsg(&message);
  
  tmp = getChipAnswer(ERASE_COMMAND);
  
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

uint8_t getChipAnswer(uint16_t Id) {
    can_message Msg = {0};

    /* check several times for ack */
    for (uint16_t i=0; i<65000; i++) {
        if (receiveCanMsg(&Msg)) {
            if (Msg.Id == Id) {
                if (Msg.Data[0] == ACK) {
                    return ACK;
                } else if (Msg.Data[0] == NACK) {
                    return NACK;
                } else {
                    return NO_ANSWER;
                }
            }
        }
    }
    return NO_ANSWER;
}


