#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

int socketServeur(int port){
	int ecoute = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4242);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(ecoute,(struct sockaddr *)&sin,sizeof(sin));
	listen(ecoute, 5); //écoute de la socket ecoute
	return ecoute;
}

int socketClient(char nomServeur[], int port){
	int ecoute = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4242);
	struct hostent *host;
	host = gethostbyname("localhost");
	memcpy(&sin.sin_addr.s_addr,host->h_addr_list[0],sizeof(u_long));
	int echange = connect(ecoute,(struct sockaddr *)&sin,sizeof(sin));
	return echange;
}