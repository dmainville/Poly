#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "memoire_24.h"



int main ()

{
  Memoire24CXXX mem = Memoire24CXXX();
  uint8_t* donnee;
  uint8_t instruction=0x00;
  uint8_t operande;
  // le i paire correspond a l'adresse de l'instruction
  //   le i+1 correstion a l'adresse de l'operande 
  // le i=+2 pour aller a chaque instruction
  // 0xFF correspond a l'instruction fin
for (  uint16_t i=0; instruction!=0xFF; i+=2 )
  {
    
    mem.lecture(i,donnee);
    instruction=*donnee;
    // lire l'operande de la memoire
    mem.lecture(i+1,donnee);
    operande=*donnee;
    
    
    switch (instruction)
    {
	     case 0x01:
	      {
		// fonction pour debut 
		break;
	      }
      
	     case 0x02 :
	      {
		// fonction pour attendre	
		
		break;
	      }
	     case 0x44:
	      {
		// fonction pour allumer la del
		break;
	      }
	     case 0x45:
	      {
		// fonction pour eteindre la del 
		break;
	      }
	     case 0x48:
	      {
		// fonction pour jouer la sonorite
		break;
	      }
	    case 0x09:
	      {
		 // fonction pour arreter de jouer la sonorite
		break;
	      }
	     case 0x60:
	      {
		// fonction pour arreter les moteurs
		break;
	      }
	     case 0x61:
	      {
		// fonction pour arreter les moteurs
		break;
	      }
	     case 0x62:
	      {
		// fonction pour avancer
		break;
	      }
	     case 0x63:
	      {
		// fonction pour reculer
		 break;
	      }
	    case 0x64:
	      {
		// fonction pour tourner a droite
		break;
	      }
	    case 0x65:
	      {
		// fonction pour tourner a gauche
		break;
	      }
      
	    case 0xA0:
	      {
		// fonction pour debut de boucle
		break;
	      }
      
	    case 0xA1:
	      {
		// fonction pour fin de boucle
		break;
	      }
	
      
    }     
      
      
  }
      
      
      return 0;
}
      
      
      