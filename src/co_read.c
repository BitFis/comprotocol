/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_read.c
* @author Emanuel Foster, Lucien Zuercher
* @date 3. Sep. 2014
* @brief Funktionen und Hilfsfunktionen zum Lesen einer Verbindung.
*
* Die hier vorhandenen Funktionen werden genutzt um eine Verbindung
* gebgebenen Port abzuhoeren. Bit für Bit werden diese Informationen
* nach einem gegebenen Tackt eingelesen und in auf Cache geschrieben.
*/

#include "../headers/co.h"

void f_co_processbyte(uint8_t byte)
{
	if(ISSET_BIT(co_status, MESSAGEREADING))
	{
		// Byte im Buffer abspeichern
		f_co_MsgCache_append(co_byte);
		
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