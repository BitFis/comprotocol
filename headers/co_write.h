/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_write.h
* @author Emanuel Foster, Lucien Zuercher
* @date 3. Sep. 2014
* @brief Enthaelt Funktionen zum Absenden einer Nachricht
*
* Dieses Dokument enthaelt Funktionen und Hilfsfunktionen um eine Nachricht
* nach dem <i>comprotocol</i> Protokoll abzusenden. Die Bits werden
* Interruptweise nach einem definiertem Timer übertragen.
*/

#ifndef _CO_WRITE_H
# define _CO_WRITE_H

/****************************************************************************
* Includes
****************************************************************************/

# include "co.h"

/****************************************************************************
* Globale Variablen
****************************************************************************/

/**
 * Temporary Variable can be used everywhere
 */
extern uint8_t tmp;

extern uint8_t checksum;
volatile extern uint8_t bSending;
volatile extern uint8_t bSend;

/****************************************************************************
* Enumirationen & Strukturen
****************************************************************************/


/****************************************************************************
* Funktionen
****************************************************************************/

/**
 * Sendet den Header einer neuen übetragung: start-byte, destination-id, source-id
 * @param Destioation-ID
 */
void f_co_SendProtocollHeader(char destination_id);

/**
 * Sendet ein Byte
 * @param Zu sendendes Byte
 * @return Wurde Byte ohne Fehler gesendet 0 = Fehler, 1 = Kein Fehler
 */
bool f_co_SendByte(char p_cByte);

/**
 * Sendet ein Bit
 * @param Zu sendendes Bit
 */
void f_co_SendBit(char p_cBit);

/**
 * Kontrolliert ob das gesendete Bit ohne Kollision gesendet wurde
 * @param Gesendetes Bit welche Kontrolliert werden soll
 * @return Wurde Byte ohne Fehler gesendet 0 = Fehler, 1 = Kein Fehler
 */
bool f_co_ControllSend(char p_cBitControll);

#endif /* _CO_WRITE_H */

/****************************************************************************/