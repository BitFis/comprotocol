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
 * genutzt fuer die checksumme
 */
extern uint8_t checksum;

/**
 * enthealt das zud endende byte
 */
volatile uint8_t bSending;

/**
 * Buffer fuer die Nachricht, die uebertragen wird
 */
volatile uint8_t sSendByte[CO_MAXMESSAGEBUFFERSIZE];

/**
 * Zeigt auf das zu sendende Byte
 */
volatile uint8_t cPointerSendByte;

/**
 * Enthaelt die Position des derzeitigen buffers
 */
volatile uint8_t cPositionBit;

/**
 * groesse des packetes
 */
volatile uint8_t cPaketGroesse;

/****************************************************************************
* Enumirationen & Strukturen
****************************************************************************/


/****************************************************************************
* Funktionen
****************************************************************************/

/**
 * Sendet einen Text
 * @param p_sText Zu sendender Text
 */
void f_co_write_Text(char* p_sText);

/**
 * Bei jedem 2. Interrupt ein Bit senden
 */
void f_co_write_Send();

/**
 * Sendet einen Command
 * @param p_cCommand Zu sendender Command
 */
void f_co_write_Command(unsigned char p_cCommand);

/**
 * Sendet den Header einer neuen übetragung: start-byte, destination-id, source-id
 * @param destination_id Destioation-ID
 */
void f_co_write_ProtocollHeader(char destination_id);

/**
 * Sendet ein Byte
 * @param p_cByte Zu sendendes Byte
 * @return Wurde Byte ohne Fehler gesendet 0 = Fehler, 1 = Kein Fehler
 */
bool f_co_write_Byte(char p_cByte);

/**
 * Kontrolliert ob das gesendete Bit ohne Kollision gesendet wurde
 * @param p_cBitControll Gesendetes Bit welche Kontrolliert werden soll
 * @return Wurde Byte ohne Fehler gesendet 0 = Fehler, 1 = Kein Fehler
 */
bool f_co_write_Controll(char p_cBitControll);

#endif /* _CO_WRITE_H */

/****************************************************************************/