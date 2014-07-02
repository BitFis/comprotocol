/*
 * comprotocol.c
 *
 * Created: 2/07/2014 11:11:58 PM
 *  Author: Lucien
 */ 


#include <avr/io.h>
#include "co.h"

int main(void)
{
	// testing code
	DDRB=0xff;
	DDRA=0x00;
	
    while(1)
    {
		f_co_switchinput();
    }
}