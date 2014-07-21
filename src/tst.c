/*
 * tst.c
 *
 * Created: 21/07/2014 8:29:36 PM
 *  Author: Lucien
 */ 

#include "tst.h"

int8_t var = 0x00;
volatile int8_t flag = 0x00;

void tst_func_blink()
{
	while(1)
	{
		_delay_ms(1000);
		
		PORTB = var = ~var;	
	}
}

void tst_func_interrupt()
{
	PORTB = flag;
}

void tst_func_interrupt_init()
{
	/*TCCR0 |= 0x05;
	TIMSK |= (1<<TOIE0);*/
	//TCCR0 |= 0x05;
	//TIMSK |= /*(1<<TOIE0) |*/ (1<<OCIE0);
	
	cli();
	
	MCUCR |= (1<<ISC01);
	MCUCR &= ~(1<<ISC00);
	
	GICR |= (1 << INT0);
	
	sei();
}
/*
ISR(INT0_vect)
{
	flag = ~flag;
}*/