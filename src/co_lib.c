/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_lib.c
* @author Emanuel Foster, Lucien Zuercher
* @date 3. Sep. 2014
* @brief Enthaelt Hilfsfunktionen und Emuriationen
*
* Dieses Dokument enthaelt Funktionen und Definitionen von Makros die auch
* ausserhalb dieser Bibliothek genutzt werden können.
*/

/************************************************************************/

#include "../headers/co_lib.h"

/************************************************************************/

uint8_t* co_MsgCache_cache;
uint8_t co_MsgCache_position;

/************************************************************************/

void f_co_MsgCache_release()
{
	free(co_MsgCache_cache);
}

/************************************************************************/

void f_co_MsgCache_init()
{
	co_MsgCache_cache = malloc(CO_MAXMESSAGEBUFFER * sizeof(uint8_t));
	co_MsgCache_position = 0;
}

/************************************************************************/

void f_co_MsgCache_append(uint8_t value)
{
	if(co_MsgCache_position < CO_MAXMESSAGEBUFFER)
		co_MsgCache_cache[co_MsgCache_position++] = value;
}

/************************************************************************/

void f_co_MsgCache_setPosition(uint8_t position)
{
	position = position < CO_MAXMESSAGEBUFFER ? position : CO_MAXMESSAGEBUFFER - 1;
}

/************************************************************************/

void f_co_MsgCache_reset()
{
	co_MsgCache_position = 0;
}

/************************************************************************/

uint8_t* f_co_MsgCache_getStart()
{
	return co_MsgCache_cache;
}

/************************************************************************/