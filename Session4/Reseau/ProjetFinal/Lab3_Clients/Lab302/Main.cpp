#undef UNICODE

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

// Link avec ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

void offrirSelection();
void ajusteSelection(char);
void afficherSelectionCourrante();

std::vector<char> selectionCourrante;
int nbOptions = 0;



int __cdecl main(int argc, char **argv)
{
	bool DEBUG = true;
    WSADATA wsaData;
    SOCKET leSocket;// = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    char motEnvoye[10];
	char motRecu[100];
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

	char *host;
	char *port = "5001";
	char charInAdresseServeur[15];

	if(!DEBUG)
	{
		printf("Veuillez entrer l'adresse du serveur:\n");
		gets_s(charInAdresseServeur);
		host = charInAdresseServeur;
	}
	else
	{
		host = "192.168.44.65";
		printf("Mode DEBUG, l'adresse du serveur est %s \n",host);
		getchar();
	}



	// getaddrinfo obtient l'adresse IP du host donné
    iResult = getaddrinfo(host, port, &hints, &result);
    if ( iResult != 0 ) {
        printf("Erreur de getaddrinfo: %d\n", iResult);
        WSACleanup();
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

	sockaddr_in *adresse;
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


				/*//----------------------------
				// Demander à l'usager un mot a envoyer au serveur
				printf("Saisir un mot de 7 lettres pour envoyer au serveur: ");
				gets_s(motEnvoye);

				//-----------------------------
				// Envoyer le mot au serveur
				iResult = send(leSocket, motEnvoye, 7, 0 );
				if (iResult == SOCKET_ERROR) {
					printf("Erreur du send: %d\n", WSAGetLastError());
					closesocket(leSocket);
					WSACleanup();
					printf("Appuyez une touche pour finir\n");
				getchar();

					return 1;
				}

				printf("Nombre d'octets envoyes : %ld\n", iResult);*/

	//------------------------------
	//Affichage des services
	//------------------------------
	printf("Affichage des services disponibles:\n");

	bool finAtteinte = false;
	int temp = 0;

	while(!finAtteinte)
	{
		//Recevoir l' information envoyée par le serveur
		iResult = recv(leSocket, motRecu, 100, 0);

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
	printf("A. Aide\n\n");

	selectionCourrante.clear();
	afficherSelectionCourrante();

	bool quitter = false;
	while(!quitter)
	{
		printf("\n");
		offrirSelection();
		afficherSelectionCourrante();
	}

    // cleanup
    closesocket(leSocket);
    WSACleanup();

	printf("Appuyez une touche pour finir\n");
	getchar();
    return 0;
}

void offrirSelection()
{
	printf("Veuillez selectionner une option :\n");
	char c = getchar();

	if(!c)
	{
		printf("b");
		printf("Option invalide1 \n");
		return;
	}

	if(isdigit(c)) //option numérique
	{
		int i = c-'0';
		if(i > nbOptions)
		{
			printf("Option invalide2 \n");
			return;
		}

		ajusteSelection(c);
	}
	else
	{
		if( ! (c == 'A' || c == 'E' || c == 'Q'))
		{
			printf("Option invalide3 \n");
			return;
		}
		
		//l'une des 3 options, envoyer, aide ou quitter

	}
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


void afficherSelectionCourrante()
{
	if(selectionCourrante.size() == 0)
		printf("Selection courrante : Nulle");
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
		printf("Selection courrante : %s\n", s.c_str());
	}
}


