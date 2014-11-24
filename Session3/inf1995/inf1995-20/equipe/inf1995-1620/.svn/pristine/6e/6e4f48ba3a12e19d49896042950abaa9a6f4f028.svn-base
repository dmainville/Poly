#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

// La sortie de chaque capteur est connectée à une pin du port A. 
// Ces sorties servent d'entrées au programme.
// On obtient une sortie de 0 lorsqu'un capteur détecte une ligne noire.


#define BOUTON_ENFONCE (PIND & _BV(2))


	void partirMinuterieSon (uint16_t duree) {
	    	// mode CTC du timer 1 avec horloge divisee par 1024
	    	// interruption après la duree specifiee
		//8Mh --> 8 million operation seconde --> 0.000 000 125 seconde par operation * 1024 prescaler = 0.000 128 seconde operation 
		//8Mh --> 8 million operation seconde --> 0.000 000 125 seconde par operation * 256 prescaler = 0.000 032 seconde operation       



		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1  = 0;		// initialize counter
		OCR1A = duree;
	
		//TCCR1B |= (1 << WGM12);   // CTC mode
		//TCCR1B |= (1 << CS10);   // pas de prescaler
		TCCR1B |= (1 << CS12);   // 256 prescaler 



	}


void partirCompteur() 
{    
	TCNT0  = 0; 		  // initialize counter 8 bits

	TCCR1B |= (1 << WGM12);   // CTC mode
}

int main()
{
	// PORT A est en mode entrée. Les sorties des DEL du capteurs de lignes servent de valeurs d'entrée.
	// La DEL de gauche est connectée à la pin2, la DEL du centre à la pin4 et celle de droite à la pin6.
	DDRB = 0xFF;
	//TCNT1  = 0; 		  // initialize counter 8 bits

	partirMinuterieSon(255); 
	//partirCompteur();




		for(;;)
		{	
			uint8_t compteurTCNT1L = TCNT1L & 3;
			//uint8_t compteurTCNT1l = TCNT1L;
			//compteurTCNT1l >> 7;
			//TCNT1 >> 7;
			//uint8_t compteurTCNT1l = TCNT1;
	
			if(compteurTCNT1L == 0)
			{
				PORTB = _BV(PORTB1); //vert
				_delay_ms(1000);
				PORTB = 0x00;
				_delay_ms(1000);
			}
			else if(compteurTCNT1L == 1)
			{
				PORTB = _BV(PORTB0);	//rouge
				_delay_ms(1000);
				PORTB = 0x00;
				_delay_ms(1000);
			}
			else
			{
				/*for(int i=0; i<100; i++)
				{
					PORTB = _BV(PORTB0);	//rouge
					_delay_ms(5);
					PORTB = _BV(PORTB1);	//rouge
					_delay_ms(5);
				}*/
				PORTB = 0x00;
				_delay_ms(1000);

			}

		}
	
	
	return 0;

}




