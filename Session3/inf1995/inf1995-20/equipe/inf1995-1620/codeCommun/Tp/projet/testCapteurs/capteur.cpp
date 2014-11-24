/****************************************************************************
 * Fichier: TP3_ex1.cpp
 * Auteur: Yannick OUellet et David Mainville
 * Date: 16 Septembre 2013
 * DESCRIPTION : Activation de LED ambrée avec bouton.
 ****************************************************************************/

/* Information sur branchements */
/* Port A0 branché sur +        DEL*/
/* Port A1 branché sur -        DEL*/

/* Port B2 branché sur module de son*/
/* Port B3 branché sur module de son*/

/* Port D4 branché sur enable moteur gauche*/
/* Port D6 branché sur sens moteur gauche*/

/* Port D5 branché sur enable moteur droit*/
/* Port D7 branché sur sens moteur droit*/


// F_CPU permet de définir la vitesse du micro-controleur soit 8MHz
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

bool capteurDroit()
{
	return (PINA & _BV(PORTA6));
}

int main()
{

	DDRB = 0xff; // sortie

	DDRA = 0x00; // entree

	while(true)
	{
		bool ok = false;

		if(capteurDroit())
			ok = true;

		/*if(PINA & _BV(PORTA2))
			ok = true;

		if(PINA & _BV(PORTA4))
			ok = true;*/

		if(ok)
			PORTB = _BV(PORTB0);
		else
			PORTB = 0x0;	
	}
		

	return 0;
}
