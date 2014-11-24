/****************************************************************************
 * Fichier: TP2_ex2.cpp
 * Auteur: Michael Ferris
 * Date: 11 Septembre 2013
 * DESCRIPTION : Activation de LED ambrée avec bouton.
 ****************************************************************************/

/* Information sur branchements */
/* Port B0 branché sur +        */
/* Port B1 branché sur -        */


/* Tableau d etats
 * 
 * Etat Present | Entree bouton | Etat suivant
 * 	0		0		0
 * 	0		1		0P
 * 	0P		0		1
 * 	0P		1		0P
 * 	1		0		1
 * 	1		1		1P
 * 	1P		0		2
 * 	1P		1		1P
 * 	2		0		2
 * 	2		1		2P
 * 	2P		0		0
 * 	2P		1		2P
 * 
 * 
 * Couleurs associees aux etats
 * 0 = rouge
 * 0P = ambre
 * 1 = vert
 * 1P = rouge
 * 2 = eteint
 * 2P = vert
 * */




// F_CPU permet de définir la vitesse du micro-controleur soit 8MHz
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BOUTON_ENFONCE (PIND & _BV(2))


int main()
{
    DDRB = 0xff; // PORT B est en mode sortie.
    DDRD = 0x0; // PORT D est en mode entrée.

    unsigned long etat = 0;
    bool enfonce = false;
    
    // Boucle infinie
    for(;;)
    {
      if(!enfonce)
      {
	switch (etat)
	{
	    case 0:
	    {
	      PORTB = _BV(PORTB1); //rouge
	      break;
	    }
	    case 1:
	    {
	      PORTB = _BV(PORTB0); //vert
	      break;
	    }
	    case 2:
	    {
	      PORTB = 0x0; //eteinte
	      break;
	    }
	}
      }

      // Verification du bouton poussoir avec anti-rebond
      if(BOUTON_ENFONCE)
      {
	if(!enfonce)
	{
	  enfonce = true;
	  etat++;
	  
	  if(etat >2)
	    etat = 0;
	}
	else
	{
	  switch (etat)
	  {
	      case 0:
	      {
		PORTB = _BV(PORTB0); //vert
		_delay_ms(20);
		break;
	      }
	      case 1:
	      {
		PORTB = _BV(PORTB1); //rouge
		_delay_ms(8);
		PORTB = _BV(PORTB0); //vert
		_delay_ms(12);
		break;
	      }
	      case 2:
	      {
		PORTB = _BV(PORTB1); //rouge
		_delay_ms(20);
		break;
	      }
	  }
	}
	
      }
      else
      {
	enfonce = false;
      }
    }

    return 0;
}