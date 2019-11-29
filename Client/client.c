#include <stdio.h>
#include <string.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX 100

int main(int argc,char *argv[]){ 
	
	int ecoute = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(7777);
	struct hostent *host;
	host = gethostbyname("localhost");
	memcpy(&server.sin_addr.s_addr,host->h_addr_list[0],sizeof(u_long));
	int echange = connect(ecoute, (struct sockaddr *)&server, sizeof(server));
	printf("Un client est connecté \n");
	char *message = "Bonjour";
	write(echange, message, strlen(message)+1);
	char tampon[MAX];
	int nbLus = read(echange, tampon, MAX);
	printf("J'ai lu '%s' \n",tampon);
	return 0;
}
