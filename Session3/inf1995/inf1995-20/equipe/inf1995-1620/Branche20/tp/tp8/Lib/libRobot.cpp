/****************************************************************************
 * Fichier: libRobot.cpp
 * Auteur: Yannick Ouellet, David Mainville, Mario Saliby, Youssef ZEMMAHI
 * Date: 24 Ocotbre 2013
 * DESCRIPTION : Lib pour le robot
 ****************************************************************************/

/* Information sur branchements */
/* Port B0 branché sur +        */
/* Port B1 branché sur -        */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "libRobot.h"


#define BOUTON_ENFONCE (PIND & _BV(2))


LibRobot::LibRobot(){}

LibRobot::~LibRobot(){}

// Fonction pour vérifier l'état du bouton en prenant compte du rebond
uint8_t LibRobot::BoutonEstEnfonce()
{ 
  //Require -- DDRB = 0xff; // PORT B est en mode sortie.
  
    if(BOUTON_ENFONCE)
    {
        // Anti-Rebond
        _delay_ms(10);
        // Revérification du bouton suite au delais pour s'assurer de sa valeur

        // l'operateur !! permet de transformer une valeur quelconque en 0 ou 1.
        // ie: BOUTON_ENFONCE renvoit 2, !!2 = 1.
        return !!BOUTON_ENFONCE;
    }
    // Le bouton n'est pas enfoncé
    return 0;
}

void LibRobot::attenuerDEL(bool rouge){
  
  /* Information sur branchements */
  /* Port B0 branché sur +        */
  /* Port B1 branché sur -        */
  
  //Require -- DDRB = 0xff; // PORT B est en mode sortie.
  
  const uint16_t dureeOperation = 1000; //en us
  const uint16_t nbOperation = 1000; //1000 operations seconde
  
  for(uint16_t j = 0; j< nbOperation; j++)
  {
      for(uint8_t i =0; i< 3; i++)
      {
	  uint16_t attenteAllumee = dureeOperation-j; //en micro seconde
	  uint16_t attenteEteint = dureeOperation-attenteAllumee;    

	  if(rouge)
	      PORTB = _BV(PORTB0); //Rouge
	  else
	      PORTB = _BV(PORTB1); //Vert
	      
	  _delay_loop_2(attenteAllumee*2+1);
	  
	  PORTB = 0x0;
	  _delay_loop_2(attenteEteint*2+1);
      }
    
  }
  
}

void LibRobot::tournerRoueDroite(uint16_t dureeAllumee, uint16_t periode,  int duree )
{
    //dureeAllumee nb milliseconde allumee pour une periode (A)
    //periode nb milliseconde pour une periode (B)
    //duree nb milliseconde de roulement total
  
    /* Information sur branchements */
    /* Port C0 branché sur JM1+        */
    /* Port C1 branché sur JM1-        */
  
    DDRC = 0xff; // PORT B est en mode sortie.
    
    uint16_t attenteAllumee = dureeAllumee;
    uint16_t attenteEteint = periode - attenteAllumee;

    PORTC = 0x0;

    int dureeCourante = 0;
    while(dureeCourante < duree)
    {
	dureeCourante += periode;
	for(uint8_t i =0; i< 2; i++)
	{
	    PORTC = _BV(PORTC0);
	    _delay_loop_2((attenteAllumee<<1)+1); //Pour F_CPU 8000000UL
	    
	    PORTC = 0x0;
	    _delay_loop_2((attenteEteint<<1)+1);
	}
    }
}



