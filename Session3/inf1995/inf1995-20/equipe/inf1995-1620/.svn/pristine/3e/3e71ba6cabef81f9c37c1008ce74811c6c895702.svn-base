/****************************************************************************
 * Fichier: Probleme2.cpp
 * Auteur: Mario Saliby(1668958) et Youssef Zemmahi(1665843)
 * Date: 16 Septembre 2013
 * DESCRIPTION : Quand la carte mère démarre, la DEL libre s'allume en 
 * 		 rouge. Si le bouton-poussoir noir est pesé, la DEL devient 
 * 		 ambre. Quand le bouton-poussoir est relâché, la DEL 
 * 		 devient verte. Si le bouton est de nouveau pesé, la DEL revient
 *  		 au rouge. Quand il est relâché, la DEL s'éteint. 
 * 		 Si le bouton est de nouveau pesé, la DEL devient 
 * 		 verte. Quand il est relâché, la DEL tourne au rouge ce qui 
 * 		 fait que la carte mère est de retour à son état initial et 
 * 		 tout peut recommencer.
 ****************************************************************************/

/****************************************************************************
 * 
 * Entree(s): DDRD (bouton-poussoir enfonce ou pas)
 * Sortie(s): DEL eteinte (00), DEL rouge (01), DEL verte (10), DEL ambre (11)
 * Etats possibles: ER, EA, EV, EE
 * Encondage des etats: ER (00), EA (01), EV (10), EE (11)
 * 
 * -------------------------------------------------------------------------
 * | Etat Present	| Entree	| Etat Suivant	| Sortie	|
 * ------------------------------------------------------------------------
 * | ER			| 0		| ER		| 01		|
 * | ER			| 1		| EA		| 01		|
 * | EA			| 0		| EV		| 11		|
 * | EV			| 1		| ER		| 10		|
 * | ER			| 0		| EE		| 01		|
 * | EE			| 1		| EV		| 00		|
 * | EV			| 0		| ER		| 10		|
 * -------------------------------------------------------------------------
 * 	Tableau 1: tableau de etats
 * 
 * 
 ***************************************************************************/



#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>


#define BOUTON_ENFONCE (PIND & _BV(2))

uint8_t BoutonEstEnfonce()
	{
		if(BOUTON_ENFONCE)
		{
		  // l'operateur !! permet de transformer une valeur quelconque en 0 ou 1.
       		  // ie: BOUTON_ENFONCE renvoit 2, !!2 = 1.
		  return !!BOUTON_ENFONCE;
		}
		// Le bouton n'est pas enfoncé
		return 0;
	}



int main ()
{
DDRB = 0xff; // Port B est en mode sortie.
DDRD = 0x00; // Port D est en mode entree.
enum step {etape1,etape2,etape3};
step etape;

etape = etape1; // Initialisation de l'etape.

 
// Boucle infinie
for(;;)
{
	switch (etape)

    {

	  case etape1:
	{
			if(!BoutonEstEnfonce())
			  // DEL est rouge tant que le bouton-poussoir n'est pas enfoce  
			  PORTB = _BV(PORTB0);
			while (BoutonEstEnfonce())
			{	// Des et tant que le bouton est enfonce, la DEL devient ambre
				PORTB = _BV(PORTB1);
				_delay_ms(12);
				PORTB = _BV(PORTB0);
				_delay_ms(8);	
				etape=etape2;
			}

			break;
	}

	  case etape2:
	{
		// La DEL est verte si le bouton est relache
		if(!BoutonEstEnfonce())
		  PORTB = _BV(PORTB1);
		while (BoutonEstEnfonce())
			{	// La DEL devient rouge des que le bouton est enfonce
				PORTB = _BV(PORTB0);
				etape=etape3;
			}
		break;
	}

	  case etape3:
	{	// La DEL s'eteint lorsque le bouton est relache
		if(!BoutonEstEnfonce())
		  PORTB = 0x0;
		while (BoutonEstEnfonce())
		{	// La DEL devient verte des que le bouton est appuye
			PORTB = _BV(PORTB1);
			etape=etape1;
		}
		break;
	}

	}
}

return 0;
}


