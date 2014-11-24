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
        if(BOUTON_ENFONCE)
        {
            // Tant que le bouton est enfoncé on affiche la LED ambré
                PORTB = _BV(PORTB0);
                _delay_ms(20);
                /*PORTB = _BV(PORTB1);
                _delay_ms(12);*/
        }
    }

    return 0;
}