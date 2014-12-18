/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_isr.c
* @author Emanuel Foster, Lucien Zuercher
* @date 15. Sep. 2014
* @brief Enthaelt alle "Interrupt" Funktionen.
*
* Hier befindet sich die Logik der ISR Funktionen
*/

/************************************************************************/

#include "../headers/co_isr.h"

/************************************************************************/
/* f_co_initializeOverflowInterrupt()									*/
/************************************************************************/
void f_co_initializeOverflowInterrupt(){
	// Timer 0 konfigurieren
	TCCR1B = CO_TIMERSPEED; //(1<<CS02); // Prescaler 1024
	
	// Overflow Interrupt erlauben
	TIMSK |= (1<<CO_USEDTIMER);	
	
	// Global Interrupts aktivieren
	sei();
}

/************************************************************************/
/* f_co_isr_int0Vect()													*/
/************************************************************************/
void f_co_isr_int0Vect() {
	GICR &= (1 << INT0);
	TIMSK |= (1 << CO_USEDTIMER);
	SET_BIT(co_status, DELAY);
}

/************************************************************************/
/* f_co_isr_timer1OvfVect()												*/
/************************************************************************/
void f_co_isr_timer1OvfVect() {
	/* Interrupt Aktion alle
	(1000000/1024)/256 Hz = 3.814697 Hz
	bzw.
	1/3.814697 s = 262.144 ms  
	*/
	if(!WRITE)
	{
		if(ISCLEAR_BIT(co_status, DELAY))
		{
			// read information
			if((~PIND) & (1<<CO_PINREADING))
				f_co_readbit(1);
			else
				f_co_readbit(0);
		}
		
		TOGGLE_BIT(co_status, DELAY);
		
	//	co_status = ( (((~PIND) & (1<<CO_PINREADING)) >> CO_PINREADING) << LASTREADBIT);
	//	SET_BIT(co_status, PROCESS);
		
		// check if byte is read and save in cache if it is
	}
	else
	{	
		f_co_write_Send();
	}
}

/************************************************************************/