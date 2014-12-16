/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_io.c
* @author Emanuel Foster, Lucien Zuercher
* @date 3. Sep. 2014
* @brief Enthaelt Funktionen zum Absenden einer Nachricht
*
* Dieses Dokument enthaelt Funktionen und Hilfsfunktionen um eine Nachricht
* nach dem <i>comprotocol</i> Protokoll abzusenden. Die Bits werden
* Interruptweise nach einem definiertem Timer übertragen.
*/

/************************************************************************/

#include "../headers/co_io.h"

/************************************************************************/

void f_co_InitProtocol() {
	
	f_co_initializeOverflowInterrupt();
	
	// temporaer statisch senden oder schreiben
	if(!WRITE)
		f_co_init_waitmode();
		
	f_co_MsgCache_init();
}

/************************************************************************/

uint8_t* f_co_GetMessage()
{
	return (f_co_MsgCache_getStart() + sizeof(t_co_msg_header));
}

/************************************************************************/

uint8_t f_co_GetCommand()
{
	return (*((t_co_msg_header*)f_co_MsgCache_getStart())).Info;
}

/************************************************************************/

uint8_t f_co_GetKey()
{
	uint8_t tmp = (*((t_co_msg_header*)f_co_MsgCache_getStart())).Info;
	// Taste ist 0 wenn keine Taste empfangen wurde
	return (tmp & 0xf0) == 16 ? (tmp & 0x0f) : 0;
}

/************************************************************************/

void f_co_update()
{
	if(!WRITE) {
		f_co_read_update();
	}
}

/************************************************************************/