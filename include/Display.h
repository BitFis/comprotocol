#ifndef _CO_DISPLAY_C
#define _CO_DISPLAY_C

#include <avr/io.h>
#include <util/delay.h>


#define RS 4
#define E 5
#define LCD PORTA
#define DISPLAY 2
#define CURSOR 1
#define CURSOR_B 0	

unsigned char S_LCD = 7;

void f_co_LCD_Init();
void f_co_function_set(unsigned char p_byte);
void f_co_commands(unsigned char p_byte);
void f_co_write(unsigned char p_byte);
void f_co_LCD_CHR(unsigned char p_byte);
unsigned char f_co_swap_byte(unsigned char p_byte);
void f_co_LCD_STR(char p_string[255]);
void f_co_LCD_ON();
void f_co_LCD_OFF();
void f_co_CUR_ON();
void f_co_CUR_OFF();
void f_co_CURB_ON();
void f_co_CURB_OFF();
void f_co_LCD_CLR();
void f_co_SET_DCB();
void f_co_LCD_RAM(unsigned char p_Adresse);
void f_co_LCD_INT(int p_Zahl);


/**************************************************************************
*
* Funktion: 	LCD_Init
* Paramteter:	-
*
* Beschreibung: Initialisert das Display ein
* 
*
**************************************************************************/

void f_co_LCD_Init(){
	DDRA = 0xFF;
	unsigned char byte;


	_delay_ms(20);
	byte = 0b00000011;
	f_co_function_set(byte);	//Set DL at High
	_delay_ms(10);
	byte = 0b00000011;
	f_co_function_set(byte);	//Set DL at High
	_delay_ms(10);
	byte = 0b00000011;
	f_co_function_set(byte);			//Set DL at High
	_delay_ms(10);
	byte = 0b00000010;
	f_co_function_set(byte);	//Set DL at High
	_delay_ms(10);
	byte = 0b00101000;	
	f_co_commands(byte);		//Set DL at High. Set Display Line Number and character Font
	_delay_ms(10);
	byte = 0b00001111;
	f_co_commands(byte);	
	_delay_ms(10);
	byte = 0b00000001;
	f_co_commands(byte);			//Clear Display
	_delay_ms(10);
	byte = 0b00000110;
	f_co_commands(byte);			//Set Shift Modes
	_delay_ms(10);
}

/**************************************************************************
*
* Funktion: 	function_set
* Paramteter:	unsigned char p_byte
*
* Beschreibung: Berechnet den Wert aus einer Hochrechnung aus
*
**************************************************************************/
void f_co_function_set(unsigned char p_byte){
	LCD &= ~(1 << RS);
	LCD = p_byte;
	LCD |= (1 << E);
	LCD &= ~(1 << E);
	LCD |= (1 << RS);
}

/**************************************************************************
*
* Funktion: 	commands
* Paramteter:	unsigned char p_byte
*
* Beschreibung: Berechnet den Wert aus einer Hochrechnung aus
*
**************************************************************************/
void f_co_commands(unsigned char p_byte){
	unsigned char p_write;
	LCD &= ~(1 << RS);
	for(unsigned char Count = 0; Count < 2; Count ++)
	{
		p_byte = f_co_swap_byte(p_byte);
		p_write = p_byte & 0x0F;
		LCD = p_write;
		LCD |= (1 << E);
		LCD &= ~(1 << E);
	}
	_delay_ms(20);
	LCD |= (1 << RS);
}

/**************************************************************************
*
* Funktion: 	write
* Paramteter:	unsigned char p_byte
*
* Beschreibung: Berechnet den Wert aus einer Hochrechnung aus
*
**************************************************************************/
void f_co_write(unsigned char p_byte){
	unsigned char p_write;
	LCD |= (1 << RS);
	for(unsigned char Count = 0; Count < 2; Count ++)
	{
		p_byte = f_co_swap_byte(p_byte);
		p_write = p_byte & 0x0F;
		p_write |= 0x10;
		LCD = p_write;
		LCD |= (1 << E);
		LCD &= ~(1 << E);
	}
	_delay_ms(20);
	LCD &= ~(1 << RS);
}

/**************************************************************************
*
* Funktion: 	commands
* Paramteter:	unsigned char p_byte
*
* Beschreibung: Berechnet den Wert aus einer Hochrechnung aus
*
**************************************************************************/
void f_co_LCD_CHR(unsigned char p_byte){
	f_co_write(p_byte);
}

/**************************************************************************
*
* Funktion: 	swap_byte
* Paramteter:	unsigned char p_byte
*
* Beschreibung: Tascuht die Nibble eines Bytes
*
**************************************************************************/
unsigned char f_co_swap_byte(unsigned char p_byte){
	unsigned char nibble1 = p_byte & 0x0F;
	unsigned char nibble2 = p_byte & 0xF0;
	nibble1 = nibble1 << 4;
	nibble2 = nibble2 >> 4;
	p_byte = nibble1 | nibble2;
	return p_byte;
}

/**************************************************************************
*
* Funktion: 	commands
* Paramteter:	unsigned char p_byte
*
* Beschreibung: Berechnet den Wert aus einer Hochrechnung aus
*
**************************************************************************/
void f_co_LCD_STR(char p_string[255])
{
	for(unsigned char Count = 0; Count < strlen(p_string); Count ++)
	{
		f_co_LCD_CHR(p_string[Count]);
	}
}

/**************************************************************************
*
* Funktion: 	LCD_ON
*
* Beschreibung: Schaltet Display ein
*
**************************************************************************/
void f_co_LCD_ON()
{
	S_LCD |= (1 << DISPLAY);
	f_co_SET_DCB();
}

/**************************************************************************
*
* Funktion: 	LCD_OFF
*
* Beschreibung: Schaltet Display aus
*
**************************************************************************/
void f_co_LCD_OFF(){
	S_LCD &= ~(1 << DISPLAY);
	f_co_SET_DCB();
}

/**************************************************************************
*
* Funktion: 	CUR_ON
*
* Beschreibung: Schaltet Cursor ein
*
**************************************************************************/
void f_co_CUR_ON()
{
	S_LCD |= (1 << CURSOR);
	f_co_SET_DCB();
}

/**************************************************************************
*
* Funktion: 	CUR_OFF
*
* Beschreibung: Schaltet Cursor aus
*
**************************************************************************/
void f_co_CUR_OFF()
{
	S_LCD &= ~(1 << CURSOR);
	f_co_SET_DCB();
}

/**************************************************************************
*
* Funktion: 	CURB_ON
*
* Beschreibung: Schaltet Cursor ein
*
**************************************************************************/
void f_co_CURB_ON()
{
	S_LCD |= (1 << CURSOR_B);
	f_co_SET_DCB();
}

/**************************************************************************
*
* Funktion: 	CURB_OFF
*
* Beschreibung: Schaltet Cursor aus
*
**************************************************************************/
void f_co_CURB_OFF()
{
	S_LCD &= ~(1 << CURSOR_B);
	f_co_SET_DCB();
}

/**************************************************************************
*
* Funktion: 	LCD_CLR
*
* Beschreibung: Löscht das Display
*
**************************************************************************/
void f_co_LCD_CLR()
{		
	unsigned char clear = 1;
	f_co_commands(clear);
}

/**************************************************************************
*
* Funktion: 	SET_DCB
*
* Beschreibung: Löscht das Display
*
**************************************************************************/
void f_co_SET_DCB()
{
	unsigned char write;
	write = S_LCD;
	write += 8;
	f_co_commands(write);
}

/**************************************************************************
*
* Funktion: 	LCD_RAM
*
* Beschreibung: Setzt Display-Ram-Adresse
*
**************************************************************************/
void f_co_LCD_RAM(unsigned char p_Adresse)
{
	p_Adresse |= 0b10000000;
	f_co_commands(p_Adresse);
	_delay_ms(10);
}

/**************************************************************************
*
* Funktion: 	LCD_INT
*
* Beschreibung: Setzt Display-Ram-Adresse
*
**************************************************************************/
void f_co_LCD_INT(int p_Zahl)
{
	if(p_Zahl < 0)
	{
		p_Zahl *= -1;
		f_co_write(0b00101101);
	}
	unsigned char naZahl[50];
	unsigned char length = 0;
	for(unsigned char Count = 0; p_Zahl > 0; Count ++)
	{
		unsigned char nZahl = p_Zahl % 10;
		nZahl |= 0b00110000;
		naZahl[Count] = nZahl;
		p_Zahl /= 10;
		length = Count;
	}
	for(unsigned char Count = length; Count > 0; Count --)
	{
		f_co_write(naZahl[Count]);
	}
	f_co_write(naZahl[0]);
}

#endif /* _CO_DISPLAY_C */