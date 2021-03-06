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
#include "lib/libRobot.h"
#include "memoire_24.h"


int main()
{
	LibRobot r;
	r.initialisation();

	//LE son sur B2-3
	DDRB = 0xff; // sortie

	//LED sur le A
	DDRA = 0xff; // sortie	
	volatile uint8_t& portDEL = PORTA;
	uint8_t pinCouleur = _BV(PORTA0);
	uint8_t pinCouleur2 = _BV(PORTA1);

	//Moteurs
	DDRD = 0xff; // sortie

	//Mémoire
	Memoire24CXXX mem = Memoire24CXXX();
	uint8_t* donnee;
	uint8_t* donnee1;
	uint8_t instruction=0x00;
	uint8_t operande;
	
	uint16_t derniereBoucle = 0;

	//test
	bool temp = true;
	uint16_t operation = 0;

	for (  uint16_t i=0; instruction!=0xFF; i+=2 )
  	{
		mem.lecture(i,donnee);
		//_delay_ms(5);
		instruction=*donnee;
		//_delay_ms(5);

		// lire l'operande de la memoire
		mem.lecture(i+1,donnee1);
		//_delay_ms(5);
		operande=*donnee1;

		switch (instruction)
		{
			case 0x01:
			{
				r.debut();
				break;
			}
			case 0x02 :
			{
				if(r.debut_)
					for(int i =0; i< operande; i++) //operande
					{
						_delay_ms(25);
					}
				break;
			}
			case 0x44:
			{
				r.allumerDEL(portDEL,pinCouleur);
				break;
			}
			case 0x45:
			{
				r.eteindreDEL(portDEL,pinCouleur,pinCouleur2);
				break;
			}
			case 0x48:
			{
				r.jouerSon(operande);
				break;
			}
			case 0x09:
			{
				r.arreterSon();
				break;
			}
			case 0x60:
			case 0x61:
			{
				r.arreterMoteurs();
				break;
			}
			case 0x62:
			{
				r.avancer(operande);
				break;
			}
			case 0x63:
			{
				r.reculer(operande);
				 break;
			}
			case 0x64:
			{
				r.tournerDroite90();
				break;
			}
			case 0x65:
			{
				r.tournerGauche90();
				break;
			}
			case 0xC0:
			{	
				r.debutBoucle(operande);
				derniereBoucle = i;

				break;
			}
			case 0xC1:
			{
				if(r.finDeBoucle())//Besoin de retourner a debut de boucle
					i = derniereBoucle;
				break;
			}
			case 0xFF:
			{
				r.fin();
				return 0;
				break;
			}
		}
	}

	return 0;
}
