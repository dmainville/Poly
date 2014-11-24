/****************************************************************************
 * Fichier: TP5_ex1.cpp
 * Auteur: Yannick Ouellet et David Mainville
 * Date: 23 Septembre 2013
 * DESCRIPTION : Contrôle d'une del par interruption
 ****************************************************************************/

/* Information sur branchements */
/* Port B0 branché sur +        */
/* Port B1 branché sur -        */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define BOUTON_ENFONCE (PIND & _BV(2))

volatile uint8_t etat = 0; //Definie le numero de l etat

 ISR(INT0_vect) {

    //_delay_loop_2 ( 65530 );

    if(BOUTON_ENFONCE)
    {
	  etat++;
	  
	  if(etat >2) //Reinitialiser l etat lorsqu il atteint la fin
	    etat = 0;
    }

    EIFR |= (1 << INTF0) ; //Detecte si il y a deja une interuption
}

void initialisation() {

    cli (); //bloque toutes les interruptions.

    DDRB = 0xff; // PORT B est en mode sortie.
    DDRD = 0x0; // PORT D est en mode entrée.

    EIMSK |= _BV(INT0); //permettre les interruptions externes

    // il faut sensibiliser les interruptions externes aux
    // changement de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= 0x03 ; //The rising edge of INTn generates asynchronously an interrupt request

    // sei permet de recevoir a nouveau des interruptions.
    sei ();
}

int main()
{

    initialisation();
    
    // Boucle infinie
    for(;;)
    {
	switch (etat)
	{
	    case 0:
	    {
	      PORTB = _BV(PORTB0); //rouge
	      break;
	    }
	    case 1:
	    {
	      PORTB = _BV(PORTB1); //vert
	      break;
	    }
	    case 2:
	    {
	      PORTB = 0x0; //eteinte
	      break;
	    }
	}
    }

    return 0;
}