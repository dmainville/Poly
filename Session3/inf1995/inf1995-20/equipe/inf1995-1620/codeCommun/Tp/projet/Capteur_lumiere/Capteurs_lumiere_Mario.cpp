//Notez que si l'intersection qui suit est une intersection en L, où le robot à l'obligation de poursuivre sur le seul segment possible, le virage imposé est alors ignoré et le robot retourne à son comportement aléatoire une fois l'intersection franchie. 


// F_CPU permet de définir la vitesse du micro-controleur soit 8MHz
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "can.h"

uint8_t capteurLumiere()
{	 
    DDRB = 0xFF; //PORT B est en mode sortie.
    DDRC = 0x00; // PORT C est en mode entrée.
    DDRD = 0x00; // PORT D est en mode entrée.

    uint8_t LEFT_SENSOR = PORTA2;
    uint8_t CENTER_SENSOR = PORTA4;
    uint8_t RIGHT_SENSOR = PORTA6;

    // Instanciation de l'objet de lecture de la cellule photo voltaique droite.    
    can capteurDroit;
    //Instanciation de l'objet de lecture de la cellule photo voltaique gauche.
    can capteurGauche;
    
    // Tant que le robot ne se trouve pas à une intersection.
    while((LEFT_SENSOR && CENTER_SENSOR && RIGHT_SENSOR) || (LEFT_SENSOR && CENTER_SENSOR) || (CENTER_SENSOR && RIGHT_SENSOR) || (LEFT_SENSOR && RIGHT_SENSOR))
    //for(;;)
    {
	//Lire le PORTA0.
	uint16_t valeurD = capteurDroit.lecture(0);
	// Décaller vers la gauche pour perdre les 2 bits de poids faible et eventuellement garder les 9 et 10 bits.
	valeurD = valeurD >> 2;
	// Garder seulement les 8 bits de poids faible.
	uint8_t valeur8D = (valeurD & 0x00FF);

	// Lire le PORTA1.
	uint16_t valeurG = capteurGauche.lecture(1);
	valeurG = valeurG >> 2;
	uint8_t valeur8G = (valeurG & 0x00FF); 
		
	// Si le capteur de lumière droit reçoit plus de lumière et retourne une valeur numérique assez grande.
	if(valeur8D > valeur8G && valeur8D >= 170) 
	{   
		// PORT B1 à 0.
		PORTB &= ~(_BV(PORTB1));
		// Rouge.
		PORTB |= _BV(PORTB0);
		return 0; //Tourner a droite.
	}

	else 
	{
		// Si le capteur de lumière gauche reçoit plus de lumière et retourne une valeur numérique assez grande.
		if(valeur8D < valeur8G &&  valeur8G >= 170)
		{   
			// PORT B0 à 0.
			PORTB &= ~(_BV(PORTB0));
			// Vert.
			PORTB |= _BV(PORTB1);
			return 1; //Tourner a gauche.
		}
		else
		{	// Dans le cas ou les capteurs de lumiere retourne une valeur numerique pas assez grande pour figurer dans la plage de valeurs significatives.
			return 2; //Lumiere ambiante ou valeur egale des cellule photo voltaique donc on fait rien.
		}
	}
    }
}

uint8_t getValeurLumiere()
{
	can capteurDroit;
	can capteurGauche;
	uint16_t valeurD = capteurDroit.lecture(1); 	// Garder seulement les 8 bits de poids faible.
	valeurD = valeurD >> 2;
	uint8_t valeur8D = (valeurD & 0x00FF);

	uint16_t valeurG = capteurGauche.lecture(0);
	valeurG = valeurG >> 2;
	uint8_t valeur8G = (valeurG & 0x00FF); 

	if(valeur8G < 235 && valeur8D < 235)
		return 0;

	if(valeur8G >= 235 && valeur8G > valeur8D)
		return 1;

	return 2;
}

int main()
{
    	DDRB = 0xFF; //PORT B est en mode sortie.
    	DDRA = 0x00; // PORT A est en mode entrée.

	while(true)
	{

		uint8_t result = getValeurLumiere();
		if(result == 0) //rien
		{
			PORTB = 0x0;
		}
		else if(result == 1) //gauche
		{
			PORTB = 0x0;
			// vert.
			PORTB |= _BV(PORTB1);
		}
		else if(result == 2) //droite
		{
			PORTB = 0x0;
			// rouge.
			PORTB |= _BV(PORTB0);
		}
	}

	return 0;

}












