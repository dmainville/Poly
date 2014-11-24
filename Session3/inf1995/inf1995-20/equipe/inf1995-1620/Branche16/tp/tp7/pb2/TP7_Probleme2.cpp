/****************************************************************************
 * Fichier: TP7_Probleme2.cpp
 * Auteur: Mario Saliby(1668958) et Youssef Zemmahi(1665843)
 * Date: 19 Octobre 2013
 * DESCRIPTION : La DEL est verte lorsque la photoresistance capte une lumiere
 * 		 basse, ambree lorsque la lumiere est a un niveau moyen puis 
 * 		 rouge lorsque la lumiere est de forte intensite.
 ****************************************************************************/

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include "can.h"
#include "can.cpp"

#define VALEURANALOGIQUE (PINA)

int main()
{
  // Port A en entree.
  DDRA = 0X0;
  // Port B en sortie.
  DDRB = 0xff;
  // Construction par defaut d'un objet can.
  can convertisseur;
  // Variable ou est affectee la valeur numerique de la valeur analogique du port A.
  uint16_t valeur_numerique;

  // Boucle infinie.
  for(;;)
  {
    // Calcul de la valeur numerique 
    valeur_numerique = convertisseur.lecture(VALEURANALOGIQUE);
    // Il faut effectuer un decalage de 2 bits vers la droite pour avoir un resultat sur
    // 8 bits plutot que 10 bits puisque ces deux bits n'ont pas de signification particuliere.
    valeur_numerique = valeur_numerique >> 2;

    // Intervalle de valeurs correspondant a une lumiere basse.
    if((valeur_numerique>=0) && (valeur_numerique<85))
    {
	  // DEL est verte.
	  PORTB = _BV(PORTB1);
    }
	  
    // Intervalle de valeurs correspondant a une lumiere de bon niveau.
    if((valeur_numerique>=85) && (valeur_numerique<170))
    {
	  // DEL est ambree.
	  PORTB = _BV(PORTB1); 
	  _delay_ms(8);
	  PORTB = _BV(PORTB0);
	  _delay_ms(12);	
    }
    
    // Intervalle de valeurs correspondant a une lumiere forte. On s'arrete a 256 puisque
    // 2^8 = 256. Sur 8 bits, il n'y a donc que 256 valeurs possibles.
    if((valeur_numerique>=170) && (valeur_numerique<256))
    {
      // DEL est rouge
      PORTB = _BV(PORTB0);
    }    
  }
  return  0;
}

