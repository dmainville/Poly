#undef UNICODE

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include<iostream>

// Link avec ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

bool offrirSelection(SOCKET s);
void ajusteSelection(char);
void afficherSelectionCourrante();
void aide();
void envoyer(SOCKET s);
std::string getSelectionCourrante();
void afficheRetour(SOCKET s);
bool valideAdresse(char* adresse);
void restartConnection(SOCKET s);

std::vector<char> selectionCourrante;
int nbOptions = 0;
int modeAttente = false;
const int TAILLE_OPTIONS_CHOISIES = 20;
const int TAILLE_RETOUR = 100;
const int TAILLE_OPTIONS = 100;
const bool DEBUG = false;

char *host;
char *port = "5001";
struct addrinfo *result = NULL,
                *ptr = NULL,
                hints;
sockaddr_in *adresse;

int __cdecl main(int argc, char **argv)
{

    WSADATA wsaData;
    SOCKET leSocket;// = INVALID_SOCKET;

	char motRecu[TAILLE_OPTIONS];
    int iResult;


	//--------------------------------------------
    // InitialisATION de Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("Erreur de WSAStartup: %d\n", iResult);
        return 1;
    }
	// On va creer le socket pour communiquer avec le serveur
	leSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (leSocket == INVALID_SOCKET) {
        printf("Erreur de socket(): %ld\n\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
		printf("Appuyez une touche pour finir\n");
		getchar();
        return 1;
	}
	//--------------------------------------------
	// On va chercher l'adresse du serveur en utilisant la fonction getaddrinfo.
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_INET;        // Famille d'adresses
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;  // Protocole utilisé par le serveur

	// On indique le nom et le port du serveur auquel on veut se connecter
	//char *host = "L4708-01";
	//char *host = "L4708-10.lerb.polymtl.ca";

	//Demander au client d'entrer l'adresse du serveur


	char charInAdresseServeur[15];

	bool adresseValide = false;
	if(!DEBUG)
	{
		while(!adresseValide)
		{
			try
			{
				printf("Veuillez entrer l'adresse du serveur:\n");
				gets_s(charInAdresseServeur,15);
				host = charInAdresseServeur;
				adresseValide = true;
			}
			catch(...)
			{
				printf("Format d'adresse invalide!\n");
			}
		}
	}
	else
	{
		host = "132.207.29.105";
		printf("Mode DEBUG, l'adresse du serveur est %s \n",host);
		getchar();
	}


	// getaddrinfo obtient l'adresse IP du host donné
	iResult = getaddrinfo(host, port, &hints, &result);
	if ( iResult != 0 )
	{
		printf("Erreur de getaddrinfo: %d\n", iResult);
		WSACleanup();

		printf("Appuyez une touche pour finir\n");
		getchar();
		return 1;
	}

	//---------------------------------------------------------------------		
	//On parcours les adresses retournees jusqu'a trouver la premiere adresse IPV4
	while((result != NULL) &&(result->ai_family!=AF_INET))   
			 result = result->ai_next; 

	//	if ((result != NULL) &&(result->ai_family==AF_INET)) result = result->ai_next;  
	
	//-----------------------------------------
	if (((result == NULL) ||(result->ai_family!=AF_INET))) {
		freeaddrinfo(result);
		printf("Impossible de recuperer la bonne adresse\n\n");
        WSACleanup();
		printf("Appuyez une touche pour finir\n");
		getchar();
        return 1;
	}

	
	adresse=(struct sockaddr_in *) result->ai_addr;
	//----------------------------------------------------
	//printf("Adresse trouvee pour le serveur %s : %s\n\n", host,inet_ntoa(adresse->sin_addr));
	printf("Tentative de connexion au serveur %s avec le port %s\n\n", inet_ntoa(adresse->sin_addr),port);
	
	// On va se connecter au serveur en utilisant l'adresse qui se trouve dans
	// la variable result.
	iResult = connect(leSocket, result->ai_addr, (int)(result->ai_addrlen));
	if (iResult == SOCKET_ERROR) {
        printf("Impossible de se connecter au serveur %s sur le port %s\n\n", inet_ntoa(adresse->sin_addr),port);
        freeaddrinfo(result);
        WSACleanup();
		printf("Appuyez une touche pour finir\n");
		getchar();
        return 1;
	}

	printf("Connecte au serveur %s:%s\n\n", host, port);
    freeaddrinfo(result);

	//------------------------------
	//Affichage des services
	//------------------------------
	printf("============AFFICHAGE=DES=SERVICES=DISPONIBLES===================\n");

	bool finAtteinte = false;
	int temp = 0;

	while(!finAtteinte)
	{
		//Recevoir l' information envoyée par le serveur
		iResult = recv(leSocket, motRecu, TAILLE_OPTIONS, 0);

		if (iResult > 0) {

			if(motRecu[0] == 'F' && motRecu[1] == 'I' && motRecu[2] == 'N')
			{
				finAtteinte = true;
			}
			else
			{
				nbOptions++;
				printf("%s\n", motRecu);
			}
		}
		else {
			printf("Erreur de reception : %d\n", WSAGetLastError());
			finAtteinte = true;
		}
	}

	printf("E. Envoyer la selection courrante au serveur\n");
	printf("Q. Quitter\n");
	printf("A. Aide\n");
	printf("=================================================================\n\n");

	selectionCourrante.clear();

	bool quitter = false;
	while(!quitter)
	{
		printf("\n");
		if(offrirSelection(leSocket))
			return 0; //Quitter

		if(modeAttente)//On attend de recevoir les info demandé
		{
			afficheRetour(leSocket);
			modeAttente = false;
			printf("\n\n");

			closesocket(leSocket);
			WSACleanup();

			getchar();
			printf("Appuyez une touche pour finir\n");
			getchar();

			return 0;
		}

		afficherSelectionCourrante();
		//printf("fin de boucle");
	}

    // cleanup
    closesocket(leSocket);
    WSACleanup();

	printf("Appuyez sur enter pour finir\n");
	getchar();
    return 0;
}

bool offrirSelection(SOCKET s)
{
	printf("Veuillez selectionner une option :\n");

	char c = getchar();
	while(c == 10)
		c = getchar();

	if(!c)
	{
		printf("b");
		printf("Option invalide1 \n");
		return false;
	}

	if(isdigit(c)) //option numérique
	{
		int i = c-'0';
		if(i > nbOptions || i < 1)
		{
			printf("Option invalide2 \n");
			return false;
		}

		ajusteSelection(c);
	}
	else
	{
		c = toupper(c);
		if( ! (c == 'A' || c == 'E' || c == 'Q'))
		{
			printf("char %c",c);
			printf("Option invalide3 \n");
			return false;
		}
		
		if(c == 'Q')
			return true;

		if(c == 'A')
		{
			aide();
			return false;
		}

		if(c == 'E')
		{
			envoyer(s);
			return false;
		}
		//l'une des 3 options, envoyer, aide ou quitter

	}

	return false;
}

void envoyer(SOCKET s)
{
	

	char options[TAILLE_OPTIONS_CHOISIES];
	int j =0;
	for( std::vector<char>::const_iterator i = selectionCourrante.begin(); i != selectionCourrante.end(); ++i)
	{
		if(j!=0)
		{
			options[j] = '-';
			j++;
		}

		char c = *i;
		options[j] = c;
		j++;
	}
	for(j;j<TAILLE_OPTIONS_CHOISIES;j++)
	{
		options[j] = ' ';
	}

	int iResult = send(s, options, TAILLE_OPTIONS_CHOISIES, 0 );
	modeAttente = true;

	if (iResult == SOCKET_ERROR)
	{
		modeAttente = false;
		printf("Erreur du send: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		printf("Appuyez une touche pour continuer\n");
		getchar();
	}

	printf("Nombre d'octets envoyes : %ld\n\n", iResult);
}

void aide()
{
	printf("==============================AIDE===============================\n");
	printf("Pour choisir une option vous devez entrer le numero ou le chiffre\n");
	printf("correspondant a cette derniere. Puis appuyer sur la touche 'Enter'.\n"); 
	printf("Selectionnez une option qui est deja dans votre selection pour l'en\n"); 
	printf("retirer. Une fois votre selection faite,choisissez l'option 'E' pour\n");
	printf("l'envoyer au serveur.\n");
	printf("=================================================================\n");
}

void ajusteSelection(char c)
{
	if(std::find(selectionCourrante.begin(), selectionCourrante.end(), c) != selectionCourrante.end()) {
		//Si il est présent dans la sélection, l'en enlever
		selectionCourrante.erase(std::remove(selectionCourrante.begin(), selectionCourrante.end(), c), selectionCourrante.end());
	}
	else
	{
		//Sinon l'ajouter
		selectionCourrante.push_back(c);
	}
}

std::string getSelectionCourrante()
{
	if(selectionCourrante.size() == 0)
		return "";
	else
	{
		std::string s = "";
		for( std::vector<char>::const_iterator i = selectionCourrante.begin(); i != selectionCourrante.end(); ++i)
		{
			char c = *i;
			if(s != "")
				s+= " - ";
			s+=c;
		}
		return s;
	}
}

void afficherSelectionCourrante()
{
	if(selectionCourrante.size() == 0)
		printf("Selection courrante : Nulle");
	else
		printf("Selection courrante : %s\n", getSelectionCourrante().c_str());
}

void afficheRetour(SOCKET s)
{
	char motRecu[TAILLE_RETOUR];

	bool finAtteinte = false;
	while(!finAtteinte)
	{
		//Recevoir l' information envoyée par le serveur
		int iResult = recv(s, motRecu, TAILLE_RETOUR, 0);

		if (iResult > 0) {

			if(motRecu[0] == 'F' && motRecu[1] == 'I' && motRecu[2] == 'N')
			{
				finAtteinte = true;
			}
			else
			{
				printf("%s\n", motRecu);
			}
		}
		else {
			printf("Erreur de reception : %d\n", WSAGetLastError());
			finAtteinte = true;
		}
	}

	
}


