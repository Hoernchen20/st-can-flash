#ifndef can_h
#define can_h
/*
 * can.h
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

//Ausgabe
#define CAN_AUSGABE 0

//Variablen
struct can_message {
	unsigned int    id;
	unsigned char   rtr;
	unsigned char   length;
	unsigned char   data[8];
};
extern char neue_minute;

//Funktion
char can_read_message (struct can_message *message);
void can_send_message (struct can_message *message);
char check_ack(unsigned int id);
void enter_bootloader(void);
void get_command(void);
void read_mem_command(void);
void go_command(void);
void get_id_command(void);
#endif

