/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_read.h
* @author Emanuel Foster, Lucien Zuercher
* @date 3. Sep. 2014
* @brief Funktionen und Hilfsfunktionen zum Lesen einer Verbindung.
*
* Die hier vorhandenen Funktionen werden genutzt um eine Verbindung
* gebgebenen Port abzuhoeren. Bit für Bit werden diese Informationen
* nach einem gegebenen Tackt eingelesen und in auf Cache geschrieben.
*/

#ifndef _CO_READ_H
#define _CO_READ_H

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

enum CO_READ_STATUS{
	CO_READ_WAITING = 0,
	CO_READ_HEADER = 1,
	CO_READ_MESSAGE = 2,
	CO_READ_CHECKSUM = 3
};

/****************************************************************************
* Funktionen
****************************************************************************/

/**
 * bit lesen
 * @param byte byte eingelesen
 */
void f_co_readbit(uint8_t byte);

/**
 * byte bearbeiten und dem buffer hinzufuegen
 * @param byte Das eingelesene byte
 */
void f_co_processbyte(uint8_t byte);

void f_co_processHeader();

void f_co_checkValid(uint8_t byte);

void f_co_processChecksum();

#endif /* _CO_WRITE_H */

/****************************************************************************/