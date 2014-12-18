/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_lib.h
* @author Emanuel Foster, Lucien Zuercher
* @date 3. Sep. 2014
* @brief Enthaelt Hilfsfunktionen und Emuriationen
*
* Dieses Dokument enthaelt Funktionen und Definitionen von Makros die auch
* ausserhalb dieser Bibliothek genutzt werden können.
*/

#ifndef _CO_LIB_H
#define _CO_LIB_H

/****************************************************************************
* Includes
****************************************************************************/

/** Extern **/
#include <inttypes.h>

/** Internal **/

/****************************************************************************
* Makros
****************************************************************************/

/** Bit Operationen **/

/**
 * setzt das bit auf 1
 * @param var Byte bei dem der Wert gesetzt wird
 * @param bit Die nummer des bits (0-7)
 */
#define SET_BIT(var, bit) ((var) |= (1 << bit))

/**
 * setzt das bit auf 0
 * @param var Byte bei dem der Wert gesetzt wird
 * @param bit Die nummer des bits (0-7)
 */
#define CLEAR_BIT(var, bit) ((var) &= ~(1 << bit))

/**
 * kehrt das bit
 * @param var Byte bei dem der Wert gesetzt wird
 * @param bit Die nummer des bits (0-7)
 */
#define TOGGLE_BIT(var, bit) ((var) ^= (1 << bit))

/**
 * kontrolliert ob Bit 1 ist
 * @param var Byte bei dem der Wert kontrolliert wird
 * @param bit Die nummer des bits (0-7)
 * @return bit ist 1?
 */
#define ISSET_BIT(var, bit) ((var) & (1 << bit))
/**
 * kontrolliert ob Bit 0 ist
 * @param var Byte bei dem der Wert kontrolliert wird
 * @param bit Die nummer des bits (0-7)
 * @return bit ist 0?
 */
#define ISCLEAR_BIT(var, bit) (!ISSET_BIT(var, bit))

/****************************************************************************
* Konstanten
****************************************************************************/

/**
 * Definiert den maximalen Speicher in Byte, den der Messagebuffer
 * ausnutzen darf.
 */
#define CO_MAXMESSAGEBUFFERSIZE 128

/****************************************************************************
* Enumirationen & Strukturen
****************************************************************************/

/** Bool definieren **/

/**
 * Definiert den bool type (true / false) moeglich
 */
typedef uint8_t bool;

/**
 * Richtig
 */
#define true 1

/**
 * Falsch
 */
#define false 0

/****************************************************************************
* Globale Variablen
****************************************************************************/

/**
 * Zeigt auf den start des Messagebuffers
 */
extern uint8_t* co_MsgCache_cache;

/**
 * Derzeitige Position des Zeigers der Messagebuffers
 */
extern uint8_t co_MsgCache_position;

/****************************************************************************
* Funktionen
****************************************************************************/

/**
 * Speicher, der fuer die Message genutzt wurde, wieder freigeben
 */
void f_co_MsgCache_release();

/**
 * Erstellt den Speicher fuer die Message
 */
void f_co_MsgCache_init();

/**
 * Fuegt ein gegebenes Byte nach dem Zeiger ein, wenn
 * der maximale Speicher nicht ueberschritten ist
 * @param value Das Byte welches hinzugefuegt wurde
 */
uint8_t f_co_MsgCache_append(uint8_t value);

/**
 * Den Zeiger an eine beliebige Position setzten.
 * Muss kleiner als Maximal moegliche Speichergroesse 
 * und groesser als 0 sein.
 * @param position Neue Position des Zeigers
 */
void f_co_MsgCache_setPosition(uint8_t position);

/**
 * Auslesen der derzeitg gelsenen Position
 * @return derzeitige Position des Buffers 
 */
void f_co_MsgCache_getPosition();

/**
 * Zeiger auf den Start setzten
 */
void f_co_MsgCache_reset();

/**
 * Gibt die Anfangsposition des Messagespeichers zurueck
 */
uint8_t* f_co_MsgCache_getStart();

#endif /* _CO_LIB_H */

/****************************************************************************/