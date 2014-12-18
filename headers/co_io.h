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


/****************************************************************************
* Funktionen
****************************************************************************/

/**
 * gedrückte Taste senden
 * @param gedrückte Taste als Zahl von 0 - 15.
 */
void f_co_SendTaste(char p_sTaste);

/**
 * Sendet eine Charakterreihe, bis \0
 * @param text Pointer auf den ersten Charakter des zu sendenden Textes (max 255 Bytes)
 */
void f_co_SendText(char *text);

/**
 * Initialisieren des Protokolles
 */
void f_co_InitProtocol();

/**
 * Eingelesene Message holen
 * @return Zeiger auf den Anfang der Message
 */
uint8_t* f_co_GetMessage();

/**
 * Gibt den eingelesenen Befehl zurueck
 * @return Ungefilterter Befehl
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