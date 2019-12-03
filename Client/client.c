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
#include "gestion_erreur_client.h"

// remplacer '\n' par '\0'
void enleverBack(char *entree){
	int taille = strlen(entree);
	if(entree[taille-1] == '\n'){
		entree[taille-1] = '\0';
	}
}

// lecture de l'entrée du client au clavier
void lectureClient(char* message, char* res){
	printf("%s",message);
	fgets(res, MAX, stdin);
	enleverBack(res);
}

int main(int argc,char *argv[]){
	char arret[MAX] = "Non";
	char ville_depart[MAX];
	char ville_arrivee[MAX];
	char horaire[MAX];
	char horaire1[MAX];
	char horaire2[MAX];
	char param[MAX];
	char *msg = (char*) malloc(MAX);
	int size;
	int err;
	char pointV[2] = ";";
	int echange = socketClient("localhost", PORT);
	
	do{
		msg = "Entrez une ville de départ :\n";
		lectureClient(msg, ville_depart);
		
		msg = "Entrez une ville d'arrivée :\n";
		lectureClient(msg, ville_arrivee);
		
		
		size = strlen(ville_depart)+strlen(ville_arrivee)+3+20;
		char *entree = (char*) malloc(size);
		
		printf("Voulez-vous entrer :\n\tUn horaire de départ ? (1)\n\tUn intervalle pour l'horaire de départ ? (2)\n\tPas de préférence d'horaire ? (0)\n");
		fgets(param, MAX, stdin);
		enleverBack(param);
		
		if(strcmp(param,"1") == 0){
			
			msg = "Entrez un horaire de départ : (HH:MM)\n";
			lectureClient(msg, horaire);
			err = horaire_valide(horaire);
			while(err == 0){
				msg = "Erreur de format\nEntrez a nouveau un horaire de départ : (HH:MM)\n";
				lectureClient(msg, horaire);
				err = horaire_valide(horaire);
			}
			
			sprintf(entree,"%s;%s;%s",ville_depart,ville_arrivee,horaire);
			
		} else if(strcmp(param,"2") == 0){
			strcat(entree, pointV);
			msg = "Entrez un horaire de départ min : (HH:MM)\n";
			lectureClient(msg, horaire1);
			err = horaire_valide(horaire1);
			while(err == 0){
				msg = "Erreur de format\nEntrez a nouveau un horaire de départ min : (HH:MM)\n";
				lectureClient(msg, horaire1);
				err = horaire_valide(horaire1);
			}
			
			msg = "Entrez un horaire de départ max : (HH:MM)\n";
			lectureClient(msg, horaire2);
			err = horaire_valide(horaire2);
			while(err == 0){
				msg = "Erreur de format\nEntrez a nouveau un horaire de départ max : (HH:MM)\n";
				lectureClient(msg, horaire2);
				err = horaire_valide(horaire2);
			}
			sprintf(entree,"%s;%s;%s;%s",ville_depart,ville_arrivee,horaire1,horaire2);
		}else{
			sprintf(entree,"%s;%s",ville_depart,ville_arrivee);
		}
		
		write(echange, entree, strlen(entree)+1);
		free(entree);
		
		printf("Voulez-vous faire une nouvelle recherche ? (Oui/Non)\n");
		fgets(arret, MAX, stdin);
		enleverBack(arret);
		
	}while(strcmp(arret, "Non") != 0);
	return 0;
}
