/****************************************************************************
 * Fichier: TP2_ex2.cpp
 * Auteur: Michael Ferris
 * Date: 11 Septembre 2013
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

    // Boucle infinie
    for(;;)
    {
        // LED éteinte par défaut.
        PORTB = 0x0;

        // Verification du bouton poussoir avec anti-rebond
        if(BoutonEstEnfonce())
        {
            // Tant que le bouton est enfoncé on affiche la LED ambré
            while(BOUTON_ENFONCE)
            {
                PORTB = _BV(PORTB0);
                _delay_ms(8);
                PORTB = _BV(PORTB1);
                _delay_ms(12);
            }
        }
    }

    return 0;
}