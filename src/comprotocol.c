/*
 * comprotocol.c
 *
 * Created: 2/07/2014 11:11:58 PM
 *  Author: Lucien
 */ 


#include <avr/io.h>

int main(void)
{
	// testing code
	DDRA=0xf0
	
    while(1)
    {
		PORTA=0xff;
    }
}