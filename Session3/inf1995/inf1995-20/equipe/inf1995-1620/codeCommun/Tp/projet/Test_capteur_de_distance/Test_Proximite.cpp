/****************************************************************************
 * Fichier: Test_Proximite.cpp
 * Auteur: Mario Saliby(1668958) et Youssef Zemmahi(1665843) et Yannick Ouellet et David Mainville 
 * Date: 13 Novembre 2013
 * DESCRIPTION : Test du capteur de distance, le robot emet un son lorsqu'un objet s'approche ou s'eloigne 
 * de lui.
 ****************************************************************************/

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include "lib/libRobot.h"
#include <avr/interrupt.h> 
#include "can.h"


#define VALEURANALOGIQUE (PINA & _BV(1))

	




int main ()
{	
  // PORT A en entree pour recevoir la valeur analogique 
  DDRA =0x0;
  // PORT B en sortie 
  DDRB=0xff;
  // Declaration d'un objet can.
  can convertisseur=can();
  // Variable locale qui recoit la valeur numerique apres la conversion de la valeur analogique. 
  uint16_t valeur;
  
  // Declaration et initialisation d'un objet LibRobot.
  LibRobot r;
  r.initialisation();
  r.debut();
    
    
    
   
    _delay_ms(44);

    for(;;)
    {
      // Conversion de la valeur analogique en valeur numerique.
      valeur=convertisseur.lecture(VALEURANALOGIQUE);
      _delay_ms(100); 
      // Decalage de 2 bits vers la droite pour ne garder que 8 bits.
      valeur=valeur>>2;
      
      // La valeur minimale ne peut pas etre egale a 0.
      // La valeur 7 a ete designee comme la plus petite valeur retournee lorsque le capteur ne detecte aucun objet.
      if(valeur>7) 
	    {	
		 // Intervalles qui definissent les differents sons emis dependamment de la force du signal de retour.                                                                                     
		 if ((valeur>7) &&(valeur<=22))
		     r.jouerSon(66);
		  if ((valeur>22) &&(valeur<=37))
		    r.jouerSon(67);
		  
		  if  ((valeur>37) &&(valeur<=52))
		     r.jouerSon(68);
	
		  if( (valeur>52)&&(valeur<=67))
		     r.jouerSon(69);
	
		   if ((valeur>67) &&(valeur<=82))
		      r.jouerSon(70);
	
		   if  ((valeur>82) &&(valeur<=97))
		     r.jouerSon(71);
		 
		   if( (valeur>97)&&(valeur<=112))
		       r.jouerSon(72);
			
		   if ((valeur>112) &&(valeur<=127))
		    r.jouerSon(73);
		
		   if ((valeur>127) &&(valeur<=142))
		     r.jouerSon(74);
		    
		   if  ((valeur>142) &&(valeur<=157))
		      r.jouerSon(75);
		  
		   if( (valeur>157)&&(valeur<=172))
		     r.jouerSon(76);
		   
		   if ((valeur>172) &&(valeur<=187))
		    r.jouerSon(77);
		  
		   if ((valeur>187) &&(valeur<=202))
		     r.jouerSon(78);
		  
		   if  ((valeur>202) &&(valeur<=217))
		     r.jouerSon(79);
		  
		   if( (valeur>217)&&(valeur<=232))
		     r.jouerSon(80);
		  
		   if ((valeur>232) &&(valeur<256)) 
		     r.jouerSon(81);
	    }
	    else
	    {
		 // Commande qui arrete le son.
		 r.arreterSon();
	    }
		
    }
		    
      
    
    
    return 0;
}