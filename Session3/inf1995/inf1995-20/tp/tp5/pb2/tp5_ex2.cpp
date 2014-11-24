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

volatile bool minuterieExpiree = false;
volatile bool boutonPoussoir = false;
volatile bool enableBouton = false;

ISR ( TIMER1_COMPA_vect ) {
  
    minuterieExpiree = true;
    enableBouton = false;
}


 ISR(INT0_vect) {

    if(BOUTON_ENFONCE && enableBouton)
    {
	boutonPoussoir = true;
    }

    EIFR |= (1 << INTF0) ; //Detecte si il y a deja une interuption
}

void partirMinuterie ( uint16_t duree ) {
    minuterieExpiree = 0;
    // mode CTC du timer 1 avec horloge divisee par 1024
    // interruption après la duree specifiee
    
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
    PORTB = 0x00;//DEL eteinte

    // sei permet de recevoir a nouveau des interruptions.
    sei ();
}

int main()
{

    initialisation();
    
    _delay_ms(10000); //Attendre 10 secondes
    PORTB = _BV(PORTB0); //Rouge
    _delay_ms(100); //1/10 sec
    PORTB = 0x00; //Eteint
    partirMinuterie(7813); //8Mh --> 8 million operation seconde --> 0.000 000 125 seconde par operation * 1024 prescaler = 0.000 128 seconde operation * 7813 = 1 seconde
    enableBouton = true;
    
    do {
    // attendre qu'une des deux variables soit modifiée
    // par une ou l'autre des interruptions.
      
    } while ( !minuterieExpiree && !boutonPoussoir );

    if(boutonPoussoir)
      PORTB = _BV(PORTB1); //Vert
    else
      PORTB = _BV(PORTB0); //Rouge
    
    cli (); //arretez les interuption


    return 0;
}