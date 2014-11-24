/****************************************************************************
 * Fichier: TP5_ex3.cpp
 * Auteur: Yannick OUellet et David Mainville
 * Date: 23 Septembre 2013
 * DESCRIPTION : Le PWM avec le timer1 sans interuptions
 ****************************************************************************/

/* Information sur branchements */
/* Port D5 branché sur Enable JM1*/
/* Port D6 branché sur Enable JM2*/

// F_CPU permet de définir la vitesse du micro-controleur soit 8MHz
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BOUTON_ENFONCE (PIND & _BV(2))
#define START_TIMER TCCR1B|=_BV(CS10)

void ajustementPWM ( uint8_t duree ) {
    // mise a un des etat sortie OC1A et OC1B sur comparaison
    // reussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe a 0xFF (mode #1 de la table 15-5
    // page 136 de la description technique du ATmega324PA)
    //TCCR1A = (1 << COM1A1) | (1 << COM1B1);
    TCCR1A |= 1 <<WGM10 |1 <<COM1A1 |1 <<COM1B1; //Set timer 1 in mode 1 (Phase Correct PWM TOP = 255 ) en comparaison sur A et B (1 <<COM1A1 |1 <<COM1B1)
    OCR1A = duree; //ratio frequence
    OCR1B = duree;

    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1B = (1 << CS11); //prescale
    //START_TIMER;
    }

int main()
{


    //8Mh --> 8 million operation seconde --> prescale de 8 pour 2 secondes -> 2 000 000
  
    DDRB = 0xff; // PORT C est en mode sortie.
    DDRD = 0xff; // PORT D est en mode sortie.

    ajustementPWM(0);
    _delay_ms(2000); //Attendre 2 secondes
    
    for(uint8_t i=1; i<5; i++ )
    {
	ajustementPWM(i*64-1);
	_delay_ms(2000); //Attendre 2 secondes
    }
    
    ajustementPWM(0);
    
    return 0;
}