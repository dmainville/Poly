/****************************************************************************
 * Fichier: TP3_ex1.cpp
 * Auteur: Yannick OUellet et David Mainville
 * Date: 16 Septembre 2013
 * DESCRIPTION : Activation de LED ambrée avec bouton.
 ****************************************************************************/

/* Information sur branchements */
/* Port B0 branché sur +        */
/* Port B1 branché sur -        */

// F_CPU permet de définir la vitesse du micro-controleur soit 8MHz
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BOUTON_ENFONCE (PIND & _BV(2))


// Fonction pour vérifier l'état du bouton en prenant compte du rebond
uint8_t BoutonEstEnfonce()
{
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

int main()
{
    DDRB = 0xff; // PORT B est en mode sortie.
    DDRD = 0x0; // PORT D est en mode entrée.

    unsigned long compteur = 0; //garde en memoire le nombre de fois que l on appuie sur le bouton
    bool enfonce = false; //utilise pour verifier l etat du bouton
    
    // Boucle infinie
    for(;;)
    {
        // LED éteinte par défaut.
        PORTB = 0x0;

        // Verification du bouton poussoir avec anti-rebond
        if(BoutonEstEnfonce()) // le bouton est enfonce
        {
	  if(!enfonce) 	//Augmenter le compteur seulement la premiere fois que le bouton est enfonce;
	  {		//pour pouvoir augmenter le compteur encore, le bouton doit d abord etre relache
	    enfonce = true;
	    compteur++;
	  }
	  
	  if(compteur >= 5) //Faire apparaitre la couleur rouge lorsque le compteur affiche 5 et reinitialiser le compte a 0 apres 1 seconde
	  {
		PORTB = _BV(PORTB0); //Rouge
                _delay_ms(1000); //attendre 1 seconde
		PORTB = 0x0; //eteindre la LED
		compteur = 0;
	  }
	  
        }
        else // le bouton est relache
	{
	  enfonce = false;
	}
    }

    return 0;
}