/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_isr.h
* @author Emanuel Foster, Lucien Zuercher
* @date 15. Sep. 2014
* @brief Setzt und enthaelt ISR funktionen.
*
* Hier sind die ISR funktionen definiert und werden gesetzt.
*/
#ifndef _CO_ISR_H
# define _CO_ISR_H

/****************************************************************************
* Includes
****************************************************************************/

#include "../headers/co.h"

/****************************************************************************
* Konstanten
****************************************************************************/

/**
 * Timer typ einstellen
 */
#define CO_USEDTIMER TOIE1

/**
 * Geschwindigkeit des Timers anpassen
 */
#define CO_TIMERSPEED 1

/****************************************************************************
* Funktionen
****************************************************************************/

/**
 * initialisiert die Interrupt funktion, die fuer den lese und schreibe Zyklus genutzt wird.
 */
void f_co_initializeOverflowInterrupt();

/**
 * Timer1 Funktion, sendet im sende Mod das Byte oder
 * liest im empfang Mode die gesendeten Bytes
 */
void f_co_isr_timer1OvfVect();

/**
 * Interrupt bei empfangen einer aenderung auf dem gesetzten Empfangsport
 * genutzt um synchrones Lesen und schreiben zu ermöglichen. Synchronisieren
 * mit den Verbundenen Controller.
 */
void f_co_isr_int0Vect();

/****************************************************************************
* ISR
****************************************************************************/

// ISR used to catch message
ISR(INT0_vect)
{
	f_co_isr_int0Vect();
}

/**
 * Haupttimer gesetzt zum effizient senden und empfangen der Nachrichten
 */
ISR(TIMER1_OVF_vect)
{	
	f_co_isr_timer1OvfVect();
}

#endif /* _CO_ISR_H */

/****************************************************************************/