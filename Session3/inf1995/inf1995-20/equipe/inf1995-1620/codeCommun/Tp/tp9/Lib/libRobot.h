

#ifndef LIB_ROBOT_H
#define LIB_ROBOT_H


class LibRobot
{
	public:

	//Constructeur, destructeur
	LibRobot();
	~LibRobot();
	
	static void initialisation();

	//Commandes robot
	static void debut(); //dbt
	static void attendre(int8_t duree25); //att (25 milliseconde * duree25); Empêche l'exécution d'autres commandes
	static void allumerDEL(volatile uint8_t &port, uint8_t pinCouleur); //dal
	static void eteindreDEL(volatile uint8_t &port, uint8_t pinCouleur, uint8_t pinCouleur2); //det
	static void jouerSon(uint8_t son); //sgo (voir tableau 3 tp 9)
	static void arreterSon(); //sar
	static void arreterMoteurs(); //mar
	static void avancer(uint8_t frequence255); //mav (opérande / 255 * 100%) --> vitesse max = 100% = 255
	static void reculer(uint8_t frequence255); //mre
	static void tournerDroite90(); //trd
	static void tournerGauche90(); //trg
	static void debutBoucle(uint16_t nbRepetition); //dbc (0 = aucune repetition --> une seule execution)
	static bool finDeBoucle(); //fbc, si retourne vrai on doit refaire la boucle, sinon on peut continuer
	static void fin(); //fin

	//Utils
	static uint8_t BoutonEstEnfonce();
	static void attenuerDEL(bool rouge);

	//Moteurs
	static void ajustementPWM_Moteurs( uint8_t vitesseD, uint8_t vitesseG );
	static void ajusterSens(bool sensD, bool sensG);

	//Son
	static void partirMinuterieSon ( uint16_t duree );

	//Tests
	static void testRoue(uint16_t a, uint16_t b, uint8_t port);
	static void testPort(volatile uint8_t &port, uint8_t valeur);

	//Propriete
	static bool debut_;
	static bool fin_;

	static int8_t nbBoucle;

	static volatile bool a_son; //Est ce qu'on est dans la partie a? donc son actif
	static volatile uint8_t valeur_son; //Numero du son joué
	static volatile bool enabledSon; //Est-ce que le son doit être joué
	
};

#endif /* LIB_ROBOT_H */
