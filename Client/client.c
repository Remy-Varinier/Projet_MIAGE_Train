#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/uio.h>

#include "../Common/Headers/reseau.h"

void enleverBack(char *entree){
	int taille = strlen(entree);
	if(entree[taille-1] == '\n'){
		entree[taille-1] = '\0';
	}
}

void lectureClient(char* message, char* res){
	printf("%s",message);
	fgets(res, MAX, stdin);
	enleverBack(res);
}

int main(int argc,char *argv[]){
	char* ville_depart = (char*) malloc(MAX);
	char* ville_arrivee = (char*) malloc(MAX);
	char* horaire = (char*) malloc(MAX);
	char* horaire1 = (char*) malloc(MAX);
	char* horaire2 = (char*) malloc(MAX);
	char* param = (char*) malloc(2);
	char* entree = (char*) malloc(MAX);
	int echange = socketClient("localhost", PORT);
	char *msg;
	int size; 
	char pointV[1] = ";";
	do{
		msg = "Entrez une ville de départ :\n";
		lectureClient(msg, ville_depart);
		
		
		msg = "Entrez une ville d'arrivée :\n";
		lectureClient(msg, ville_arrivee);
		
		size = strlen(entree)+strlen(ville_arrivee)+strlen(ville_arrivee)+3+20;
		entree = (char*) malloc(size);
		
		strcat(entree,ville_arrivee);
		strcat(entree, pointV);
		
		strcat(entree,ville_depart);
		strcat(entree, pointV);
		
		printf("Voulez-vous entrer :\n\tUn horaire de départ ? (1)\n\tUn intervalle pour l'horaire de départ ? (2)\n\tPas de préférence d'horaire ? (0)\n");
		scanf("%s",param);
		
		if(strcmp(param,"1") == 0){
			msg = "Entrez un horaire de départ : (HH:MM)\n";
			lectureClient(msg, ville_arrivee);
			
			strcat(entree,ville_depart);
			strcat(entree,pointV);
			
		} else if(strcmp(param,"2") == 0){
			msg = "Entrez un horaire de départ min :\n";
			lectureClient(msg, horaire1);
			
			msg = "Entrez un horaire de départ max :\n";
			lectureClient(msg, horaire2);
			
			strcat(entree,horaire1);
			strcat(entree,pointV);
			
			strcat(entree,horaire2);
		}
		write(echange, entree, strlen(entree)+1);
		
	}while(strcmp(entree, "exit") != 0);
	return 0;
}
