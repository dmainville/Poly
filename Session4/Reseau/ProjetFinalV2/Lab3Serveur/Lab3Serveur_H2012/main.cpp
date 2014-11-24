#undef UNICODE

#include <winsock2.h>
#include <iostream>
#include <algorithm>
#include <strstream>

using namespace std;

// link with Ws2_32.lib
#pragma comment( lib, "ws2_32.lib" )

// External functions
extern DWORD WINAPI EchoHandler(void* sd_) ;
char* reponseService(char numeroService);

const int TAILLE_OPTIONS_CHOISIES = 20;
const int TAILLE_RETOUR = 100;
const int TAILLE_OPTIONS = 100;

// List of Winsock error constants mapped to an interpretation string.
// Note that this list must remain sorted by the error constants'
// values, because we do a binary search on the list when looking up
// items.
static struct ErrorEntry {
    int nID;
    const char* pcMessage;

    ErrorEntry(int id, const char* pc = 0) : 
    nID(id), 
    pcMessage(pc) 
    { 
    }

    bool operator<(const ErrorEntry& rhs) const
    {
        return nID < rhs.nID;
    }
} gaErrorList[] = {
    ErrorEntry(0,                  "No error"),
    ErrorEntry(WSAEINTR,           "Interrupted system call"),
    ErrorEntry(WSAEBADF,           "Bad file number"),
    ErrorEntry(WSAEACCES,          "Permission denied"),
    ErrorEntry(WSAEFAULT,          "Bad address"),
    ErrorEntry(WSAEINVAL,          "Invalid argument"),
    ErrorEntry(WSAEMFILE,          "Too many open sockets"),
    ErrorEntry(WSAEWOULDBLOCK,     "Operation would block"),
    ErrorEntry(WSAEINPROGRESS,     "Operation now in progress"),
    ErrorEntry(WSAEALREADY,        "Operation already in progress"),
    ErrorEntry(WSAENOTSOCK,        "Socket operation on non-socket"),
    ErrorEntry(WSAEDESTADDRREQ,    "Destination address required"),
    ErrorEntry(WSAEMSGSIZE,        "Message too long"),
    ErrorEntry(WSAEPROTOTYPE,      "Protocol wrong type for socket"),
    ErrorEntry(WSAENOPROTOOPT,     "Bad protocol option"),
    ErrorEntry(WSAEPROTONOSUPPORT, "Protocol not supported"),
    ErrorEntry(WSAESOCKTNOSUPPORT, "Socket type not supported"),
    ErrorEntry(WSAEOPNOTSUPP,      "Operation not supported on socket"),
    ErrorEntry(WSAEPFNOSUPPORT,    "Protocol family not supported"),
    ErrorEntry(WSAEAFNOSUPPORT,    "Address family not supported"),
    ErrorEntry(WSAEADDRINUSE,      "Address already in use"),
    ErrorEntry(WSAEADDRNOTAVAIL,   "Can't assign requested address"),
    ErrorEntry(WSAENETDOWN,        "Network is down"),
    ErrorEntry(WSAENETUNREACH,     "Network is unreachable"),
    ErrorEntry(WSAENETRESET,       "Net connection reset"),
    ErrorEntry(WSAECONNABORTED,    "Software caused connection abort"),
    ErrorEntry(WSAECONNRESET,      "Connection reset by peer"),
    ErrorEntry(WSAENOBUFS,         "No buffer space available"),
    ErrorEntry(WSAEISCONN,         "Socket is already connected"),
    ErrorEntry(WSAENOTCONN,        "Socket is not connected"),
    ErrorEntry(WSAESHUTDOWN,       "Can't send after socket shutdown"),
    ErrorEntry(WSAETOOMANYREFS,    "Too many references, can't splice"),
    ErrorEntry(WSAETIMEDOUT,       "Connection timed out"),
    ErrorEntry(WSAECONNREFUSED,    "Connection refused"),
    ErrorEntry(WSAELOOP,           "Too many levels of symbolic links"),
    ErrorEntry(WSAENAMETOOLONG,    "File name too long"),
    ErrorEntry(WSAEHOSTDOWN,       "Host is down"),
    ErrorEntry(WSAEHOSTUNREACH,    "No route to host"),
    ErrorEntry(WSAENOTEMPTY,       "Directory not empty"),
    ErrorEntry(WSAEPROCLIM,        "Too many processes"),
    ErrorEntry(WSAEUSERS,          "Too many users"),
    ErrorEntry(WSAEDQUOT,          "Disc quota exceeded"),
    ErrorEntry(WSAESTALE,          "Stale NFS file handle"),
    ErrorEntry(WSAEREMOTE,         "Too many levels of remote in path"),
    ErrorEntry(WSASYSNOTREADY,     "Network system is unavailable"),
    ErrorEntry(WSAVERNOTSUPPORTED, "Winsock version out of range"),
    ErrorEntry(WSANOTINITIALISED,  "WSAStartup not yet called"),
    ErrorEntry(WSAEDISCON,         "Graceful shutdown in progress"),
    ErrorEntry(WSAHOST_NOT_FOUND,  "Host not found"),
    ErrorEntry(WSANO_DATA,         "No host data of that type was found")
};
const int kNumMessages = sizeof(gaErrorList) / sizeof(ErrorEntry);


//// WSAGetLastErrorMessage ////////////////////////////////////////////
// A function similar in spirit to Unix's perror() that tacks a canned 
// interpretation of the value of WSAGetLastError() onto the end of a
// passed string, separated by a ": ".  Generally, you should implement
// smarter error handling than this, but for default cases and simple
// programs, this function is sufficient.
//
// This function returns a pointer to an internal static buffer, so you
// must copy the data from this function before you call it again.  It
// follows that this function is also not thread-safe.
const char* WSAGetLastErrorMessage(const char* pcMessagePrefix, int nErrorID = 0)
{
    // Build basic error string
    static char acErrorBuffer[256];
    ostrstream outs(acErrorBuffer, sizeof(acErrorBuffer));
    outs << pcMessagePrefix << ": ";

    // Tack appropriate canned message onto end of supplied message 
    // prefix. Note that we do a binary search here: gaErrorList must be
	// sorted by the error constant's value.
	ErrorEntry* pEnd = gaErrorList + kNumMessages;
    ErrorEntry Target(nErrorID ? nErrorID : WSAGetLastError());
    ErrorEntry* it = lower_bound(gaErrorList, pEnd, Target);
    if ((it != pEnd) && (it->nID == Target.nID)) {
        outs << it->pcMessage;
    }
    else {
        // Didn't find error in list, so make up a generic one
        outs << "unknown error";
    }
    outs << " (" << Target.nID << ")";

    // Finish error message off and return it.
    outs << ends;
    acErrorBuffer[sizeof(acErrorBuffer) - 1] = '\0';
    return acErrorBuffer;
}

int main(void) 
{
	//----------------------
	// Initialize Winsock.
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR) {
		cerr << "Error at WSAStartup()\n" << endl;
		return 1;
	}

	//----------------------
	// Create a SOCKET for listening for
	// incoming connection requests.
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Internetwork,Socket type = SOCK_STREAM, Protocol TCP
	if (ServerSocket == INVALID_SOCKET) {
        cerr << WSAGetLastErrorMessage("Error at socket()") << endl;
		WSACleanup();
		return 1;
	}
	char* option = "1";
	setsockopt(ServerSocket, SOL_SOCKET, SO_REUSEADDR, option, sizeof(option)); //allow local address reuse

    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port for the socket that is being bound.
	int port=5001;
    
	//Recuperation de l'adresse locale
	hostent *thisHost;
	thisHost=gethostbyname("");
	char* ip;
	ip=inet_ntoa(*(struct in_addr*) *thisHost->h_addr_list);
	printf("Adresse locale trouvee %s : \n\n",ip);
	sockaddr_in service;
    service.sin_family = AF_INET;
    //service.sin_addr.s_addr = inet_addr("127.0.0.1");
	//	service.sin_addr.s_addr = INADDR_ANY;
	service.sin_addr.s_addr = inet_addr(ip);
    service.sin_port = htons(port);

    if (bind(ServerSocket, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR) {
		cerr << WSAGetLastErrorMessage("bind() failed.") << endl;
		closesocket(ServerSocket);
		WSACleanup();
		return 1;
	}
	
	//----------------------
	// Listen for incoming connection requests.
	// on the created socket
	if (listen(ServerSocket, 30) == SOCKET_ERROR) {
		cerr << WSAGetLastErrorMessage("Error listening on socket.") << endl;
		closesocket(ServerSocket);
		WSACleanup();
		return 1;
	}


	printf("En attente des connections des clients sur le port %d...\n\n",ntohs(service.sin_port));

    while (true) {	

		sockaddr_in sinRemote;
		 int nAddrSize = sizeof(sinRemote);
		// Create a SOCKET for accepting incoming requests.
		// Accept the connection.
		 SOCKET sd = accept(ServerSocket, (sockaddr*)&sinRemote, &nAddrSize);
        if (sd != INVALID_SOCKET) {
			cout << "Connection acceptee De : " <<
                    inet_ntoa(sinRemote.sin_addr) << ":" <<
                    ntohs(sinRemote.sin_port) << "." <<
                    endl;

			send(sd, "1. la temperature qu'il fera a une heure de la journee courante", TAILLE_OPTIONS, 0);
			send(sd, "2. l'heure du coucher du soleil dans la journee en cours", TAILLE_OPTIONS, 0);
			send(sd, "3. l'heure de levee de soleil a la prochaine journee", TAILLE_OPTIONS, 0);
			send(sd, "4. la possibilite qu'il pleuve ou non dans la journee", TAILLE_OPTIONS, 0);
			send(sd, "5. la possibilite qu'il pleuve ou non la prochaine journee", TAILLE_OPTIONS, 0);
			send(sd, "6. la possibilite qu'il neige ou non dans la journee", TAILLE_OPTIONS, 0);
			send(sd, "7. la possibilite qu'il neige ou non la prochaine journee", TAILLE_OPTIONS, 0);

			send(sd, "FIN", TAILLE_OPTIONS, 0);

			/*
			1. la température qu'il fera à une heure de la journée courante, 
			2. l'heure du coucher du soleil dans la journée en cours, 
			3. l'heure de levée de soleil à la prochaine journée, 
			4. la possibilité qu'il pleuve ou non dans la journée, 
			5. la possibilité qu'il pleuve ou non la prochaine journée, 
			6. la possibilité qu'il neige ou non dans la journée, 
			7. la possibilité qu'il neige ou non la prochaine journée. 
			*/

            DWORD nThreadID;
            CreateThread(0, 0, EchoHandler, (void*)sd, 0, &nThreadID);
        }
        else {
            cerr << WSAGetLastErrorMessage("Echec d'une connection.") << 
                    endl;
           // return 1;
        }
    }
  
    // No longer need server socket
	closesocket(ServerSocket);

    WSACleanup();
    return 0;
}


//// EchoHandler ///////////////////////////////////////////////////////
// Handles the incoming data by reflecting it back to the sender.

DWORD WINAPI EchoHandler(void* sd_) 
{
	//cout << "EchoHandler\n";
	SOCKET sd = (SOCKET)sd_;

	// Read Data from client
	char readBuffer[TAILLE_OPTIONS_CHOISIES], outBuffer[TAILLE_RETOUR];
	int readBytes;


	readBytes = recv(sd, readBuffer, TAILLE_OPTIONS_CHOISIES, 0);
	if (readBytes > 0)
	{

		cout << "Received " << readBytes << " bytes from client." << endl;
		cout << "Received " << readBuffer << " from client." << endl;
		//DoSomething(readBuffer, outBuffer);

		std::string message = "";
		for(int i=0; i<TAILLE_OPTIONS_CHOISIES; i++)
		{
			if(readBuffer[i] == ' ')
				break;

			if(readBuffer[i] == '-')
				continue;

			//caller fonction qui prend un char en param et me retourne un string
			//updater message avec le retour de la fonction caller
			char* tempChar = reponseService(readBuffer[i]);
			for(int j =0; j<TAILLE_RETOUR; j++)
			{
				outBuffer[j] = tempChar[j];
			}
			send(sd, outBuffer, TAILLE_RETOUR, 0);
		}

		send(sd, "FIN", TAILLE_RETOUR, 0);
	}
	else if (readBytes == SOCKET_ERROR)
	{
		cout << WSAGetLastErrorMessage("Echec de la reception !") << endl;
	}
	//cout << "EchoHandler closed socket\n";
	closesocket(sd);
	

	return 0;
}

char* reponseService(char numeroService){
	char resultat[TAILLE_RETOUR];
	int i=0;
	if(numeroService == '1'){
		sprintf(resultat, "Temperature a %d:%d : %d degres celcius", (rand() % 24), (rand() % 60), ((rand() % 15) + 20));
		return resultat;
	}
	if(numeroService =='2'){
		sprintf(resultat, "Coucher du soleil : %d:%d%d",  (rand() % 4 +19), (rand() % 6), (rand() % 10));
		return resultat;
	}
	if(numeroService=='3'){
		sprintf(resultat, "Lever du soleil a la prochaine journee : 0%d:%d%d",  (rand() % 3 +4), (rand() % 6), (rand() % 10));
		return resultat;
	}
	if(numeroService=='4'){
		int i= rand() %2;
		if (i==0){
			sprintf(resultat, "Pluie dans la journee : Oui");
		}
		else {
			sprintf(resultat, "Pluie dans la journee : Non");
		}
		return resultat;
	}
	if(numeroService=='5'){
		int i= rand() %2;
		if (i==0){
			sprintf(resultat, "pluie dans la prochaine journee : Oui");
		}
		else {
			sprintf(resultat, "pluie dans la prochaine journee : Non");
		}
		return resultat;
	}
	if(numeroService=='6'){
		int i= rand() %2;
		if (i==0){
			sprintf(resultat, "Neige dans la journee : Oui");
		}
		else {
			sprintf(resultat, "Neige dans la journee : Non");
		}
		return resultat;
	}
	if(numeroService=='7'){
		int i= rand() %2;
		if (i==0){
			sprintf(resultat, "Neige dans la prochaine journee : Oui");
		}
		else {
			sprintf(resultat, "Neige dans la prochaine journee : Non");
		}
		return resultat;
	}
	sprintf(resultat, "Ce service n'existe pas");
	return resultat;
}