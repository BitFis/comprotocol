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
* Funktionen
****************************************************************************/



#endif /* _CO_LIB_H */

/****************************************************************************/