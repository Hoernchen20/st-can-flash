/*
 * bootloader_communication.h
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
 
 
#ifndef BOOTLOADER_COMMUNICATION_H
#define BOOTLOADER_COMMUNICATION_H

/* Includes ----------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "can.h"

/* Exported constants ------------------------------------------------*/
/* Exported variables ------------------------------------------------*/
extern char neue_minute;

/* Exported types ----------------------------------------------------*/
#ifndef BOOL
#define BOOL
typedef enum { FALSE, TRUE }bool;
#endif

/* Exported macro ----------------------------------------------------*/
/* Exported functions ------------------------------------------------*/
bool startBootloader(void);
void printVersionAndCommands(void);
void printChipId(void);
void readMemory(int memory_size);
void startMicrocontroller(void);
int writeMemory(unsigned int adress, char *file_name);
void eraseMemory(void);



#endif /* BOOTLOADER_COMMUNICATION_H */
