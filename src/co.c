/****************************************************************************
 * Copyright (C) 2014 by Emanuel Foster / Lucien Zürcher                    *
 *                                                                          *
 * License MIT				                                                *
 ****************************************************************************/

/**
 * @file co.h
 * @author Emanuel Foster / Lucien Zürcher
 * @date 8.8.2014
 * @brief Funktionslibrary für das comprotocol
 *
 * Enthält die Funktionen von co.h.
 * Eine Dokumentation aller funktionen ist im co.h zu finden
 */
 
#include "../headers/co.h"

//////////////////////////////////////////////////////////////////////////
uint8_t tmp;

volatile uint8_t co_byte = 0x00;
volatile uint8_t co_status = 0x00;


uint8_t checksum;
volatile uint8_t bSending;
volatile uint8_t sSendByte[CO_MAXMESSAGEBUFFERSIZE];
volatile uint8_t cPointerSendByte;
volatile uint8_t cPositionBit;
volatile uint8_t cPaketGroesse;


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
	
	// co_byte wieder zuruecksetzen
	co_byte = 0x01;
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


void f_co_SendTaste(char p_sTaste)
{
	f_co_LCD_Init();
	char cCommand = 0b00010000 + p_sTaste;
	f_co_write_Command(cCommand);
	//Animation
	f_co_CURB_OFF();
	f_co_LCD_STR("sending ");
	while(bSending != 0)
	{
		for(char Count = 0; Count < 3; Count++)
		{
			char Count2 = 0;
			char cSavePositionBit = cPositionBit;
			while(cSavePositionBit > 0)
			{
				Count2++;
				cSavePositionBit = cSavePositionBit << 1;
			}
			char cProzentEnde = (cPointerSendByte * 8 + Count2) * 100 / (cPaketGroesse * 8);
			_delay_ms(2000);
			f_co_LCD_CHR('.');
			f_co_LCD_RAM(16);
			f_co_LCD_INT(cProzentEnde);
			f_co_LCD_CHR('%');
			f_co_LCD_RAM(9 + Count);
		}
		_delay_ms(2000);
		
		f_co_LCD_RAM(8);
		f_co_LCD_STR("   ");
		f_co_LCD_RAM(8);
	}
	f_co_LCD_CLR();
	f_co_LCD_STR("finish");
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
		/* Interrupt Aktion alle
		(1000000/1024)/256 Hz = 3.814697 Hz
		bzw.
		1/3.814697 s = 262.144 ms  
		*/
		//Nur bei jedem zweiten mal senden
		if(bSending == 1)
		{
			bSending = 2;
		}
		else if(bSending == 2)
		{
			bSending = 1;
			char sendD = sSendByte[cPointerSendByte];
			sendD = cPositionBit & sendD;
			cPositionBit = cPositionBit >> 1;
			//Prüfe ob Ende von Byte erreicht
			if(cPositionBit == 0)
			{
				cPointerSendByte++;
				cPositionBit = 0b10000000;
			}
			//Prüfe ob Ende erreicht
			if(cPointerSendByte == cPaketGroesse)
			{
				bSending = 0;
			}
			//Falls Bit != 0 ...
			if(sendD != 0)
			{
				//Auf PIN 2 asugeben
				sendD = 0b00000100;
			}
			PORTD = ~sendD;
		}
	}

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
