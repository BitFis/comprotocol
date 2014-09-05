/****************************************************************************
 * Copyright (C) 2012 by Emanuel Forster / Lucien Zuercher                   *
 *                                                                          *
 * License MIT				                                                *
 ****************************************************************************/

/**
 * @file co.h
 * @author Emanuel Forster / Lucien Zuercher
 * @date 8.8.2014
 * @brief Funktionslibrary fuer das comprotocol
 *
 * Enthaelt die definitionen und Beschreibungen des files co.c
 */


#ifndef CO_H_
#define CO_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>

/**
 * used to safe byte while reading
 */
volatile extern uint8_t co_byte;
/**
 * status of while reading
 */
volatile extern uint8_t co_status;

/**
 * contains current position in message buffer
 */
extern uint8_t *co_cachpos;

extern uint8_t co_curinput; // current input remove later
// REMOVE later used to output switch
extern uint8_t co_debug_var;

/**
 * Temporary Variable can be used everywhere
 */
extern uint8_t tmp;

//////////////////////////////////////////////////////////////////////////
// Bit operations
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

/**
 * @brief Netzwerk Status
 *
 * Enthaelt den Netzwerkstatus. Damit erkennt man ob gelesen oder
 * geschrieben wird und welchen process durchgefuehrt wird.
 * Ebenso ob die Message Fertig gelesen/ geschrieben wurde.
 */
enum 
{
	READING,
	PROCESS,
	LASTREADBIT,
	DELAY,
	MESSAGEREADING,
	MESSAGEREAD,
	ERROR
};

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

void f_co_inputchange();
/**
 * initialisiert die Interrupt funktion, die fuer den lese und schreibe Zyklus genutzt wird.
 */
void f_co_initializeOverflowInterrupt();
/**
 * initialisiert den wartemodus. Heisst es wird auf eine Aenderung gewartet auf PIN 2 des PORTS B
 */
void f_co_init_waitmode();
/**
 * bit lesen
 */
void f_co_readbit();
/**
 * byte bearbeiten und dem buffer hinzufuegen
 * @param byte Das eingelesene byte
 */
void f_co_processbyte(uint8_t byte);
/** 
 * update Funktion, die immer mindestens einmal im loop augerufen werden sollte, 
 * damit die eingelesenen Informationen bearbeitet werden koennen.
 */
void f_co_update();
/**
 * Sendet einen Text
 */
void f_co_SendText(char* p_cText);
/**
 Sendet einen Command
 */
void f_co_SendCommand(unsigned char p_cCommand){
/**
 * Sendet den Header einer neuen übetragung: start-byte, destination-id, source-id
 */
void f_co_SendProtocollHeader(char destination_id)
/**
 * Sendet ein Byte
 */
bool f_co_SendByte(char p_cByte);
/**
 * Sendet ein Bit
 */
void f_co_SendBit(char p_cBit);
/**
 * Kontrolliert ob das gesendete Bit ohne Kollision gesendet wurde
 */
bool f_co_ControllSend(char p_cBitControll);
#endif /* CO_H_ */
