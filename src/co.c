/****************************************************************************
 * Copyright (C) 2014 by Emanuel Foster / Lucien Zürcher                    *
 *                                                                          *
 * License MIT				                                                *
 ****************************************************************************/

/**
 * @file co.c
 * @author Emanuel Foster / Lucien Zürcher
 * @date 8.8.2014
 * @brief Funktionslibrary für das comprotocol
 *
 * Enthält die Funktionen von co.h.
 * Eine Dokumentation aller funktionen ist im co.h zu finden
 */
 
/************************************************************************/

#include "../headers/co.h"

/************************************************************************/
/* status Variablen														*/
/************************************************************************/
volatile uint8_t co_byte = 0x00;
volatile uint8_t co_status = 0x00;

/************************************************************************/
/* Send Variablen														*/
/************************************************************************/
uint8_t checksum;
volatile uint8_t bSending;
volatile uint8_t sSendByte[CO_MAXMESSAGEBUFFERSIZE];
volatile uint8_t cPointerSendByte;
volatile uint8_t cPositionBit;
volatile uint8_t cPaketGroesse;

/************************************************************************/
/* globale Variablen													*/
/************************************************************************/
volatile uint8_t tmp;

uint8_t co_debug_var = 0;

uint8_t co_slower = 0x00;

/************************************************************************/