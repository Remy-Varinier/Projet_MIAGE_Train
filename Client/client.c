#include <stdio.h>
#include <string.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/uio.h>

#include "../Common/Headers/reseau.h"

int main(int argc,char *argv[]){ 
	int echange = socketClient("localhost",4242);
	printf("Un client est connecté \n");
	char *message = "Bonjour";
	write(echange, message, strlen(message)+1);
	char tampon[MAX];
	int nbLus = read(echange, tampon, MAX);
	printf("J'ai lu '%s' \n",tampon);
	return 0;
}
