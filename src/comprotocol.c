/****************************************************************************
 * Copyright (C) 2012 by Matteo Franchin                                    *
 *                                                                          *
 * This file is part of Box.                                                *
 *                                                                          *
 *   Box is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Box is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/**
 * @file main.c
 * @author My Self
 * @date 9 Sep 2012
 * @brief File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 */

#include <avr/io.h>

//#include "co.h"
#include "co.h"

int main(void)
{
	// testing code
	DDRB=0xff;
	DDRD=0x00;
	
	//f_co_initializeOverflowInterrupt();
	
	DDRB=0xff;
	
	//SET_BIT(co_status, READING);
	
	f_co_initializeOverflowInterrupt();
	
	f_co_init_waitmode();
	
//	f_co_SendText("Hello");
	
    while(1)
    {
		f_co_update();
		
		PORTB = ~co_debug_var;
    }
}