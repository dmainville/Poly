/****************************************************************************
 * Fichier: TP6_ex2.cpp
 * Auteur: Yannick OUellet et David Mainville
 * Date: 30 Septembre 2013
 * DESCRIPTION :   Communication RS232
 ****************************************************************************/

/* Information sur branchements */
/* Port D5 branché sur Enable JM1*/
/* Port D6 branché sur Enable JM2*/

// F_CPU permet de définir la vitesse du micro-controleur soit 8MHz
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "memoire_24.h"

#define BOUTON_ENFONCE (PIND & _BV(2))

void initialisationUART ( void ) {

    // 2400 bauds. Nous vous donnons la valeur des deux
    // premier registres pour vous éviter des complications
    UBRR0H = 0;
    UBRR0L = 0xCF;
    
    
    
    // permettre la reception et la transmission par le UART0
    UCSR0A |= 0; //Flags
    
    UCSR0B |= 1 <<RXEN0 | 1<<TXEN0 ;//Activer reception et transmission
    /*UCSR0B |= 1 <<RXCIE0 //RXCIEn: RX Complete Interrupt Enable n
    UCSR0B |= 1 <<TXCIE0 //TXCIEn: TX Complete Interrupt Enable n
    UCSR0B |= 1 <<UDRIE0 //UDRIEn: USART Data Register Empty Interrupt Enable n*/
    
    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C = 0; //UPM01 et UPM00 a 0 pour la non parite, USBS0 a 0 pour 1 stop bit
    UCSR0C |= 1 <<UCSZ01 | 1<<UCSZ00 |_BV(7) ;
    //UCSROC |= 1<<UMSEL00 //Synchrone
}

// De l'USART vers le PC

void transmissionUART ( uint8_t donnee ) {

    while(! (UCSR0A & (1<<UDRE0)) ) {}
    
    UDR0 = donnee;
  
}

void lectureUART()
{
    Memoire24CXXX mem = Memoire24CXXX();
    int position = 0x00;
    uint8_t lettresLues = 0;
    
    PORTB = _BV(PORTB0); //Rouge
    
    
    //while(!(position == 41 || position > 200))
    while(!(lettresLues == 255 || position > 200))
    {
	//Lecture
	uint8_t *l;
	mem.lecture(position,l);
	position++;
	lettresLues = *l;
	
	//Transmission
	transmissionUART ( lettresLues );
    }
    
    PORTB = _BV(PORTB1); //Vert

}

int main()
{
    DDRD = 0xff; // PORT D est en mode sortie.
    DDRB = 0xff; // PORT B est en mode sortie.
    
    initialisationUART();
    
    lectureUART();

    return 0;
}
