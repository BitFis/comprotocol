/****************************************************************************
 * Copyright (C) 2014 by Emanuel Forster / Lucien Zürcher                   *
 *                                                                          *
 * License MIT				                                                *
 ****************************************************************************/

/**
 * @file co.h
 * @author Emanuel Forster / Lucien Zürcher
 * @date 8.8.2014
 * @brief Funktionslibrary für das comprotocol
 *
 * Enthält die Funktionen von co.h.
 * Eine Dokumentation aller funktionen ist im co.h zu finden
 */
 
#include "co.h"

//////////////////////////////////////////////////////////////////////////
uint8_t tmp;

volatile uint8_t co_byte = 0x00;
volatile uint8_t co_status = 0x00;




//////////////////////////////////////////////////////////////////////////
//uint8_t co_byte = 0x01;
//uint8_t co_status = 0x00;
uint8_t *co_cachpos = 0;

uint8_t co_debug_var = 0;

uint8_t co_slower = 0x00;

uint8_t co_tmp_status=0x00;
uint8_t co_curinput = 0x00;


/************************************************************************/
/*                                                                      */
/************************************************************************/
void f_co_initializeOverflowInterrupt(){
	// Timer 0 konfigurieren
	TCCR1B = CO_TIMERSPEED; //(1<<CS02); // Prescaler 1024
	
	// Overflow Interrupt erlauben
	TIMSK |= (1<<CO_USEDTIMER);	
	
	// Global Interrupts aktivieren
	sei();
}

/*
 * 
 */
void f_co_init_waitmode()
{
	// I-Flag temporaer speichern
	tmp = SREG;
	cli();
	
	// setzten des INT0 um bei einer Aenderung das
	// lesen zu beginnen
	// INT0 (PD2) auf fallende flanke reagieren
	MCUCR |= (1 << ISC01);
	MCUCR &= ~(1 << ISC00);

	GICR |= (1 << INT0);
	
	// timer fuers erste deaktivieren, da noch keine Nachricht erhalten
	TIMSK &= ~(1 << CO_USEDTIMER);
	
	SREG = tmp;
}

void f_co_processbyte(uint8_t byte)
{
	if(ISSET_BIT(co_status, MESSAGEREADING))
	{
		// Byte im Buffer abspeichern	
	}
	else
	{
		// Message kontrollieren
		if(byte == CO_MESSAGEIDENTIFIER)
			SET_BIT(co_status, MESSAGEREADING);
		else
			co_status = (1 << ERROR);
	}
	
	// zurueck zum wartemodus wenn ein error erkannt wurde
	if(ISSET_BIT(co_status, ERROR))
	{
		CLEAR_BIT(co_status, ERROR);
		f_co_init_waitmode();
	}
}

void f_co_readbit()
{
	// check if whole byte is read
	tmp = co_byte & (1 << 7);

	co_byte = co_byte << 1;
	co_byte |= ((co_status & (1 << LASTREADBIT)) >> LASTREADBIT);
	
	if(tmp)
	{
		f_co_processbyte(co_byte);
		co_byte = 0x01;
		co_debug_var = 0xff;
	}
	else
		co_debug_var = co_byte;
}


void f_co_update()
{
	if(ISSET_BIT(co_status, PROCESS))
	{
		if(ISCLEAR_BIT(co_status, DELAY))
		{
			f_co_readbit();
		}
		
		TOGGLE_BIT(co_status, DELAY);
		CLEAR_BIT(co_status, PROCESS);
	}
}

// TMP function remove later used to add something to the debug
void f_co_adddebug(char debugvalue, char bitpos)
{
	co_debug_var=(debugvalue & 1 << bitpos);
}
f_co_outputDebug()
{
	PORTB=co_debug_var;
}

//////////////////////////////////////////////////////////////////////////

// ISR used to catch message
ISR(INT0_vect)
{
	GICR &= (1 << INT0);
	TIMSK |= (1 << CO_USEDTIMER);
	SET_BIT(co_status, DELAY);
}

ISR(TIMER1_OVF_vect)
{
	if((~PIND) & (1<<CO_PINREADING))
		SET_BIT(co_status, LASTREADBIT);
	else
		CLEAR_BIT(co_status, LASTREADBIT);
//	co_status = ( (((~PIND) & (1<<CO_PINREADING)) >> CO_PINREADING) << LASTREADBIT);
	SET_BIT(co_status, PROCESS);
}

/*
Der Overflow Interrupt Handler
wird aufgerufen, wenn TCNT0 von
255 auf 0 wechselt (256 Schritte),
d.h. ca. alle 2 ms
*
#ifndef TIMER0_OVF_vect
// Für ältere WinAVR Versionen z.B. WinAVR-20071221 
#define TIMER0_OVF_vect TIMER0_OVF0_vect
#endif

ISR (INT0_vect)
{
	PORTB = 0xff;
	co_status = ~co_status;
}

ISR (TIMER0_OVF_vect)
{
/*	co_slower += 1;
	if(co_slower == 0x16)
	{
		f_co_readbit(PIND);
		
		co_slower =0;
	}
	
    /* Interrupt Aktion alle
    (1000000/1024)/256 Hz = 3.814697 Hz
    bzw.
    1/3.814697 s = 262.144 ms  
    *
	char sendA;
	char sendC;
    //Falls Bit = 0 ...
    if(bSend == 0)
    {
        //... sende 0
		sendA = 0;
		sendC = 0;
    }
    else{
        //... sende 1
        sendA = 128;
		sendC = 1;
    }
    PORTA = ~sendA;
    PORTC = ~sendC;
	
	bSending = false;*
}*/
