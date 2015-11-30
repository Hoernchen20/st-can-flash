#ifndef mcp2515_h
#define mcp2515_h
/*
 * mcp2515.h
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


#include "mcp2515_register_definitions.h"

#ifndef BOOL
#define BOOL
typedef enum { FALSE, TRUE }bool;
#endif

typedef struct {
    uint16_t    Id;
    uint8_t     DataLength;
    uint8_t     Data[8];
}can_message;

//Ausgabe
#define MCP2515_Ausgabe 0

//Funktionen
void mcp2515_init(void);
uint8_t mcp2515_status(void);
char txb0ctrl_status(void);
char rx_status(void);
bool mcp2515_read_message (can_message *message);
void tx_buffer_0_write(void);
char mcp2515_send_message (can_message *message);

#endif
