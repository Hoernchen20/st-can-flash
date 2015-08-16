/*
 * main.c
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
#include <stdlib.h>
#include "can.c"
#include "mcp2515.c"


int main(int argc, char **argv)
{
  int c;
  int bflg, aflg, errflg;
  char *ifile;
  char *ofile;
  extern char *optarg;
  extern int optind, optopt;

  printf("ST-Flash over CAN v0.1\n");
  
  if (argc < 2) {
    printf("No Options\n");
    return 0;
  }
  
  /*
   * Init can-controller */
  mcp2515_init();
   
  /*
   * Start bootloader */
  enter_bootloader();

  /*
   * start different programs */
  while ((c = getopt(argc, argv, "gvir:swepu")) != -1) {
    switch (c) {
    /*
     * Get bootloader version and allowed commands */
    case 'g':
      get_command();
      break;
    /*
     * Get ID */
    case 'i':
      get_id_command();
      break;
    /*
     * Read Memory */
    case 'r':
      read_mem_command(atoi(optarg));
      break;
    /*
     * Start user application */
    case 's':
      go_command();
      break;
    /*
     * Help text */
    case '?':
      printf("Valid option:\n");
      printf("  -g\n");
      printf("    Get the Version and the allowed command supported by the current version of the bootloader\n");
      printf("  -v\n");
      printf("    Get the bootloader version and the Read Protection status of the Flash memory\n");
      printf("  -i\n");
      printf("    Get the chip ID\n");
      printf("  -r\n");
      printf("    Read memory\n");
      printf("  -s\n");
      printf("    Starts user applicaion code\n");
      printf("  -w\n");
      printf("    Write memory\n");
      printf("  -e\n");
      printf("    Erase momery\n");
      printf("  -p\n");
      printf("    Write Protect\n");
      printf("  -u\n");
      printf("    Write Unprotect\n");
    }
  }
  
  printf("End\n");
	return 0;
}

