#ifndef mcp2515_register_definitions_h
#define mcp2515_register_definitions_h
/*
 * mcp2515_register_definitions.h
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

// ***** I/O REGISTER DEFINITIONS *****************************************

#define	TXB0CTRL	 0x30 // TRANSMIT BUFFER 0 CONTROL REGISTER
#define	TXB1CTRL	 0x40 // TRANSMIT BUFFER 1 CONTROL REGISTER
#define	TXB2CTRL	 0x50 // TRANSMIT BUFFER 2 CONTROL REGISTER
#define	TXRTSCTRL	 0x0D // TXRTS PIN CONTROL AND STATUS REGISTER
#define	TXB0SIDH	 0x31 // TRANSMIT BUFFER 0 STANDARD IDENTIFIER HIGH
#define	TXB1SIDH	 0x41 // TRANSMIT BUFFER 1 STANDARD IDENTIFIER HIGH
#define	TXB2SIDH	 0x51 // TRANSMIT BUFFER 2 STANDARD IDENTIFIER HIGH
#define	TXB0SIDL	 0x32 // TRANSMIT BUFFER 0 STANDARD IDENTIFIER LOW
#define	TXB1SIDL	 0x42 // TRANSMIT BUFFER 1 STANDARD IDENTIFIER LOW
#define	TXB2SIDL	 0x52 // TRANSMIT BUFFER 2 STANDARD IDENTIFIER LOW
#define	TXB0EID8	 0x33 // TRANSMIT BUFFER 0 EXTENDED IDENTIFIER HIGH
#define	TXB1EID8	 0x43 // TRANSMIT BUFFER 1 EXTENDED IDENTIFIER HIGH
#define	TXB2EID8	 0x53 // TRANSMIT BUFFER 2 EXTENDED IDENTIFIER HIGH
#define	TXB0EID0	 0x34 // TRANSMIT BUFFER 0 EXTENDED IDENTIFIER LOW
#define	TXB1EID0	 0x44 // TRANSMIT BUFFER 1 EXTENDED IDENTIFIER LOW
#define	TXB2EID0	 0x54 // TRANSMIT BUFFER 2 EXTENDED IDENTIFIER LOW
#define	TXB0DLC		 0x35 // TRANSMIT BUFFER 0 DATA LENGTH CODE
#define	TXB1DLC		 0x45 // TRANSMIT BUFFER 1 DATA LENGTH CODE
#define	TXB2DLC		 0x55 // TRANSMIT BUFFER 2 DATA LENGTH CODE
#define	TXB0D0		 0x36 // TRANSMIT BUFFER 0 DATA BYTE 0
#define	TXB0D1		 0x37 // TRANSMIT BUFFER 0 DATA BYTE 1
#define	TXB0D2		 0x38 // TRANSMIT BUFFER 0 DATA BYTE 2
#define	TXB0D3		 0x39 // TRANSMIT BUFFER 0 DATA BYTE 3
#define	TXB0D4		 0x3A // TRANSMIT BUFFER 0 DATA BYTE 4
#define	TXB0D5		 0x3B // TRANSMIT BUFFER 0 DATA BYTE 5
#define	TXB0D6		 0x3C // TRANSMIT BUFFER 0 DATA BYTE 6
#define	TXB0D7		 0x3D // TRANSMIT BUFFER 0 DATA BYTE 7
#define	TXB1D0		 0x46 // TRANSMIT BUFFER 1 DATA BYTE 0
#define	TXB1D1		 0x47 // TRANSMIT BUFFER 1 DATA BYTE 1
#define	TXB1D2		 0x48 // TRANSMIT BUFFER 1 DATA BYTE 2
#define	TXB1D3		 0x49 // TRANSMIT BUFFER 1 DATA BYTE 3
#define	TXB1D4		 0x4A // TRANSMIT BUFFER 1 DATA BYTE 4
#define	TXB1D5		 0x4B // TRANSMIT BUFFER 1 DATA BYTE 5
#define	TXB1D6		 0x4C // TRANSMIT BUFFER 1 DATA BYTE 6
#define	TXB1D7		 0x4D // TRANSMIT BUFFER 1 DATA BYTE 7
#define	TXB2D0		 0x56 // TRANSMIT BUFFER 2 DATA BYTE 0
#define	TXB2D1		 0x57 // TRANSMIT BUFFER 2 DATA BYTE 1
#define	TXB2D2		 0x58 // TRANSMIT BUFFER 2 DATA BYTE 2
#define	TXB2D3		 0x59 // TRANSMIT BUFFER 2 DATA BYTE 3
#define	TXB2D4		 0x5A // TRANSMIT BUFFER 2 DATA BYTE 4
#define	TXB2D5		 0x5B // TRANSMIT BUFFER 2 DATA BYTE 5
#define	TXB2D6		 0x5C // TRANSMIT BUFFER 2 DATA BYTE 6
#define	TXB2D7		 0x5D // TRANSMIT BUFFER 2 DATA BYTE 7
#define	RXB0CTRL	 0x60 // RECEIVE BUFFER 0 CONTROL
#define	RXB1CTRL	 0x70 // RECEIVE BUFFER 1 CONTROL
#define	BFPCTRL		 0x0C // RXnBF Pin Control and Status
#define	RXB0SIDH	 0x61 // RECEIVE BUFFER 0 STANDARD IDENTIFIER HIGH
#define	RXB1SIDH	 0x71 // RECEIVE BUFFER 1 STANDARD IDENTIFIER HIGH
#define	RXB0SIDL	 0x62 // RECEIVE BUFFER 0 STANDARD IDENTIFIER LOW
#define	RXB1SIDL	 0x72 // RECEIVE BUFFER 1 STANDARD IDENTIFIER LOW
#define	RXB0EID8	 0x63 // RECEIVE BUFFER 0 EXTENDED IDENTIFIER HIGH
#define	RXB1EID8	 0x73 // RECEIVE BUFFER 1 EXTENDED IDENTIFIER HIGH
#define	RXB0EID0	 0x64 // RECEIVE BUFFER 0 EXTENDED IDENTIFIER LOW
#define	RXB1EID0	 0x74 // RECEIVE BUFFER 1 EXTENDED IDENTIFIER LOW
#define	RXB0DLC		 0x65 // RECEIVE BUFFER 0 DATA LENGHT CODE
#define	RXB1DLC		 0x75 // RECEIVE BUFFER 1 DATA LENGHT CODE
#define	RXB0DM0		 0x66 // RECEIVE BUFFER 0 DATA BYTE 0
#define	RXB0DM1		 0x67 // RECEIVE BUFFER 0 DATA BYTE 1
#define	RXB0DM2		 0x68 // RECEIVE BUFFER 0 DATA BYTE 2
#define	RXB0DM3		 0x69 // RECEIVE BUFFER 0 DATA BYTE 3
#define	RXB0DM4		 0x6A // RECEIVE BUFFER 0 DATA BYTE 4
#define	RXB0DM5		 0x6B // RECEIVE BUFFER 0 DATA BYTE 5
#define	RXB0DM6		 0x6C // RECEIVE BUFFER 0 DATA BYTE 6
#define	RXB0DM7		 0x6D // RECEIVE BUFFER 0 DATA BYTE 7
#define	RXB1DM0		 0x76 // RECEIVE BUFFER 1 DATA BYTE 0
#define	RXB1DM1		 0x77 // RECEIVE BUFFER 1 DATA BYTE 1
#define	RXB1DM2		 0x78 // RECEIVE BUFFER 1 DATA BYTE 2
#define	RXB1DM3		 0x79 // RECEIVE BUFFER 1 DATA BYTE 3
#define	RXB1DM4		 0x7A // RECEIVE BUFFER 1 DATA BYTE 4
#define	RXB1DM5		 0x7B // RECEIVE BUFFER 1 DATA BYTE 5
#define	RXB1DM6		 0x7C // RECEIVE BUFFER 1 DATA BYTE 6
#define	RXB1DM7		 0x7D // RECEIVE BUFFER 1 DATA BYTE 7
#define	RXF0SIDH	 0x00 // FILTER 0 STANDARD IDENTIFIER HIGH
#define	RXF1SIDH	 0x04 // FILTER 1 STANDARD IDENTIFIER HIGH
#define	RXF2SIDH	 0x08 // FILTER 2 STANDARD IDENTIFIER HIGH
#define	RXF3SIDH	 0x10 // FILTER 3 STANDARD IDENTIFIER HIGH
#define	RXF4SIDH	 0x14 // FILTER 4 STANDARD IDENTIFIER HIGH
#define	RXF5SIDH	 0x18 // FILTER 5 STANDARD IDENTIFIER HIGH
#define	RXF0SIDL	 0x01 // FILTER 0 STANDARD IDENTIFIER LOW
#define	RXF1SIDL	 0x05 // FILTER 1 STANDARD IDENTIFIER LOW
#define	RXF2SIDL	 0x09 // FILTER 2 STANDARD IDENTIFIER LOW
#define	RXF3SIDL	 0x11 // FILTER 3 STANDARD IDENTIFIER LOW
#define	RXF4SIDL	 0x15 // FILTER 4 STANDARD IDENTIFIER LOW
#define	RXF5SIDL	 0x19 // FILTER 5 STANDARD IDENTIFIER LOW
#define	RXF0EID8	 0x02 // FILTER 0 EXTENDED IDENTIFIER HIGH
#define	RXF1EID8	 0x06 // FILTER 1 EXTENDED IDENTIFIER HIGH
#define	RXF2EID8	 0x0A // FILTER 2 EXTENDED IDENTIFIER HIGH
#define	RXF3EID8	 0x12 // FILTER 3 EXTENDED IDENTIFIER HIGH
#define	RXF4EID8	 0x16 // FILTER 4 EXTENDED IDENTIFIER HIGH
#define	RXF5EID8	 0x1A // FILTER 5 EXTENDED IDENTIFIER HIGH
#define	RXF0EID0	 0x03 // FILTER 0 EXTENDED IDENTIFIER LOW
#define	RXF1EID0	 0x07 // FILTER 1 EXTENDED IDENTIFIER LOW
#define	RXF2EID0	 0x0B // FILTER 2 EXTENDED IDENTIFIER LOW
#define	RXF3EID0	 0x13 // FILTER 3 EXTENDED IDENTIFIER LOW
#define	RXF4EID0	 0x17 // FILTER 4 EXTENDED IDENTIFIER LOW
#define	RXF5EID0	 0x1B // FILTER 5 EXTENDED IDENTIFIER LOW
#define	RXM0SIDH	 0x20 // MASK 0 STANDARD IDENTIFIER HIGH
#define	RXM1SIDH	 0x24 // MASK 1 STANDARD IDENTIFIER HIGH
#define	RXM0SIDL	 0x21 // MASK 0 STANDARD IDENTIFIER LOW
#define	RXM1SIDL	 0x25 // MASK 1 STANDARD IDENTIFIER LOW
#define	RXM0EID8	 0x22 // MASK 0 EXTENDED IDENTIFIER HIGH
#define	RXM1EID8	 0x26 // MASK 1 EXTENDED IDENTIFIER HIGH
#define	RXM0EID0	 0x23 // MASK 0 EXTENDED IDENTIFIER LOW
#define	RXM1EID0	 0x27 // MASK 1 EXTENDED IDENTIFIER LOW
#define	CNF1		 0x2A // CONFIGURATION 1
#define	CNF2		 0x29 // CONFIGURATION 2
#define	CNF3		 0x28 // CONFIGURATION 3
#define	TEC			 0x1C // TRANSMIT ERROR COUNTER
#define	REC			 0x1D // RECEIVER ERROR COUNTER
#define	EFLG		 0x2D // ERROR FLAG
#define	CANINTE		 0x2B // INTERRUPT ENABLE
#define	CANINTF		 0x2C // INTERRUPT FLAG
#define	CANCTRL		 0x0F // CAN CONTROL REGISTER
#define	CANSTAT		 0x0E // CAN STATUS REGISTER

//*****Transmit Control***************************************
//3-1: TXBnCTRL - TRANSMIT BUFFER n CONTROL REGISTER
#define	TXP0	 0 // Transmit Buffer Priority
#define	TXP1	 1
#define	TXREQ	 3 // Message Transmit Request bit
#define	TXERR	 4 // Transmission Error Detected bit
#define	MLOA	 5 // Message Lost Arbitration bit
#define	ABTF	 6 // Message Aborted Flag bit

//3-2: TXRTSCTRL - TXnRTS PIN CONTROL AND STATUS REGISTER
#define	B0RTSM	 0 // TX0RTS Pin mode bit
#define	B1RTSM	 1 // TX1RTS Pin mode bit
#define	B2RTSM	 2 // TX2RTS Pin mode bit
#define	B0RTS	 3 // TX0RTS Pin State bit
#define	B1RTS	 4 // TX1RTS Pin State bit
#define	B2RTS	 5 // TX2RTS Pin State bit

//3-3: TXBnSIDH - TRANSMIT BUFFER n STANDARD IDENTIFIER HIGH
#define	SID3	 0 // Standard Identifier bits
#define	SID4	 1
#define	SID5	 2
#define	SID6	 3
#define	SID7	 4
#define	SID8	 5
#define	SID9	 6
#define	SID10	 7

//3-4: TXBnSIDL - TRANSMIT BUFFER n STANDARD IDENTIFIER LOW
#define	EID16	 0 // Extended Identifier bits
#define	EID17	 1
#define	EXIDE	 3	// Extended Identifier Enable bit
#define	SID0	 5 // Standard Identifier bits
#define	SID1	 6
#define	SID2	 7

//3-5: TXBnEID8 - TRANSMIT BUFFER n EXTENDED IDENTIFIER HIGH
#define	EID8	 0 // Extended Identifier bits
#define	EID9	 1
#define	EID10	 2
#define	EID11	 3
#define	EID12	 4
#define	EID13	 5
#define	EID14	 6
#define	EID15	 7

//3-6: TXBnEID0 - TRANSMIT BUFFER n EXTENDED IDENTIFIER LOW
#define	EID0	 0 // Extended Identifier bits
#define	EID1	 1
#define	EID2	 2
#define	EID3	 3
#define	EID4	 4
#define	EID5	 5
#define	EID6	 6
#define	EID7	 7

//3-7: TXBnDLC - TRANSMIT BUFFER n DATA LENGTH CODE
#define	DLC0	 0	// Data Length Code bits
#define	DLC1	 1
#define	DLC2	 2
#define	DLC3	 3
#define	RTR		 6 // Remote Transmission Request bit

//3-8: TXBnDm  TRANSMIT BUFFER n DATA BYTE m
#define	TXBnDm0	 0 // Transmit Buffer n Data Field Bytes m
#define	TXBnDm1	 1
#define	TXBnDm2	 2
#define	TXBnDm3	 3
#define	TXBnDm4	 4
#define	TXBnDm5	 5
#define	TXBnDm6	 6
#define	TXBnDm7	 7

//*****Receive Control****************************************
//4-1: RXB0CTRL - RECEIVE BUFFER 0 CONTROL
#define	FILHIT 	 0	// Filter Hit bit
#define	BUKT1	 1	// Read-only Copy of BUKT bit
#define	BUKT	 2	// Rollover Enable bit
#define	RXRTR	 3	// Received Remote Transfer Request bit
#define	RXM0	 5 // Receive Buffer Operating Mode bits
#define	RXM1	 6

//4-2: RXB1CTRL - RECEIVE BUFFER 1 CONTROL
#define	FILHIT0	 0	// Filter Hit bits
#define	FILHIT1	 1
#define	FILHIT2	 2
#define	RXRTR	 3	// Received Remote Transfer Request bit
#define	RXM0	 5	// Receive Buffer Operating Mode bits
#define	RXM1	 6

//4-3: RXnBF - Pin Control and Status 
#define	B0BFM	 0 // RX0BF Pin Operation Mode bit
#define	B1BFM	 1 // RX1BF Pin Operation Mode bit
#define	B0BFE	 2 // RX0BF Pin Function Enable bit
#define	B1BFE	 3 // RX1BF Pin Function Enable bit
#define	B0BFS	 4 // RX0BF Pin State bit (Digital Output mode only)
#define	B1BFS	 5 // RX1BF Pin State bit (Digital Output mode only)

//4-4: RXBnSIDH - RECEIVE BUFFER n STANDARD IDENTIFIER HIGH
#define	SID3	 0 // Standard Identifier bits
#define	SID4	 1
#define	SID5	 2
#define	SID6	 3
#define	SID7	 4
#define	SID8	 5
#define	SID9	 6
#define	SID10	 7

//4-5: RXBnSIDL - RECEIVE BUFFER n STANDARD IDENTIFIER LOW
#define	EID16	 0 // Extended Identifier bits
#define	EID17	 1
#define	IDE		 3	// Extended Identifier Flag bit
#define	SRR		 4	// Standard Frame Remote Transmit Request bit
#define	SID0	 5 // Standard Identifier bits
#define	SID1	 6
#define	SID2	 7

//4-6: RXBnEID8 - RECEIVE BUFFER n EXTENDED IDENTIFIER HIGH
#define	EID8	 0 // Extended Identifier bits
#define	EID9	 1
#define	EID10	 2
#define	EID11	 3
#define	EID12	 4
#define	EID13	 5
#define	EID14	 6
#define	EID15	 7

//4-7: RXBnEID0 - RECEIVE BUFFER n EXTENDED IDENTIFIER LOW
#define	EID0	 0 // Extended Identifier bits
#define	EID1	 1
#define	EID2	 2
#define	EID3	 3
#define	EID4	 4
#define	EID5	 5
#define	EID6	 6
#define	EID7	 7

//4-8: RXBnDLC - RECEIVE BUFFER n DATA LENGHT CODE
#define	DLC0	 0	// Data Length Code bits
#define	DLC1	 1
#define	DLC2	 2
#define	DLC3	 3
#define	RB0		 4 // Reserved Bit 0
#define	RB1		 5 // Reserved Bit 1
#define	RTR		 6 // Extended Frame Remote Transmission Request bit

//4-9: RXBnDM - RECEIVE BUFFER n DATA BYTE M
#define	RBnDm0	 0 // Receive Buffer n Data Field Bytes m
#define	RBnDm1	 1
#define	RBnDm2	 2
#define	RBnDm3	 3
#define	RBnDm4	 4
#define	RBnDm5	 5
#define	RBnDm6	 6
#define	RBnDm7	 7

//4-10: RXFnSIDH - FILTER n STANDARD IDENTIFIER HIGH
#define	SID3	 0 // Standard Identifier Filter bits
#define	SID4	 1
#define	SID5	 2
#define	SID6	 3
#define	SID7	 4
#define	SID8	 5
#define	SID9	 6
#define	SID10	 7

//4-11: RXFnSIDL - FILTER n STANDARD IDENTIFIER LOW
#define	EID16	 0 // Extended Identifier Filter bits
#define	EID17	 1
#define	EXIDE	 3 // Extended Identifier Enable bit
#define	SID0	 5 // Standard Identifier Filter bits
#define	SID1	 6
#define	SID2	 7

//4-12: RXFnEID8 - FILTER n EXTENDED IDENTIFIER HIGH
#define	EID8	 0 // Extended Identifier Filter bits
#define	EID9	 1
#define	EID10	 2
#define	EID11	 3
#define	EID12	 4
#define	EID13	 5
#define	EID14	 6
#define	EID15	 7

//4-13: RXFnEID0 - FILTER n EXTENDED IDENTIFIER LOW
#define	EID0	 0 // Extended Identifier Filter bits
#define	EID1	 1
#define	EID2	 2
#define	EID3	 3
#define	EID4	 4
#define	EID5	 5
#define	EID6	 6
#define	EID7	 7

//4-14: RXMnSIDH - MASK n STANDARD IDENTIFIER HIGH
#define	SID3	 0 // Standard Identifier Mask bits
#define	SID4	 1
#define	SID5	 2
#define	SID6	 3
#define	SID7	 4
#define	SID8	 5
#define	SID9	 6
#define	SID10	 7

//4-15: RXMnSIDL - MASK n STANDARD IDENTIFIER LOW
#define	EID16	 0 // Extended Identifier Filter bits
#define	EID17	 1
#define	SID0	 5 // Standard Identifier Mask bits
#define	SID1	 6
#define	SID2	 7

//4-16: RXMnEID8 - MASK n EXTENDED IDENTIFIER HIGH
#define	EID8	 0 // Extended Identifier Filter bits
#define	EID9	 1
#define	EID10	 2
#define	EID11	 3
#define	EID12	 4
#define	EID13	 5
#define	EID14	 6
#define	EID15	 7

//4-17: RXMnEID0 - MASK n EXTENDED IDENTIFIER LOW
#define	EID0	 0 // Extended Identifier Filter bits
#define	EID1	 1
#define	EID2	 2
#define	EID3	 3
#define	EID4	 4
#define	EID5	 5
#define	EID6	 6
#define	EID7	 7

//*****Bit Timing*********************************************
//5-1: CNF1 - CONFIGURATION 1
#define	BRP0	 0 // Baud Rate Prescaler bits
#define	BRP1	 1
#define	BRP2	 2
#define	BRP3	 3
#define	BRP4	 4
#define	BRP5	 5
#define	SJW0	 6 // Synchronization Jump Width Length bits
#define	SJW1	 7

//5-2: CNF2 - CONFIGURATION 2
#define	PRSEG0	 0 // Propagation Segment Length bits
#define	PRSEG1	 1
#define	PRSEG2	 2
#define	PHSEG10	 3 // PS1 Length bits
#define	PHSEG11	 4
#define	PHSEG12	 5
#define	SAM		 6 // Sample Point Configuration bit
#define	BTLMODE	 7 // PS2 Bit Time Lengh bit

//5-3: CNF3 - CONFIGURATION 3
#define	PHSEG20	 0 // PS2 Length bits
#define	PHSEG21	 1
#define	PHSEG22	 2
#define	WAKFIL	 6 // Wake-up Filter bit
#define	SOF		 7 // Start-of-Frame signal bit

//*****Error Detection****************************************
//6-1: TEC - TRANSMIT ERROR COUNTER
#define	TEC0	 0 // Transmit Error Count bits
#define	TEC1	 1
#define	TEC2	 2
#define	TEC3	 3
#define	TEC4	 4
#define	TEC5	 5
#define	TEC6	 6
#define	TEC7	 7

//6-2: REC - RECEIVER ERROR COUNTER
#define	REC0	 0 // Receive Error Count bits
#define	REC1	 1
#define	REC2	 2
#define	REC3	 3
#define	REC4	 4
#define	REC5	 5
#define	REC6	 6
#define	REC7	 7

//6-3: EFLG - ERROR FLAG
#define	EWARN	 0 // Error Warning Flag bit
#define	RXWAR	 1 // Receive Error Warning Flag bit
#define	TXWAR	 2 // Transmit Error Warning Flag bit
#define	RXEP	 3 // Receive Error-Passive Flag bit
#define	TXEP	 4 // Transmit Error-Passive Flag bit
#define	TXBO	 5 // Bus-Off Error Flag bit
#define	RX0OVR	 6 // Receive Buffer 0 Overflow Flag bit
#define	RX1OVR	 7 // Receive Buffer 1 Overflow Flag bit

//*****Interrupt**********************************************
//7-1: CANINTE - INTERRUPT ENABLE
#define	RX0IE	 0 // Receive Buffer 0 Full Interrupt Enable bit
#define	RX1IE	 1 // Receive Buffer 1 Full Interrupt Enable bit
#define	TX0IE	 2 // Transmit Buffer 0 Empty Interrupt Enable bit
#define	TX1IE	 3 // Transmit Buffer 1 Empty Interrupt Enable bit
#define	TX2IE	 4 // Transmit Buffer 2 Empty Interrupt Enable bit
#define	ERRIE	 5 // Error Interrupt Enable bit
#define	WAKIE	 6 // Wakeup Interrupt Enable bit
#define	MERRE	 7 // Message Error Interrupt Enable bit

//7-2: CANINTF - INTERRUPT FLAG
#define	RX0IF	 0 // Receive Buffer 0 Full Interrupt Flag bit
#define	RX1IF	 1 // Receive Buffer 1 Full Interrupt Flag bit
#define	TX0IF	 2 // Transmit Buffer 0 Empty Interrupt Flag bit
#define	TX1IF	 3 // Transmit Buffer 1 Empty Interrupt Flag bit
#define	TX2IF	 4 // Transmit Buffer 2 Empty Interrupt Flag bit
#define	ERRIF	 5 // Error Interrupt Flag bit
#define	WAKIF	 6 // Wakeup Interrupt Flag bit
#define	MERRF	 7 // Message Error Interrupt Flag bit

//*****Can Control********************************************
//10-1: CANCTRL - CAN CONTROL REGISTER
#define	CLKPRE0	 0 // CLKOUT Pin Prescaler bits
#define	CLKPRE1	 1
#define	CLKEN	 2 // CLKOUT Pin Enable bit
#define	OSM		 3 // One Shot Mode bit
#define	ABAT	 4 // Abort All Pending Transmissions bit
#define	REQOP0	 5 // Request Operation Mode bits
#define	REQOP1	 6
#define	REQOP2	 7

//10-2: CANSTAT - CAN STATUS REGISTER
#define	ICOD0	 1 // Interrupt Flag Code bits
#define	ICOD1	 2
#define	ICOD2	 3
#define	OPMOD0	 5 // Operation Mode bits
#define	OPMOD1	 6
#define	OPMOD2	 7

//*****MCP2515 Status*****************************************
#define CANINTF_RX0IF   0
#define CANINTF_RX1IF   1
#define TXB0CNTRL_TXREQ 2
#define CANINTF_TX0IF   3
#define TXB1CNTRL_TXREQ 4
#define CANINTF_TX1IF   5
#define TXB2CNTRL_TXREQ 6
#define CANINTF_TX2IF   7

//*****SPI Instruction Set************************************
//12-1: SPI INSTRUCTION SET
#define	RESET		 0b11000000
#define	READ		 0b00000011
#define	WRITE		 0b00000010
#define	Read_Status	 0b10100000
#define	RX_Status	 0b10110000
#define	Bit_Modify	 0b00000101
#define RTS_TX0      0b10000001
#define RTS_TX0      0b10000001
#define RTS_TX1      0b10000010
#define RTS_TX2      0b10000100
#define Load_TX0	 0b01000000
#define Load_TX1     0b01000010
#define Load_TX2     0b01000100
#define Read_RX0     0b10010000
#define Read_RX1     0b10010100

#endif

