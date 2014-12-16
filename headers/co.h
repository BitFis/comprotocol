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
* read, write
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
	PROCESS, /**< Byte fertig gelesen. */
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
 * Timer typ einstellen
 */
#define CO_USEDTIMER TOIE1

/**
 * Geschwindigkeit des Timers anpassen
 */
#define CO_TIMERSPEED 3

/**
 * Pin wo gelesen wird einstellen.
 * ! ACHTUNG !
 * nur pin 2/3 kann ein "listening handler" hinzugefuegt werden.
 */
#define CO_PINREADING 2

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
 * contains current position in message buffer
 */
extern uint8_t *co_cachpos;

extern uint8_t co_curinput; // current input remove later

/** 
 * Temporaere Variable fuer Release entfernen
 */
extern uint8_t co_debug_var;


/****************************************************************************
* Funktionen
****************************************************************************/

/**
 * gedrückte Taste senden
 * @param gedrückte Taste als Zahl von 0 - 15.
 */
void f_co_SendTaste(char p_sTaste);

/**
 * Byte zu String konvertieren
 * @param Byte welches konvertiert werden soll
 * @param Pointer in welche das Resultat geschrieben wird
 */
void f_co_ConvertByteToStr(char p_cByte, char *sResult);

/** NOT IMPLEMENTED */
void f_co_inputchange();

/**
 * initialisiert die Interrupt funktion, die fuer den lese und schreibe Zyklus genutzt wird.
 */
void f_co_initializeOverflowInterrupt();

/**
 * initialisiert den wartemodus. Heisst es wird auf eine Aenderung gewartet auf PIN 2 des PORTS B
 */
void f_co_init_waitmode();

#endif /* CO_H_ */

/****************************************************************************/