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

/** NOT IMPLEMENTET */
uint8_t* f_co_GetMessage();
/** NOT IMPLEMENTET */
uint8_t f_co_GetCommand();
/** NOT IMPLEMENTET **/
uint8_t f_co_GetKey();

#endif /* _CO_WRITE_H */

/****************************************************************************/