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
 
#include "../headers/co.h"

//////////////////////////////////////////////////////////////////////////
uint8_t tmp;

volatile uint8_t co_byte = 0x00;
volatile uint8_t co_status = 0x00;


uint8_t checksum;
volatile uint8_t bSending;
volatile uint8_t bSend;


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

void f_co_processbyte(uint8_t byte)
{
	if(ISSET_BIT(co_status, MESSAGEREADING))
	{
		// Byte im Buffer abspeichern
		
		// TMP REMOVE
		
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


void f_co_SendText(char* p_sText){
  
    f_co_SendProtocollHeader(2);
  
    char nLength = strlen(p_sText);
    char cCommand = (1<<7) & nLength;
	//Command and L�nge senden
	f_co_SendByte(cCommand);
	
    char* Text_save = p_sText;

    bool controll = true;
    //Solange bis kein Zeichen mehr vorhanden
    while(*p_sText != '\0' && controll){
        controll = f_co_SendByte(*(p_sText));
        p_sText++;
    }
	if(controll)
	{
		f_co_SendByte(checksum);
	}
    //Falls controll-bit != gesendetes-bit
    else
	{
        //Eigene ID als ms warten
        _delay_ms(10);
        //Text erneut senden
        f_co_SendText(Text_save);           
    }	
}

void f_co_SendCommand(unsigned char p_cCommand){
  
    f_co_SendProtocollHeader(2);
    bool controll = f_co_SendByte(p_cCommand);
    
	if(controll)
	{
		f_co_SendByte(checksum);
	}
    //Falls controll-bit != gesendetes-bit
    else
	{
        //Eigene ID als ms warten
        _delay_ms(10);
        //Text erneut senden
        f_co_SendCommand(p_cCommand);           
    }	
}

bool f_co_SendByte(char p_cByte){
	//Checksum XOR Verkn�fen
	checksum ^= p_cByte;
    //Senden Anfangen mit letztem Bit
    char cFilter = 0b10000000;
    //Solange Filter > 0 (Schleife 8-mal durchlaufen)
    while(cFilter != 0){
        //Zu sendendes Bit herausfiltern
        char cbit = p_cByte & cFilter;
        //gefiltertes Bit senden
        f_co_SendBit(cbit);
        //warten
        cFilter >>= 1;
    }
    return true;
}

void f_co_SendBit(char p_cBit){
  
	// bSending -> 1 = sendbereit, 0 = gesendet
    //Warten Bis vorheriges Bit gesendet wurde
    while(bSending != 0)
    {
    }
	
    bSend = p_cBit;
    bSending = 1;
}

bool f_co_ControllSend(char p_cBitControll){
    //Bit einlesen
    DDRA = 0xFE;
    char bit_read = ~PINA;
  
    if(p_cBitControll == 0){
        if(bit_read == 0){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if(bit_read == 1){
            return true;
        }
        else{
            return false;
        }
    }
}

void f_co_SendProtocollHeader(char destination_id){
  
	DDRA = 0x80;
    DDRC = 0x01;

	checksum = 0;

	char source_id = ID;
  
    bSending = 1;
    //4-mal 1/0 senden f�r Beginn
	f_co_SendByte(0b10101010);
	
	//HEADER Daten senden
    f_co_SendByte(destination_id);
    f_co_SendByte(source_id);
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
		// read information
		if((~PIND) & (1<<CO_PINREADING))
			SET_BIT(co_status, LASTREADBIT);
		else
			CLEAR_BIT(co_status, LASTREADBIT);
	//	co_status = ( (((~PIND) & (1<<CO_PINREADING)) >> CO_PINREADING) << LASTREADBIT);
		SET_BIT(co_status, PROCESS);
	}
	else
	{	
		/* Interrupt Aktion alle
		(1000000/1024)/256 Hz = 3.814697 Hz
		bzw.
		1/3.814697 s = 262.144 ms  
		*/
		if(bSending == 1)
		{
			bSending = 2;
		}
		else if(bSending == 2){
			
		
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
	   //     sendA = 128;
			sendC = 1;
		}
	    PORTA = ~sendA;
		PORTC = ~sendC;
	
		bSending = 0;
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
