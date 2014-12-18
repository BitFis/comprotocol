/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_io.c
* @author Emanuel Foster, Lucien Zuercher
* @date 3. Sep. 2014
* @brief Enthaelt Funktionen zum Absenden einer Nachricht
*
* Dieses Dokument enthaelt Funktionen und Hilfsfunktionen um eine Nachricht
* nach dem <i>comprotocol</i> Protokoll abzusenden. Die Bits werden
* Interruptweise nach einem definiertem Timer übertragen.
*/

/************************************************************************/

#include "../headers/co_io.h"

/************************************************************************/
/* f_co_InitProtocol()													*/
/************************************************************************/
void f_co_InitProtocol() {
	
	f_co_initializeOverflowInterrupt();
	
	// temporaer statisch senden oder schreiben
	if(!WRITE)
		f_co_init_waitmode();
		
	f_co_MsgCache_init();
}

/************************************************************************/
/* f_co_GetMessage()													*/
/************************************************************************/
uint8_t* f_co_GetMessage()
{
	return (f_co_MsgCache_getStart() + sizeof(t_co_msg_header));
}

/************************************************************************/
/* f_co_GetCommand()													*/
/************************************************************************/
uint8_t f_co_GetCommand()
{
	return ((t_co_msg_header*)f_co_MsgCache_getStart())->Info;
}

/************************************************************************/
/* f_co_GetKey()														*/
/************************************************************************/
uint8_t f_co_GetKey()
{
	uint8_t tmp = ((t_co_msg_header*)f_co_MsgCache_getStart())->Info;
	// Taste ist 0 wenn keine Taste empfangen wurde
	return (tmp & 0xf0) == 16 ? (tmp & 0x0f) : 0;
}

/************************************************************************/
/* f_co_update()														*/
/************************************************************************/
void f_co_update()
{
	if(!WRITE) {
		f_co_read_update();
	}
}

/************************************************************************/
/* f_co_SendText(string)														*/
/************************************************************************/
void f_co_SendText(char *text){
	f_co_write_Text(text);
}

/************************************************************************/
/* f_co_SendTaste(p_sTaste)												*/
/************************************************************************/
void f_co_SendTaste(char p_sTaste)
{
	f_co_LCD_Init();
	char cCommand = 0b00010000 + p_sTaste;
	f_co_write_Command(cCommand);
	//Animation
	f_co_CURB_OFF();
	f_co_LCD_STR("sending ");
	while(bSending != 0)
	{
		for(char Count = 0; Count < 3; Count++)
		{
			char Count2 = 0;
			char cSavePositionBit = cPositionBit;
			while(cSavePositionBit > 0)
			{
				Count2++;
				cSavePositionBit = cSavePositionBit << 1;
			}
			char cProzentEnde = (cPointerSendByte * 8 + Count2) * 100 / (cPaketGroesse * 8);
			_delay_ms(2000);
			f_co_LCD_CHR('.');
			f_co_LCD_RAM(16);
			f_co_LCD_INT(cProzentEnde);
			f_co_LCD_CHR('%');
			f_co_LCD_RAM(9 + Count);
		}
		_delay_ms(2000);
		
		f_co_LCD_RAM(8);
		f_co_LCD_STR("   ");
		f_co_LCD_RAM(8);
	}
	f_co_LCD_CLR();
	f_co_LCD_STR("finish");
}

/************************************************************************/