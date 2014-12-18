/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_document.h
* @author Emanuel Foster, Lucien Zuercher
* @date 1. Jan. 2014
* @brief Laedt alle benoetigten Abhaengigkeiten.
*
* Laedt alle benoetigten Abhaengigkeiten. Dazu gehoeren config, lib, 
* read, write, io, isr
* 
*/

#ifndef CO_H_
#define CO_H_

/****************************************************************************
* Includes
****************************************************************************/

/** Extern **/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>

/** Intern **/
#include "co_config.h"
#include "co_lib.h"
#include "co_isr.h"
#include "co_read.h"
#include "co_write.h"

/****************************************************************************
* Makros
****************************************************************************/

/****************************************************************************
* Enumirationen & Strukturen
****************************************************************************/

/** Netzstatus definieren **/

/**
 * @brief Netzwerk Status
 *
 * Enthaelt den Netzwerkstatus. Damit erkennt man ob gelesen oder
 * geschrieben wird und welchen process durchgefuehrt wird.
 * Ebenso ob die Message Fertig gelesen/ geschrieben wurde.
 */
enum 
{
	READING, /**< Information ob zurzeit geschrieben wird */
	HEADERPROCESSED, /**< Byte fertig gelesen. */
	LASTREADBIT, /**< Zuletzt gelesenes Bit */
	DELAY, /**< Aussetzen um jeden zweiten "clock" lesen */
	MESSAGEREADING, /**< Message lesen */
	MESSAGEREAD, /**< Message gelesen  */
	ERROR /**< Fehler */
};

/****************************************************************************
* Konstanten
****************************************************************************/

/* Programmierer Einstellungen */

/**
 * Identifikationsbyte
 */
#define CO_MESSAGEIDENTIFIER 0b10101010

/****************************************************************************
* Globale Variablen
****************************************************************************/

/**
 * Speichert Byte fuer das Lesen oder das Schreiben
 */
volatile extern uint8_t co_byte;

/**
 * Status vom Lesen oder Schreiben
 */
volatile extern uint8_t co_status;

/** Buffer Variablen **/

/**
 * Temporaere Variable, kann ueberall benutzt werden
 */
extern uint8_t tmp;

/** 
 * Temporaere Variable fuer Release entfernen - debug fuer pins
 */
extern uint8_t co_debug_var;


/****************************************************************************
* Funktionen
****************************************************************************/

#endif /* CO_H_ */

/****************************************************************************/
