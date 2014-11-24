/* Information sur branchements */
/* Port C0 branché sur JM1+     */
/* Port C1 branché sur JM1-     */

// F_CPU permet de définir la vitesse du micro-controleur soit 8MHz
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BOUTON_ENFONCE (PINC & _BV(2))


void EtatTransitoire()
{
    PORTB &= ~(_BV(PORTB0)); //Del eteinte

    for(uint8_t i = 0; i<3; i++) //La DEL clignote pendant 3 secondes
    {
	for(uint8_t j = 0; j<4; j++) //La DEL clignote 4 fois par seconde
    	{
		PORTB = _BV(PORTB0); //rouge
		_delay_ms(125);

		PORTB &= ~(_BV(PORTB0)); //eteinte
		_delay_ms(125);
    	}
    }

    PORTB &= ~(_BV(PORTB0)); //Del eteinte
}

int main()
{
    DDRB = 0xff; // PORT B est en mode sortie.
    
    //bool enfonce = false;

    EtatTransitoire();
    
		    /*uint16_t dureeOperation = 250000; //en us
		    uint16_t nbOperation = 4; 	      //4 operations seconde
		  
		    for(uint8_t k = 0; k<3; k++)
		    {
			uint16_t attenteAllumee = k*(dureeOperation>>2);
			uint16_t attenteEteint = dureeOperation - attenteAllumee;

			PORTC = 0x0;

			for(uint16_t j = 0; j< nbOperation; j++)
			{
			    for(uint8_t i =0; i< 1; i++)
			    {
				PORTC = _BV(PORTC0);
				_delay_loop_2((attenteAllumee<<1)+1);
				
				PORTC = 0x0;
				_delay_loop_2((attenteEteint<<1)+1);
			    }
			}
		    }
	    }


	  enfonce = false;
	}
    }*/

    return 0;
}
