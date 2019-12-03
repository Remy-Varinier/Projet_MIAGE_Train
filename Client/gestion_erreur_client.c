#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/uio.h>

#include "gestion_erreur_client.h"

int horaire_valide(char *horaire){
	//Renvoi 1 si l'horaire est au format HH:MM
	if((horaire[0] <= '1' && horaire[0] >= '0') && (horaire[1] <= '9' && horaire[1] >= '0') && (horaire[2] <= ':') && (horaire[3] <= '5' && horaire[3] >= '0') && (horaire[4] <= '9' && horaire[4] >= '0') && (horaire[5] <= '\0')){
		return 1;
	}else if((horaire[0] == '2') && (horaire[1] <= '3' && horaire[1] >= '0') && (horaire[2] <= ':') && (horaire[3] <= '5' && horaire[3] >= '0') && (horaire[4] <= '9' && horaire[4] >= '0') && (horaire[5] <= '\0')){
		return 1;
	}
	//Renvoi 0 sinon
	return 0;
}