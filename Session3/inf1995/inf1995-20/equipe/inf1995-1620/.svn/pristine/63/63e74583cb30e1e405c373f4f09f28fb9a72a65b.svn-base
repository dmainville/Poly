/****************************************************************************
 * Fichier: libRobot.cpp
 * Auteur: Yannick Ouellet, David Mainville, Mario Saliby, Youssef ZEMMAHI
 * Date: 24 Ocotbre 2013
 * DESCRIPTION : Lib pour le robot
 ****************************************************************************/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "libRobot.h"

#define BOUTON_ENFONCE (PIND & _BV(2))

bool LibRobot::debut_;
bool LibRobot::fin_;

uint8_t LibRobot::nbBoucle;

//Son
volatile bool LibRobot::a_son;
volatile uint8_t LibRobot::valeur_son;
volatile bool LibRobot::enabledSon;

LibRobot::LibRobot(){}
LibRobot::~LibRobot(){}

// Fonction pour vérifier l'état du bouton en prenant compte du rebond
uint8_t LibRobot::BoutonEstEnfonce()
{ 
  //Require -- DDRB = 0xff; // PORT B est en mode sortie.
  
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

void LibRobot::initialisation()
{
	debut_ = false;
	fin_ = false;

	a_son = false;
	valeur_son = 0;
	enabledSon = false;
	nbBoucle = 0;
}

//---------------
//Commandes robot
//---------------
	void LibRobot::debut()
	{
		debut_ = true;
	}

	void LibRobot::attendre(int8_t duree25)
	{
		if(!debut_)
			return;
		//Le calcul du temps d attente doit etre ajuste en fonction de b
		for(int i =0; i< duree25; i++)
		{
			_delay_ms(25);
		}
	}

	void LibRobot::allumerDEL(volatile uint8_t &port, uint8_t pinCouleur)
	{
		if(!debut_)
			return;
		port |= pinCouleur;
	}

	void LibRobot::eteindreDEL(volatile uint8_t &port, uint8_t pinCouleur, uint8_t pinCouleur2)
	{
		if(!debut_)
			return;
		port &= ~(pinCouleur);
		port &= ~(pinCouleur2);
	}

	void LibRobot::jouerSon(uint8_t son)
	{
		if(!debut_)
			return;

		if(son == valeur_son) //Meme son que le son courrant
			return;

		if(son < 45 && son > 81)
			return;

		valeur_son = son;
		enabledSon = true;
		a_son = true;
		
		//8Mh --> 8 million operation seconde --> 0.000 000 125 seconde par operation * 256 prescaler = 0.000 032 seconde operation
		switch (son)
		{
			case 45:{partirMinuterieSon(142);break;} //142 * 0.000 032s -> 0.00454545454545455
			case 46:{partirMinuterieSon(134);break;}
			case 47:{partirMinuterieSon(127);break;}
			case 48:{partirMinuterieSon(119);break;}
			case 49:{partirMinuterieSon(113);break;}
			case 50:{partirMinuterieSon(106);break;}
			case 51:{partirMinuterieSon(100);break;}
			case 52:{partirMinuterieSon(95);break;}
			case 53:{partirMinuterieSon(89);break;}
			case 54:{partirMinuterieSon(84);break;}
			case 55:{partirMinuterieSon(80);break;}
			case 56:{partirMinuterieSon(75);break;}
			case 57:{partirMinuterieSon(71);break;}
			case 58:{partirMinuterieSon(67);break;}
			case 59:{partirMinuterieSon(63);break;}
			case 60:{partirMinuterieSon(60);break;}
			case 61:{partirMinuterieSon(56);break;}
			case 62:{partirMinuterieSon(53);break;}
			case 63:{partirMinuterieSon(50);break;}
			case 64:{partirMinuterieSon(47);break;}
			case 65:{partirMinuterieSon(45);break;}
			case 66:{partirMinuterieSon(42);break;}
			case 67:{partirMinuterieSon(40);break;}
			case 68:{partirMinuterieSon(38);break;}
			case 69:{partirMinuterieSon(36);break;}
			case 70:{partirMinuterieSon(34);break;}
			case 71:{partirMinuterieSon(32);break;}
			case 72:{partirMinuterieSon(30);break;}
			case 73:{partirMinuterieSon(28);break;}
			case 74:{partirMinuterieSon(27);break;}
			case 75:{partirMinuterieSon(25);break;}
			case 76:{partirMinuterieSon(24);break;}
			case 77:{partirMinuterieSon(22);break;}
			case 78:{partirMinuterieSon(21);break;}
			case 79:{partirMinuterieSon(20);break;}
			case 80:{partirMinuterieSon(19);break;}
			case 81:{partirMinuterieSon(18);break;}
		}
	}

	void LibRobot::arreterSon()
	{
		if(!debut_)
			return;
		enabledSon = false;
		valeur_son = 0;		
	}

	void LibRobot::arreterMoteurs()
	{
		if(!debut_)
			return;
		ajustementPWM_Moteurs(0,0);
	}

	void LibRobot::avancer(uint8_t frequence255)
	{
		if(!debut_)
			return;

		ajusterSens(true, true);
		ajustementPWM_Moteurs(frequence255,frequence255);
	}
	void LibRobot::avancer(uint8_t frequence255G, uint8_t frequence255D, int8_t ajustementG, int8_t ajustementD )
	{
		if(!debut_)
			return;

		ajusterSens(true, true);

		uint8_t fG, fD;
		int16_t tempAdd = frequence255D+ajustementD;

		if(tempAdd > 255)
			fD = 255;
		else if(tempAdd < 0)
			fD = 0;
		else
			fD = tempAdd;

		tempAdd = frequence255G+ajustementG;
		if(tempAdd > 255)
			fG = 255;
		else if(tempAdd < 0)
			fG = 0;
		else
			fG = tempAdd;

		ajustementPWM_Moteurs(fD, fG);
	}

	void LibRobot::virer(uint8_t frequence255, int8_t ajustementG, int8_t ajustementD, bool sens )
	{
		if(!debut_)
			return;

		ajusterSens(true, true);	

		uint8_t fG, fD;
		if(sens)
		{
			int16_t tempAdd = frequence255+ajustementG;
			if(tempAdd > 255)
				fG = 255;
			else if(tempAdd < 0)
				fG = 0;
			else
				fG = tempAdd;
			fD = 0;
		}
		else
		{
			fG = 0;
			int16_t tempAdd = frequence255+ajustementD;

			if(tempAdd > 255)
				fD = 255;
			else if(tempAdd < 0)
				fD = 0;
			else
				fD = tempAdd;
		}

		ajustementPWM_Moteurs(fD, fG);
	}

	void LibRobot::reculer(uint8_t frequence255)
	{
		if(!debut_)
			return;

		ajusterSens(false, false);
		ajustementPWM_Moteurs(frequence255,frequence255);
	}

	void LibRobot::reculer(uint8_t frequence255G, uint8_t frequence255D, int8_t ajustementG, int8_t ajustementD )
	{
		if(!debut_)
			return;

		ajusterSens(false, false);

		uint8_t fG, fD;
		int16_t tempAdd = frequence255D+ajustementD;

		if(tempAdd > 255)
			fD = 255;
		else if(tempAdd < 0)
			fD = 0;
		else
			fD = tempAdd;

		tempAdd = frequence255G+ajustementG;
		if(tempAdd > 255)
			fG = 255;
		else if(tempAdd < 0)
			fG = 0;
		else
			fG = tempAdd;

		ajustementPWM_Moteurs(fD, fG);
	}

	void LibRobot::decoincer(bool gauche, bool droite, bool sens)
	{
		ajusterSens(sens, sens);

		if(gauche && droite)
			ajustementPWM_Moteurs(255, 255);
		else if(gauche)
			ajustementPWM_Moteurs(0, 255);
		else if(droite)
			ajustementPWM_Moteurs(255, 0);
	}

	void LibRobot::tournerDroite90()
	{
		if(!debut_)
			return;

		ajusterSens(false, true);
		ajustementPWM_Moteurs(255,255);

		_delay_ms(250);//attendre 1.25 seconde

		ajustementPWM_Moteurs(0,0);	
	}

	void LibRobot::tournerGauche90()
	{
		if(!debut_)
			return;

		ajusterSens(true, false);
		ajustementPWM_Moteurs(255,255);

		_delay_ms(250);//attendre 1.25 seconde

		ajustementPWM_Moteurs(0,0);	
	}

	void LibRobot::debutBoucle(uint16_t nbRepetition)
	{
		if(!debut_)
			return;
		nbBoucle = nbRepetition;
	}

	bool LibRobot::finDeBoucle()
	{
		if(!debut_)
			return false;

		nbBoucle--;
		return(nbBoucle > 0);
	}

	void LibRobot::fin()
	{
		if(!debut_)
			return;
		fin_ = true;
	}

//---------------
//Gestion Moteurs
//---------------

	void LibRobot::ajustementPWM_Moteurs( uint8_t vitesseD, uint8_t vitesseG )
	{
		//droite sur D5
		//gauche sur D4

		// mise a un des etat sortie OC1A et OC1B sur comparaison
		// reussie en mode PWM 8 bits, phase correcte
		// et valeur de TOP fixe a 0xFF (mode #1 de la table 15-5
		// page 136 de la description technique du ATmega324PA)
		//TCCR1A = (1 << COM1A1) | (1 << COM1B1);
		TCCR1A |= 1 <<WGM10 |1 <<COM1A1 |1 <<COM1B1;
		//TCCR1A |= 1 <<WGM10 |1 <<COM1A0 |1 <<COM1B0;
		//TCCR1A |= 1 <<WGM10;//Set timer 1 in mode 1 (Phase Correct PWM TOP = 255 ) en comparaison sur A et B (1 <<COM1A1 |1 <<COM1B1)
		OCR1A = vitesseD; //ratio frequence
		OCR1B = vitesseG;

		// division d'horloge par 8 - implique une frequence de PWM fixe
		TCCR1B = (1 << CS11); //prescale
		//START_TIMER;
	}

	void LibRobot::ajusterSens(bool sensD, bool sensG)
	{
		//droite sur D7
		//gauche sur D6

		if(sensD) //0 si on avance
			PORTD &= ~(_BV(PORTD7));
		else
			PORTD |= _BV(PORTD7); 

		if(sensG) //0 si on avance
			PORTD &= ~(_BV(PORTD6));
		else
			PORTD |= _BV(PORTD6);
	}

//---------------
//Gestion Sons
//---------------

	//Interuption son
	//PORTB2
	ISR ( TIMER1_COMPA_vect )
	{
	
		LibRobot r;
		if(r.enabledSon)
		{
			if(r.a_son)
				PORTB |= _BV(PORTB2);
			else
				PORTB &= ~(_BV(PORTB2));
			r.a_son = !r.a_son;
		}
		else
		{
			PORTB &= ~(_BV(PORTB2));
		}
	}

	void LibRobot::partirMinuterieSon ( uint16_t duree ) {
	    	// mode CTC du timer 1 avec horloge divisee par 1024
	    	// interruption après la duree specifiee
		//8Mh --> 8 million operation seconde --> 0.000 000 125 seconde par operation * 1024 prescaler = 0.000 128 seconde operation 
		//8Mh --> 8 million operation seconde --> 0.000 000 125 seconde par operation * 256 prescaler = 0.000 032 seconde operation       

	    	cli();           // disable all interrupts

		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1  = 0;// initialize counter

		OCR1A = duree;
		TCCR1B |= (1 << WGM12);   // CTC mode
		//TCCR1B |= (1 << CS10) | (1 << CS12);   // 1024 prescaler 
		TCCR1B |= (1 << CS12);   // 256 prescaler 
		TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

		sei();             // enable all interrupts   
	}


