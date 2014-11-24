/****************************************************************************
 * Fichier: TP7_ex1.cpp
 * Auteur: Yannick Ouellet et David Mainville
 * Date: 10 Octobre 2013
 * DESCRIPTION : Jeu de minuterie avec le bouton blanc
 ****************************************************************************/

/* Information sur branchements */
/* Port B0 branché sur +        */
/* Port B1 branché sur -        */
/* Sortie breadboard sur D2     */


// F_CPU permet de définir la vitesse du micro-controleur soit 8MHz
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BOUTON_ENFONCE !(PIND & _BV(2))

void initialisation() {

    DDRB = 0xff; // PORT B est en mode sortie.
    DDRD = 0x00; // PORT D est en mode entrée.
  
}

int main()
{
    initialisation();
    
    uint8_t compteur = 0;
    bool stop = false;
    bool test = false; //Utiliser pour tester le fonctionnement du bouton
    
    while(true)
    {
	compteur = 0;
	stop = false;
      
	while(!BOUTON_ENFONCE){} //Attendre que le bouton soit enfonce
	
	//test
	if(test)
	  PORTB = _BV(PORTB0); //rouge
	
	while(!stop) //Boucle d incrementation du compteur
	{
	    if(!BOUTON_ENFONCE || compteur >= 120)
		stop = true;
	    
	    if(!stop)
	    {
		compteur++;
		_delay_ms(100);
	    }
	}
	
	
	
	while(!stop)
	{
	    if(!BOUTON_ENFONCE)
		stop = true;
	}
	
	PORTB = _BV(PORTB1); //vert
	_delay_ms(500);
	PORTB = 0x00; //eteint
	_delay_ms(2000);
	
	//Affichage, 2 clignotements par secondes
	for(uint8_t i = 0; i<(compteur>>1); i++) //Pour compteur /2 fois
	{
	    PORTB = _BV(PORTB0); //rouge
	    _delay_ms(250);
	    PORTB = 0x00; //eteint
	    _delay_ms(250);
	}
	
	PORTB = _BV(PORTB1); //vert
	_delay_ms(1000);
	PORTB = 0x00; //eteint
    }
    
    return 0;
}