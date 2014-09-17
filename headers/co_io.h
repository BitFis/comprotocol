/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_io.h
* @author Emanuel Foster, Lucien Zuercher
* @date 3. Sep. 2014
* @brief Enthaelt Funktionen zum Absenden einer Nachricht
*
* Dieses Dokument enthaelt Funktionen und Hilfsfunktionen um eine Nachricht
* nach dem <i>comprotocol</i> Protokoll abzusenden. Die Bits werden
* Interruptweise nach einem definiertem Timer übertragen.
*/

#ifndef _CO_WRITE_H
#define _CO_WRITE_H

/****************************************************************************
* Includes
****************************************************************************/

# include "co.h"

/****************************************************************************
* Makros
****************************************************************************/


/****************************************************************************
* Enumirationen & Strukturen
****************************************************************************/

/**
 * Protokol Header definition
 */
typedef struct {
	uint8_t Initialisation;	/**< Initialisierung */
	uint8_t Target;	/**< Ziel Addresse */
	uint8_t Source;	/**< Von Addresse */
	uint8_t Command; /**< Befehl- oder Textinformationen */
} co_type_header;

/****************************************************************************
* Funktionen
****************************************************************************/

/**
 * Initialisieren des Protokolles
 */
void f_co_InitProtocol();

/** Send Funktionen **/

/**
 * Sendet einen Text
 * @param Zu sendender Text
 */
void f_co_SendText(char* p_cText);

/**
 * Sendet einen Command
 * @param Zu sendender Command
 */
void f_co_SendCommand(unsigned char p_cCommand);

/** Lese Funktionen **/

/**
 * Eingelesene Message holen
 * @return Zeiger auf den Anfang der Message
 */
uint8_t* f_co_GetMessage();

/** NOT IMPLEMENTED */
bool f_co_MessageRead();

/**
 * Gibt den eingelesenen Befehl zurueck
 * @return Ungefiterter Befehl
 */
uint8_t f_co_GetCommand();

/**
 * Gibt den eingelesenen Tastencode zurueck wenn 
 * in nach dem Protokoll eine Taste empfangen wurde.
 * @return Tasten code
 */
uint8_t f_co_GetKey();

/** 
 * update Funktion, die immer mindestens einmal im loop augerufen werden sollte, 
 * damit die eingelesenen Informationen bearbeitet werden koennen.
 */
void f_co_update();

#endif /* _CO_WRITE_H */

/****************************************************************************/