/****************************************************************************
 * Fichier: TP3_ex2.cpp
 * Auteur: Yannick Ouellet et David Mainville
 * Date: 16 Septembre 2013
 * DESCRIPTION : Changement de couleur de la DEL avec etats
 ****************************************************************************/

/* Information sur branchements */
/* Port B0 branché sur +        */
/* Port B1 branché sur -        */


/* Tableau d etats
 * 
 * Etat Present | Entree bouton | Etat suivant  |     Sortie
 * 	0		0		0		0          
 * 	0		1		0P		0
 * 	0P		0		1		0
 * 	0P		1		0P		0
 * 	1		0		1		0
 * 	1		1		1P		0
 * 	1P		0		2		0
 * 	1P		1		1P		0
 * 	2		0		2		0
 * 	2		1		2P		0
 * 	2P		0		0		0
 * 	2P		1		2P		0
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

    unsigned long etat = 0; //Definie le numero de l etat
    bool enfonce = false; //utilise pour verifier l etat du bouton et definie si l etat est a "p" (voir Tableau d etats)
    
    // Boucle infinie
    for(;;)
    {
      if(!enfonce) //Affichage lorsque le bouton n est pas enfonce en fonction du numero d etat
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

      // Verification du bouton poussoir 
      if(BOUTON_ENFONCE)
      {
	if(!enfonce) //Augmenter le numero d etat a chaque "nouvel" enfoncement
	{
	  enfonce = true;
	  etat++;
	  
	  if(etat >2) //Reinitialiser l etat lorsqu il atteint la fin
	    etat = 0;
	}
	else //Affichage lorsque le bouton est enfonce en fonction du numero d etat
	{
	  switch (etat)
	  {
	      case 0:
	      {
		PORTB = _BV(PORTB1); //vert
		_delay_ms(20);
		break;
	      }
	      case 1:
	      {
		PORTB = _BV(PORTB0); //rouge
		_delay_ms(8);
		PORTB = _BV(PORTB1); //vert
		_delay_ms(12);
		break;
	      }
	      case 2:
	      {
		PORTB = _BV(PORTB0); //rouge
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