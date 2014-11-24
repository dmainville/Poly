/****************************************************************************
 * Fichier: localiser_souris.cpp
 * Auteur: Mario Saliby et Youssef Zemmah et david mainville et yannick ouellet
 * Date: 16 Septembre 2013
 * DESCRIPTION : la fonction detecte la position de la souris et renvoie le trajet 
 * a effectuer pour s'en rapprocher le maximum,les informations dans la documentation 
 * sont limitees a une distance maximal de 80 centimetres soit environ 32 pouces,
 * si la souris est detectee mais est a une distance superieur a 80 cm , les 
 * valeurs renvoyee seront les valeurs maximales, afin d'approcher au maximum 
 * la sourie puis refaire un autre scan 
 ****************************************************************************/
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h> 
#include "can.h"


#define VALEURANALOGIQUE (PINA & _BV(1))

enum angle {AxeX,Angle45,AxeY};
angle orientation;



// bool  detecter_souris ( orientation  position )
int main ()
{ 
uint8_t axe_x=0;
uint8_t axe_y=0;

angle orientation;
 
  uint8_t distance;
  bool detecter;
  can convertisseur=can();
  // Variable locale qui recoit la valeur numerique apres la conversion de la valeur analogique. 
  uint16_t valeur;
  
   valeur=convertisseur.lecture(VALEURANALOGIQUE);
     _delay_ms(100); 
      // Decalage de 2 bits vers la droite pour ne garder que 8 bits.
      valeur=valeur>>2;
  
  
      
   if(valeur>7)   
   {
     detecter=true;
      // 32 pouces (environ 80 cm) / 4 pouces (environ 10cm) plage de valeur ( (256-7)/8=31)
 
  if(( valeur >=211)&&(valeur<=256))
    distance= 4;
  
  switch (orientation) 
  {// cas 0,1,2  , axe des x , angle , axe des y
      case AxeX :
	{
	       if(( valeur >110)&&(valeur<=250))
		    {
		      axe_x=1;	
		      axe_y=0;
		    }
	      if(( valeur >57)&&(valeur<=110))
		    {
		      axe_x=1;
		      axe_y=0;
		    }
	       if(( valeur >39)&&(valeur<=57))
		    {
		      axe_x=2;
		      axe_y=0;
		    }
		    if(( valeur <=39))
		    {
		      axe_x=3;
		      axe_y=0;
		    }
		break;
	}

    
    
      case Angle45 :  // diagonale d'un carre de cote=10 pouces = 14 pouces
	{
	       if(( valeur >66)&&(valeur<=250))
		    {
		      axe_x=1;
		      axe_y=1;
		    }
	     if(valeur<=66)
		    {
		      axe_x=2;
		      axe_y=2;
		    }
	   
		    break;
	 }
    
   }   
    

}
   else
   {
     detecter=false;
     axe_x=0;
     axe_y=0;
   
   }
 return 0;
// return detecter;
}

 
 