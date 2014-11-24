/****************************************************************************
 * Fichier: TP7_Probleme1.cpp
 * Auteur: Mario Saliby(1668958) et Youssef Zemmahi(1665843)
 * Date: 19 octobre 2013
 * DESCRIPTION : Lorsque le bouton poussoir blanc est enfonce, un compteur est
 * 		 incremente 10 fois par seconde. Quand le bouton est relaache 
 * 		 ou que le compteur atteint 120, la DEL devient verte pendant
 * 		 une demi seconde. La carte mere ne fait plus rien pendant deux 
 * 		 secondes avant de devenir rouge. La DEL va clignoter compteur 
 * 		 divise par 2 fois, 2 fois paar seconde. La DEL tourne ensuite au vert
 * 		 pendant une seconde avant de revenir a son etat original.
 ****************************************************************************/

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>


#define BOUTON_ENFONCE (PIND & _BV(2))

// Logique inverse a cause du bouton poussoir blanc. Lorsqu'il est relache, la tension
// sur le signal de sortie est Vcc alors que lorsqu'il est appuye, le circuit est ferme.
uint8_t BoutonEstEnfonce()
{
  if(!!BOUTON_ENFONCE)
  {
    // anti-rebond.
    _delay_ms(10);
    return 1;
  }
  return 0;
}



int main ()
{
  // Port B en sortie.
  DDRB = 0xff;  
  // Port D en entree.
  DDRD=0x0;
  // Variable globale pour incrementer le compteur.
  uint8_t compteur;

  // Boucle infinie.
  for(;;)
  {
    // DEL est eteinte au depart.
    PORTB = 0x0;
    if(BoutonEstEnfonce())
    {
      // Le compteur est initialise a 0. La boucle for reste en vigueur tant que
      // le bouton est enfonce et que le compteur n'atteint pas 120
      for(compteur=0; ((BoutonEstEnfonce()) && (compteur<120)); compteur+=10)
      {
	// Delai de une seconde.
	_delay_ms(1000); 
	if(!BoutonEstEnfonce())
	{	
	  // Anti-rebon quand le bouton est relache :).
	  _delay_ms(10);
	}
      }
      
      // DEL verte clignote pendant 1/2 seconde.
      for(int i=0;i<5;i++)
      {	
	  // DEL verte.
	  PORTB = _BV(PORTB1);
	  _delay_ms(50);
	  // DEL eteinte.
	  PORTB=0x0;
	  _delay_ms(50);
      }
      
      _delay_ms(1950);
      
      for(compteur=compteur/2;compteur>0;compteur--)
      {
	// DEL rouge clignote 30 fois par au rythme de 2 fois par seconde.
	PORTB = _BV(PORTB0);
	_delay_ms(250);
	PORTB=0x0; 
	_delay_ms(250);
      }
      // DEL verte pendant une seconde.
      PORTB = _BV(PORTB1);
      _delay_ms(1000);    
    }

  }
  return 0;
}


