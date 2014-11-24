/****************************************************************************
 * Fichier: ecriture_mem_tp9.cpp
 * Auteur: Youssef ZEMMAHI ,Mario SALIBY , Yannick OUellet, David Mainville
 * Date: 31 Octobre 2013
 * DESCRIPTION :   Ecriture du pseudo-code binaire dans la memoire externe du robot 
 ****************************************************************************/

/* Information sur branchements */
/* Port D5 branché sur Enable JM1*/
/* Port D6 branché sur Enable JM2*/

// F_CPU permet de définir la vitesse du micro-controleur soit 8MHz
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "memoire_24.h"



void initialisationUART ( void ) 
{

    // 2400 bauds. Nous vous donnons la valeur des deux
    // premier registres pour vous éviter des complications
    UBRR0H = 0;
    UBRR0L = 0xCF;
    
    
    
    // permettre la reception et la transmission par le UART0
    UCSR0A |= 0; //Flags
    
    UCSR0B |= 1 <<RXEN0 | 1<<TXEN0 ;//Activer reception et transmission
    /*UCSR0B |= 1 <<RXCIE0 //RXCIEn: RX Complete Interrupt Enable n
    UCSR0B |= 1 <<TXCIE0 //TXCIEn: TX Complete Interrupt Enable n
    UCSR0B |= 1 <<UDRIE0 //UDRIEn: USART Data Register Empty Interrupt Enable n*/
    
    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C = 0; //UPM01 et UPM00 a 0 pour la non parite, USBS0 a 0 pour 1 stop bit
    UCSR0C |= 1 <<UCSZ01 | 1<<UCSZ00 |_BV(7) ;
    //UCSROC |= 1<<UMSEL00 //Synchrone
}




// Du PC vers l'USART
unsigned char receptionUSART ()
{
  while(! (UCSR0A & (1<<RXC0)) )
  {
   ; 
  }
  
  return UDR0;
}



// Ecrire dans la memoire externe
void ecritureUART ()
{
  // Creation d'un objet Memoire24CXXX.
  Memoire24CXXX mem = Memoire24CXXX();
  // Adresse de depart dans la memoire.
   uint16_t adresse = 0x00;
  // Variable a laquelle sera affecte le premier octet du bytecode.
   uint16_t nbrOctets1;
  // Variable a laquelle sera affecte le deuxieme octet du bytecode.
  uint8_t nbrOctets2;
  // Variable a laquelle sera affectee chaque instruction ou operande lors de
  // la lecture du bytecode.
  uint8_t donnee;
 
  // Lecture du premier octet du bytecode.
  nbrOctets1 = receptionUSART();
  // Decalage de 8 bits vers la gauche.
  nbrOctets1 = nbrOctets1 << 8;
  
  // Lecture du deuxieme octet du bytecode.
  nbrOctets2 = receptionUSART();
  
  // Obtention du nombre d'octets total dans le bytecode.
  nbrOctets1 += nbrOctets2;
  
  // Boucle pour lire tous les octets du bytecode. Le nombre d'octets calcule
  // plus haut est diminue de 2. Ce resultat represente le nombre reel d'octets
  // designant les instructions ou leur operande. 
  for(uint16_t i = 0; i<nbrOctets1-2; i++)
  {
    // Lecture du prochain octet dans le bytecode.
    donnee = receptionUSART();
    
    // Ecriture de l'octet a l'adresse memoire designee.
    mem.ecriture(adresse+i,donnee);
    _delay_ms(5);
  }
    
}







int main()
{    
  DDRB=0xff;
 
    initialisationUART();
    
    ecritureUART();
    PORTB=_BV(PORTB3);

    return 0;
}