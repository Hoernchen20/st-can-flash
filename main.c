/*
 * main.c
 * 
 * Copyright 2015  <pi@raspi-nas>
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
#include "can.c"
#include "mcp2515.c"

int main(int argc, char **argv)
{
  printf("ST-Flash over CAN v0.1\n");
  
  /*
   * MCP2515 initialisieren */
  mcp2515_init();
   
  /*
   * Bootloader starten */
  enter_bootloader();
  usleep(100);
  
  /*
   * Version lesen */
  get_command();
  usleep(100);
  
  /*
   * Get ID */
  get_id_command();
  usleep(100);
  
  /*
   * Start user application */
  //go_command();
  
  printf("Ende\n");
	return 0;
}

