/****************************************************************************
 * Fichier: TP3_ex1.cpp
 * Auteur: Yannick OUellet et David Mainville
 * Date: 16 Septembre 2013
 * DESCRIPTION : Activation de LED ambrée avec bouton.
 ****************************************************************************/

/* Information sur branchements */
/* Port B0 branché sur +        */
/* Port B1 branché sur -        */

// F_CPU permet de définir la vitesse du micro-controleur soit 8MHz
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lib/libRobot.h"


int main()
{
    DDRB = 0xff; // PORT B est en mode sortie.
    DDRD = 0x00; // PORT D est en mode entree.
    
    LibRobot r;
    
    while(true)
    {
      
      if(r.BoutonEstEnfonce())
	{
	    r.attenuerDEL(true);
	}
	else
	{
	    r.tournerRoueDroite(5,10,3000); //frequence 50% pendant 1 seconde
	}
	
	_delay_ms(3000);
    }
    
    return 0;
}