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

/************************************************************************/
/* f_co_processbyte(byte)                                               */
/************************************************************************/
void f_co_processbyte(bool byte)
{
}

/************************************************************************/
/* f_co_processHeader()                                                   */
/************************************************************************/
void f_co_processHeader() {
	SET_BIT(co_status, HEADERPROCESSED); 
//	(<>*f_co_MsgCache_append(co_byte));
}

/************************************************************************/
/* f_co_resetReader()                                                 */
/************************************************************************/
void f_co_resetReader() {
	co_status = 0x00;
}

/************************************************************************/
/* f_co_read_update()                                                   */
/************************************************************************/
void f_co_read_update() {
	if(co_MsgCache_position >= CO_READ_HEADERSIZE ){
		f_co_processHeader();
	}else if(co_MsgCache_position >= co_read_msglength){
	//	SET_BIT(co_status, )
	}
	co_debug_var = co_MsgCache_position;
}

/************************************************************************/
/* f_co_readbit(byte)                                                   */
/************************************************************************/
void f_co_readbit(bool bit)
{
	bool tmp = co_byte & (1 << 7);
	
	co_byte = co_byte << 1;
	co_byte |= bit;
	
	// check if message is real
	if(ISCLEAR_BIT(co_status, MESSAGEREADING))
	{
		if(CO_MESSAGEIDENTIFIER == co_byte)
		{
			SET_BIT(co_status, MESSAGEREADING);
			f_co_MsgCache_setPosition(0);
			tmp = 1;
		}
	}
	
	// reads byte
	if(ISSET_BIT(co_status, MESSAGEREADING) && tmp)
	{
		// ganzes byte gelesen
		f_co_processbyte(co_byte);
		co_byte = 0x01;
	}
	
	// information abspeichern fuer status
	if(bit)
		SET_BIT(co_status, LASTREADBIT);
	else
		CLEAR_BIT(co_status, LASTREADBIT);
}
