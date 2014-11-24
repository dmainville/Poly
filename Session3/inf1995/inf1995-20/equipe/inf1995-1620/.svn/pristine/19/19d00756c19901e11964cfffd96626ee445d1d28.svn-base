// Définitions et inclusions.
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lib/libRobot.h"



// Chacun des capteurs du robot est connecté à une des pines du port D. Leurs sorties servent d'entrée au programme. 
// Le capteur gauche est relié à la pin D2, le capteur central à la pine D4 et le capteur droit à la pin D6.
#define SENSOR_LEFT(PIND2 & _BV(2))
#define SENSOR_CENTER(PIND4 & _BV(2))
#define SENSOR_RIGHT(PIND6 & _BV(2))


// Vartiables 
LibRobot robot;
bool vide_;
enum Comportement {avancer, tournegauche, tournerdroite};
Comportement comportement;
enum TypeIntersection {croix, baseT, droiteT, gaucheT, coinD, coinG};
TypeIntersection typeintersection;




// Cette methode est appelee lorsqu'au moins deux capteurs detectent une ligne noire.
// Elle determine le type d'intersection a laquelle se trouve le robot en changeant la valeur de la variable typeintersection .
// La methode comportementAleatoire() est ensuite appelee pour determiner quel virage prendre dependamment du type d'intersection.
void trouverTypeIntersection()
{
  if(!SENSOR_LEFT && !SENSOR_CENTER && !SENSOR_RIGHT)
  {
    while(!SENSOR_LEFT && !SENSOR_RIGHT)
    {
      robot.avancer(operande);
    }
	  
    if(!SENSOR_CENTER)
    {
      typeintersection = croix;
    }
    else
    {
      typeintersection = baseT; 
    }
  }

  
  if(!SENSOR_CENTER && !SENSOR_RIGHT)
  {
    while(!SENSOR_RIGHT)
    {
      robot.avancer(operande);
    }
	  
    if(!SENSOR_CENTER)
    {
      typeintersection = droiteT;
    }
    else
    {
      typeintersection = coinD;
    }
  }

  
  if(!SENSOR_LEFT && !SENSOR_CENTER)
  {
    while(!SENSOR_LEFT)
    {
      robot.avancer(operande);
    }
	  
    if(!SENSOR_CENTER)
    {
      typeintersection = gaucheT;
    }
    else
    {
      typeintersection = coinG;
    }
  }
}





