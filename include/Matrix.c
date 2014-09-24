#include <avr/io.h>
#include <util/delay.h>

unsigned char f_co_Exp(unsigned char pBasis, unsigned char pExponent);
unsigned char f_co_GET_TASTE();


/**************************************************************************
*
* Funktion: 	Taste_einlesen
* Paramteter:	-
*
* Beschreibung: Liest aus einer Matrix-Tastatur den gedrückten Scan-COde ein
* 
* Scan-Code:	1  2  3  4
*				5  6  7  8
*				9 10 11 12
*			   13 14 15 16
*
**************************************************************************/

unsigned char f_co_GET_TASTE(){
	
	DDRB = 0x0F;
	
	unsigned char Count = 0;
	unsigned char Taste = 1;
	unsigned char Taste_vorher = 0;
	unsigned char Taste_gedrueckt = 0;
	
	//Entprellung
	while(Taste_gedrueckt < 5){
		if(Taste_vorher == Taste){
			Taste_gedrueckt++;
		}
		Taste_vorher = Taste;
		Taste = 0;
		//Für Jede Reihe ein Durchgang
		for(unsigned char Zaehler = 0; Zaehler < 4; Zaehler++){
			//Falls bereits eine Taste gedrückt wurde
			if(Taste == 0){
				Count = f_co_Exp(2, Zaehler);
				PORTB = ~Count;			//Asugeben
				_delay_ms(1);			//Warte 1ms
				Count = ~PINB;			//Einlesen
				Count >>= 4;			// Durch 4 teilen
				// 1 -> 1
				// 2 -> 2
				// 4 -> 3
				// 8 -> 4
				while(Count != 0){
					Taste ++;
					Count /= 2;
				}
				if(Taste != 0){
					//Taste + 4 * Reihe rechnen
					Taste += Zaehler * 4;
				}
			}
		}
	}
	
	return Taste;
}

/**************************************************************************
*
* Funktion: 	Exp
* Paramteter:	unsigned char pBasis   		//Basiswert
*				unsigned char pExponent		//Exponent
*
* Beschreibung: Berechnet den Wert aus einer Hochrechnung aus
*
**************************************************************************/
unsigned char f_co_Exp(unsigned char pBasis, unsigned char pExponent){
	unsigned char Returnwert = 1;
	
	
	while(pExponent > 0){
		Returnwert *= pBasis;
		pExponent--;
	}
	return Returnwert;
}
