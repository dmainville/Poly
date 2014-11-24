/****************************************************************************
 * Fichier: TP4_ex2.cpp
 * Auteur: Yannick OUellet et David Mainville
 * Date: 17 Septembre 2013
 * DESCRIPTION : Tourner la roue droite avec differentes frequences
 ****************************************************************************/

/* Information sur branchements */
/* Port C0 branché sur JM1+        */
/* Port C1 branché sur JM1-        */

// F_CPU permet de définir la vitesse du micro-controleur soit 8MHz
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BOUTON_ENFONCE (PIND & _BV(2))

int main()
{
    DDRC = 0xff; // PORT C est en mode sortie.
    DDRD = 0x0; // PORT D est en mode entrée.
    
    bool enfonce = false;

    
    PORTC = 0x0;
    
    // Boucle infinie
    for(;;)
    {
        // Verification du bouton poussoir avec anti-rebond
        if(BOUTON_ENFONCE)
        {
	    enfonce = true;
        }
        else
	{
	    if(enfonce)
	    {
		for(uint8_t l =0; l<2; l++)
		{
		    uint16_t dureeOperation = 16667; //en us
		    uint16_t nbOperation = 60; //60 operations seconde
		    
		    if(l ==1)
		    {
			dureeOperation = 2500; //en us
			nbOperation = 400; //60 operations seconde
		    }
		  
		    for(uint8_t k = 0; k<5; k++)
		    {
			uint16_t attenteAllumee = k*(dureeOperation>>2);
			uint16_t attenteEteint = dureeOperation - attenteAllumee;

			PORTC = 0x0;
			for(uint16_t j = 0; j< nbOperation; j++)
			{
			    for(uint8_t i =0; i< 2; i++)
			    {
				PORTC = _BV(PORTC0);
				_delay_loop_2((attenteAllumee<<1)+1);
				
				PORTC = 0x0;
				_delay_loop_2((attenteEteint<<1)+1);
			    }
			}
		    }
		}
	    }

	  PORTC = 0x0;
	  enfonce = false;
	}
    }

    return 0;
}