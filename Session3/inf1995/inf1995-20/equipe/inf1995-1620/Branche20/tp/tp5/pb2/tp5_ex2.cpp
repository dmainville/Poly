/****************************************************************************
 * Fichier: TP5_ex2.cpp
 * Auteur: Yannick Ouellet et David Mainville
 * Date: 23 Septembre 2013
 * DESCRIPTION : Jeu de réflexe avec l'utilisation d'une minuterie
 ****************************************************************************/

/* Information sur branchements */
/* Port B0 branché sur +        */
/* Port B1 branché sur -        */


// F_CPU permet de définir la vitesse du micro-controleur soit 8MHz
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define BOUTON_ENFONCE (PIND & _BV(2))

volatile bool rouge = false;

ISR ( TIMER1_COMPA_vect ) {
  
	rouge = !rouge;
	PORTB = 0x0;
	if(rouge)
	{
		PORTB = _BV(PORTB0);
	}
}


void partirMinuterie ( uint16_t duree ) {
    	// mode CTC du timer 1 avec horloge divisee par 1024
    	// interruption après la duree specifiee
	//8Mh --> 8 million operation seconde --> 0.000 000 125 seconde par operation * 1024 prescaler = 0.000 128 seconde operation    

	    cli();           // disable all interrupts

	    TCCR1A = 0;
	    TCCR1B = 0;
	    TCNT1  = 0;// initialize counter

	    OCR1A = duree;
	    TCCR1B |= (1 << WGM12);   // CTC mode
	    TCCR1B |= (1 << CS10) | (1 << CS12);   // 1024 prescaler 
	    TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

	    sei();             // enable all interrupts   
}

void initialisation() {

    cli (); //bloque toutes les interruptions.

    DDRB = 0xff; // PORT B est en mode sortie.
    DDRD = 0x0; // PORT D est en mode entrée.

    EIMSK |= _BV(INT0); //permettre les interruptions externes
    EICRA |= 0x03 ; //The rising edge

    // sei permet de recevoir a nouveau des interruptions.
    sei ();
}

int main()
{

    initialisation();
    
    partirMinuterie(7813); //8Mh --> 8 million operation seconde --> 0.000 000 125 seconde par operation * 1024 prescaler = 0.000 128 seconde operation * 7813 = 1 seconde

    _delay_ms(5000); //Attendre 5 secondes

	//partirMinuterie(7813);
	partirMinuterie(3907);


	while(true){}

    return 0;
}
