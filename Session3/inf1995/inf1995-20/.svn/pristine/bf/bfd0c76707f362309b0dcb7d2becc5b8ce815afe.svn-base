/****************************************************************************
 * Fichier: TP6_ex1.cpp
 * Auteur: Yannick OUellet et David Mainville
 * Date: 30 Septembre 2013
 * DESCRIPTION :  lecture et écriture en mémoire
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


int main()
{
    DDRB = 0xff; // PORT B est en mode sortie.
    
    Memoire24CXXX mem = Memoire24CXXX();
    
    //Ecriture
    uint8_t position = 0x00;
    uint8_t lettres[41] = {	0x2A,0x45,0x2A, 	//*E*
				0x43,0x2A,		//C*
				0x4F,0x2A,		//O*
				0x4C,0x2A,		//L*  
				0x45,0x2A,		//E*  
				0x20,0x2A,		//escpace*  
				0x50,0x2A,		//P*  
				0x4F,0x2A,		//O*  
				0x4C,0x2A,		//L*  
				0x59,0x2A,		//Y*  
				0x54,0x2A,		//T*  
				0x45,0x2A,		//E*  
				0x43,0x2A,		//C*  
				0x48,0x2A,		//H*  
				0x4E,0x2A,		//N*
				0x49,0x2A,		//I*  
				0x51,0x2A,		//Q*  
				0x55,0x2A,		//U*
				0x45,0x2A,		//E*  
				0xFF,0x2A
    };
    
    uint8_t lettresLues[41];
    
    for(uint8_t i = 0; i<41; i++)
    {
	mem.ecriture(position,lettres[i]);
	position++;
	_delay_ms(5);
    }
    
    //Lecture
    position = 0x00;
    for(uint8_t i = 0; i<41; i++)
    {
	uint8_t *l;
	mem.lecture(position,l);
	position++;
	lettresLues[i] = *l;
    }
    
    //lettresLues[13] = 0x10; test avec mauvaise valeur
    
    bool valide = true;
    for(uint8_t i = 0; i<41; i++)
    {
	if(lettres[i] != lettresLues[i])
	{
	    valide = false;
	    i = 41;
	}
    }
    
    PORTB = _BV(PORTB0); //rouge*/
    if(valide)
      PORTB = _BV(PORTB1); //Vert

    return 0;
}