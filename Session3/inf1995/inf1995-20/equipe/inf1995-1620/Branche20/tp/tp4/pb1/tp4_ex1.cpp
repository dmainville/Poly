/****************************************************************************
 * Fichier: TP4_ex1.cpp
 * Auteur: Yannick OUellet et David Mainville
 * Date: 17 Septembre 2013
 * DESCRIPTION : Attenuation d une DEL
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
    
    bool enfonce = false;
    bool rouge = true;
    
    //1 MHz donc 1000 operation secondes donc 1ms par operation
    const uint16_t dureeOperation = 1000; //en us
    const uint16_t nbOperation = 1000; //1000 operations seconde

    //void _delay_loop_2 	( 	uint16_t  	__count	) 	effectue 4 cycles d operation
    //Le vitesse du cpu est de 8MHz donc 8 millions d operations par secondes
    //donc 0.000 000 5 s pour un _delay_loop_2(1)
    
    
    // Boucle infinie
    for(;;)
    {
        // Verification du bouton poussoir avec anti-rebond
        if(BOUTON_ENFONCE)
        {
	    enfonce = true;
	    if(rouge)
	      PORTB = _BV(PORTB0); //Rouge
	    else
	      PORTB = _BV(PORTB1); //Vert
		
        }
        else
	{
	    if(enfonce)
	    {
		for(uint16_t j = 0; j< nbOperation; j++)
		{
		    for(uint8_t i =0; i< 3; i++)
		    {
			uint16_t attenteAllumee = dureeOperation-j; //en micro seconde
			uint16_t attenteEteint = dureeOperation-attenteAllumee;    

			if(rouge)
			    PORTB = _BV(PORTB0); //Rouge
			else
			    PORTB = _BV(PORTB1); //Vert
			    
			_delay_loop_2(attenteAllumee*2+1);
			
			PORTB = 0x0;
			_delay_loop_2(attenteEteint*2+1);
		    }
		  
		}
		rouge = !rouge;
	      
	    }
	  // LED éteinte par défaut.
	  PORTB = 0x0;
	  enfonce = false;

	}
    }

    return 0;
}