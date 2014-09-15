/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_read.c
* @author Emanuel Foster, Lucien Zuercher
* @date 3. Sep. 2014
* @brief Funktionen und Hilfsfunktionen zum Lesen einer Verbindung.
*
* Die hier vorhandenen Funktionen werden genutzt um eine Verbindung
* gebgebenen Port abzuhoeren. Bit für Bit werden diese Informationen
* nach einem gegebenen Tackt eingelesen und in auf Cache geschrieben.
*/

#include "../headers/co.h"