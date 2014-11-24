/****************************************************************************
 * Fichier: Probleme1.cpp
 * Auteur: Mario Saliby(1668958) et Youssef Zemmahi(1665843)
 * Date: 16 Septembre 2013
 * DESCRIPTION : La DEL est éteinte au départ. On doit appuyer et relâcher 
 *		 5 fois le bouton-poussoir avant que la DEL tourne au rouge 
 *		 pendant exactement 1 seconde. Par la suite, on revient au 
 *		 départ pour pouvoir recommencer.
 ****************************************************************************/

/***********************************************************************************
 * 
 * Entrée(s): DDRD (bouton-poussoir appuye ou non)
 * Sortie(s): DDRB (allumee ou eteinte)
 * États possibles: INIT, S1, S2, S3, S4, S5
 * Encodage des états : INIT(000), S1(001), S2(010), S3(011), S4(100), S5(101)
 * 
 * 
 * ----------------------------------------------------------------------
 * | Etat Initial	| Entree (DDRD)	| Etat Suivant	| Sortie (DDRB)	|
 * ----------------------------------------------------------------------
 * | INIT			| 0				| INIT			| 0				|
 * | INIT			| 1				| S1			| 0				|
 * | S1				| 0				| S1			| 0				|
 * | S1				| 1				| S2			| 0				|
 * | S2				| 0				| S2			| 0				|
 * | S2				| 1				| S3			| 0				|
 * | S3				| 0				| S3			| 0				|
 * | S3				| 1				| S4			| 0				|
 * | S4				| 0				| S4			| 0				|
 * | S4				| 1				| S5			| 0				|
 * | S5				| X				| INIT			| 1				|
 * ----------------------------------------------------------------------
 * 			Tableau 1: tableau d'etats
 * 
 ******************************************************************************/ 

/* Information sur branchements */
/* Port B0 branché sur +        */
/* Port B1 branché sur -        */

// F_CPU permet de définir la vitesse du micro-controleur soit 8MHz
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>


#define BOUTON_ENFONCE (PIND & _BV(2))

// Fonction pour vérifier l'état du bouton en prenant compte du rebond
uint8_t BoutonEstEnfonce()
	{	
		if(BOUTON_ENFONCE)
		{	// Anti-Rebond
			_delay_ms(75);
			// l'operateur !! permet de transformer une valeur quelconque en 0 ou 1.
       			// ie: BOUTON_ENFONCE renvoit 2, !!2 = 1.
			return !!BOUTON_ENFONCE;
	}
	// Le bouton n'est pas enfoncé
	return 0;
	}


	int main()
{
	DDRB = 0xff; // Port B est en mode sortie.
	DDRD = 0x0; // Port D est en mode entree.
	int compteur=0; // Le compteur du nombre de fois ou le bouton-poussoir a ete appuye est initialise a 0.


	// Boucle infinie.
	for(;;) 
	
{
	// LED est eteinte au depart
	PORTB = 0x0;
	
	// Verification du bouton poussoir avec anti-rebond.
	if(BoutonEstEnfonce())
		// Incrementation du compteur a chaque fois que le bouton-poussoir est pousse.
		compteur++;
		if(compteur==5)
		{
			// LED s'allume en rouge une fois que le compteur est a 5.
            		PORTB = _BV(PORTB0);
			// LED reste allume pendant 1 seconde.
			_delay_ms(1000);
			
			// Le compteur est reinitialise a 0 pour revenir a l'etat initial.
			compteur=0;
		}
}

return 0;

}
