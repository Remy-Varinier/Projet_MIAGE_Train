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

#define MAX_CAR 80
#define MAX_RES 50

/*
	Structure servant à stocker les resultats retounés par le serveur
	avant de les afficher
*/
typedef struct {
	char numTrain[MAX_CAR];;
	char villeDep[MAX_CAR];
	char villeArr[MAX_CAR];
	char hDep[MAX_CAR];
	char hArr[MAX_CAR];
	char prix[MAX_CAR];
	char duree[MAX_CAR];
	char option[MAX_CAR];
	char prixModif[MAX_CAR];
}Resultat;

/*
	Prend un type resultat (une info de train) en paramètre et l'affiche avec 
	des codes couleurs et un format particulier
*/
void afficheResultat(Resultat r){
	char optionPrix[MAX_CAR] = "";
	if(strcmp(r.option, "NULL") != 0)
		sprintf(optionPrix, "Prix avec %s : %s",r.option,r.prixModif);
	
	printf("\033[0;32mTrain n°: %s\033[0m\t\t\033[1;34m%s\033[0m (\033[0;36m%s\033[0m) \t\033[1;34m%s\033[0m (\033[0;36m%s\033[0m)\n\tDurée:%s\tPrix:%s€\t%s\n\n",r.numTrain, r.villeDep, r.hDep, r.villeArr, r.hArr, r.duree, r.prix,optionPrix);
}

// Remplace dernier caratère par '\0' si il s'agit d'un '\n'
void enleverBack(char *entree){
	int taille = strlen(entree);
	if(entree[taille-1] == '\n'){
		entree[taille-1] = '\0';
	}
}

// Affichage d'un message passé et lecture de l'entrée du client au clavier
void lectureClient(char* message, char* res){
	printf("%s",message);
	fgets(res, MAX, stdin);
	enleverBack(res);
}


int main(int argc,char *argv[]){
	
	// Test si les paramètres serveur et port sont bien passés en paramètre du client
	if(argc < 3){
		printf("Erreur d'usage : client serveur port\n");
		exit(1);
	}
	
	// Initialisation de nos variables
	char listGare[MAX] = "";
	char arret[MAX] = "Non";
	char ville_depart[MAX];
	char ville_arrivee[MAX];
	char horaire[MAX];
	char horaire1[MAX];
	char horaire2[MAX];
	char trajet[MAX];
	char param[MAX];
	char *msg = (char*) malloc(MAX);
	int size;
	int err;
	
	// Connexion au serveur 
	int echange = socketClient(argv[1], atoi(argv[2]));
	
	// Récupère la liste des gares pour que le client sache quel choix sont disponibles
	read(echange, listGare, MAX);
	
	// Utilise le programme clear de bash
	system("clear");
	
	printf("Cher utilisateur, bienvenue sur la consultation des trains en ligne\n");
	printf("La liste des villes disponibles est: \033[1;34m%s\33[0m.\n\n",listGare);
	
	do{
		// Début de la saisie de la demande par le client
		
		msg = "Veuillez indiquer une ville de départ :\n";
		lectureClient(msg, ville_depart);
		if(strlen(ville_depart) == 0)
			strcpy(ville_depart,"a");
		
		msg = "\nVeuillez indiquer une ville d'arrivée :\n";
		lectureClient(msg, ville_arrivee);
		if(strlen(ville_arrivee) == 0)
			strcpy(ville_arrivee,"a");
		
		size = strlen(ville_depart)+strlen(ville_arrivee)+3+20;
		char *entree = (char*) malloc(size);
		
		printf("\nVoulez-vous entrer :\n\tUn horaire de départ ? (\033[0;32m1\33[0m)\n\tUn intervalle pour l'horaire de départ ? (\033[0;32m2\33[0m)\n\tPas de préférence d'horaire ? (\033[0;32m0\33[0m)\n");
		fgets(param, MAX, stdin);
		enleverBack(param);
		
		if(strcmp(param,"1") == 0){
			
			msg = "\nVeuillez entrer un horaire de départ : (\033[0;32mHH:MM\33[0m)\n";
			lectureClient(msg, horaire);
			err = horaire_valide(horaire);
			
			while(err == 0){
				msg = "Attention, erreur de format. \nEntrez a nouveau un horaire de départ : (\033[0;32mHH:MM\33[0m)\n";
				lectureClient(msg, horaire);
				err = horaire_valide(horaire);
			}
			
			sprintf(entree,"%s;%s;%s;0",ville_depart,ville_arrivee,horaire);
			
		} else if(strcmp(param,"2") == 0){
			msg = "\nVeuillez entrer un horaire de départ minimum : (HH:MM)\n";
			lectureClient(msg, horaire1);
			err = horaire_valide(horaire1);
			
			while(err == 0){
				msg = "Attention, erreur de format\nEntrez a nouveau un horaire de départ min : (\033[0;32mHH:MM\33[0m)\n";
				lectureClient(msg, horaire1);
				err = horaire_valide(horaire1);
			}
			
			msg = "\nVeuillez entrez un horaire de départ maximum : (\033[0;32mHH:MM\33[0m)\n";
			lectureClient(msg, horaire2);
			err = horaire_valide(horaire2);
			
			while(err == 0){
				msg = "Attention, erreur de format\nEntrez a nouveau un horaire de départ max : (\033[0;32mHH:MM\33[0m)\n";
				lectureClient(msg, horaire2);
				err = horaire_valide(horaire2);
			}
			
			msg = "\nVoulez-vous :\n\tLe trajet au meilleur prix ? (\033[0;32m1\33[0m)\n\tLe trajet de durée optimum ? (\033[0;32m2\33[0m)\n\tTous les trains ? (\033[0;32m0\33[0m)\n";
			lectureClient(msg, trajet);
			
			sprintf(entree,"%s;%s;%s;%s;%s",ville_depart,ville_arrivee,horaire1,horaire2,trajet);
		
		}else{
			msg = "\nVoulez-vous :\n\tLe trajet au meilleur prix ? (\033[0;32m1\33[0m)\n\tLe trajet de durée optimum ? (\033[0;32m2\33[0m)\n\tTous les trains ? (\033[0;32m0\33[0m)\n";
			lectureClient(msg, trajet);
			
			if(strcmp(trajet,"2") != 0 && strcmp(trajet,"1") != 0)
				strcpy(trajet,"0");
				
			sprintf(entree,"%s;%s;%s",ville_depart,ville_arrivee,trajet);
		}
		
		// Envoie la demande du client au serveur
		write(echange, entree, strlen(entree)+1);
		free(entree);
		
		//utilise le programme clear de bash
		system("clear");
		
		
		char tampon[MAX]="";
		
		// Récupération des résultats de la demande
		int lu = read(echange, tampon, MAX);
		
		char* affichage = NULL;
		char *ligneRes[MAX];
		int i = 0;
		Resultat resultats[MAX_RES];
		affichage = strtok(tampon, "!");  
		
		
		printf("Voici le(s) resultat(s) de votre recherche:\n\n");
		//tant qu'il reste des trains
		while(affichage != NULL){
			ligneRes[i] = affichage;
			affichage = strtok(NULL, "!");
			i++;
		}
		for(int j = 0; j<i; j++){
			affichage = NULL;
			int k = 0;
			affichage = strtok(ligneRes[j], ";");  
			printf("\t========================================\n");
			int reduc=0;
			//tant qu'il reste des paramètres
			while(affichage != NULL){
				switch(k){
					case 0:
						strcpy(resultats[j].numTrain,affichage);
						
						break;
					case 1:
						strcpy(resultats[j].villeDep,affichage);
						break;
					case 2:
						strcpy(resultats[j].villeArr,affichage);
						break;
					case 3:
						strcpy(resultats[j].hDep,affichage);
						break;
					case 4:
						strcpy(resultats[j].hArr,affichage);
						break;
					case 5:
						strcpy(resultats[j].duree,affichage);
						break;
					case 6:
						strcpy(resultats[j].prix,affichage);
						break;
					case 7:
						strcpy(resultats[j].option,affichage);
						break;
					case 8:
						strcpy(resultats[j].prixModif,affichage);
						break;
				}
				affichage = strtok(NULL, ";");
				k++;
			}
			
			afficheResultat(resultats[j]);
		}
		if(i == 0)
			printf("\033[0;31mAucun train ne correspond à votre demande... \n\n\033[0m");
		
		printf("Souhaitez-vous faire une nouvelle recherche ? (\033[0;32mOui\33[0m/\033[0;32mNon\33[0m)\n");
		fgets(arret, MAX, stdin);
		enleverBack(arret);
		//utilise le programme clear de bash
		system("clear");
	}while(strcmp(arret, "Non") != 0);
	
	// Envoie au serveur l'information de déconnexion
	write(echange, "exit", strlen("exit")+1);
	
	return 0;
}
