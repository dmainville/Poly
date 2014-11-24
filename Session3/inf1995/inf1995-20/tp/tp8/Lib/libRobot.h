

#ifndef LIB_ROBOT_H
#define LIB_ROBOT_H


class LibRobot
{
public:

   LibRobot();
   ~LibRobot();

   static void tournerRoueDroite(uint16_t dureeAllumee, uint16_t periode,  int duree );
   
   static void attenuerDEL(bool rouge);
   
   static uint8_t BoutonEstEnfonce();

};

#endif /* LIB_ROBOT_H */
