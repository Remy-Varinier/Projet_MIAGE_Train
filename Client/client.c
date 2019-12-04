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

	if(argc < 3){
		printf("Erreur d'usage : client serveur port\n");
		exit(1);
	}

	char tampon[MAX];
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

	int echange = socketClient(argv[1], atoi(argv[2]));
	printf("Cher utilisateur, bienvenue sur la consultation des trains en ligne.\n");
	printf("La liste des villes disponibles est: Valence, Grenoble, Montélimar, Paris Gare de Lyon, Marseille, Lyon Part-Dieu et Strasbourg.\n");
	do{
		msg = "Veuillez indiquer une ville de départ :\n";
		lectureClient(msg, ville_depart);
		
		msg = "Veuillez indiquer une ville d'arrivée :\n";
		lectureClient(msg, ville_arrivee);
		
		size = strlen(ville_depart)+strlen(ville_arrivee)+3+20;
		char *entree = (char*) malloc(size);
		
		printf("Voulez-vous entrer :\n\tUn horaire de départ ? (1)\n\tUn intervalle pour l'horaire de départ ? (2)\n\tPas de préférence d'horaire ? (0)\n");
		fgets(param, MAX, stdin);
		enleverBack(param);
		
		if(strcmp(param,"1") == 0){
			
			msg = "Veuillez entrer un horaire de départ : (HH:MM)\n";
			lectureClient(msg, horaire);
			err = horaire_valide(horaire);
			while(err == 0){
				msg = "Attention, erreur de format. \nEntrez a nouveau un horaire de départ : (HH:MM)\n";
				lectureClient(msg, horaire);
				err = horaire_valide(horaire);
			}
			msg = "Voulez-vous :\n\tLe trajet au meilleur prix ? (1)\n\tLe trajet de durée optimum ? (2)\n\tTous les trains ? (0)\n";
			lectureClient(msg, trajet);
			sprintf(entree,"%s;%s;%s;%s",ville_depart,ville_arrivee,horaire,trajet);
		} else if(strcmp(param,"2") == 0){
			msg = "Veuillez entrer un horaire de départ minimum : (HH:MM)\n";
			lectureClient(msg, horaire1);
			err = horaire_valide(horaire1);
			while(err == 0){
				msg = "Attention, erreur de format\nEntrez a nouveau un horaire de départ min : (HH:MM)\n";
				lectureClient(msg, horaire1);
				err = horaire_valide(horaire1);
			}
			
			msg = "Veuillez entrez un horaire de départ maximum : (HH:MM)\n";
			lectureClient(msg, horaire2);
			err = horaire_valide(horaire2);
			while(err == 0){
				msg = "Attention, erreur de format\nEntrez a nouveau un horaire de départ max : (HH:MM)\n";
				lectureClient(msg, horaire2);
				err = horaire_valide(horaire2);
			}
			msg = "Voulez-vous :\n\tLe trajet au meilleur prix ? (1)\n\tLe trajet de durée optimum ? (2)\n\tTous les trains ? (0)\n";
			lectureClient(msg, trajet);
			sprintf(entree,"%s;%s;%s;%s;%s",ville_depart,ville_arrivee,horaire1,horaire2,trajet);
		}else{
			msg = "Voulez-vous :\n\tLe trajet au meilleur prix ? (1)\n\tLe trajet de durée optimum ? (2)\n\tTous les trains ? (0)\n";
			lectureClient(msg, trajet);
			sprintf(entree,"%s;%s;%s",ville_depart,ville_arrivee,trajet);
		}
		
		write(echange, entree, strlen(entree)+1);
		free(entree);
		
		printf("Souhaitez-vous faire une nouvelle recherche ? (Oui/Non)\n");
		fgets(arret, MAX, stdin);
		enleverBack(arret);
		
	}while(strcmp(arret, "Non") != 0 || strcmp(arret, "non") != 0);

	write(echange, "exit", strlen("exit")+1);

	int lu = read(echange, tampon, MAX);

    char* pv = NULL;
    char ligneRes[MAX];
    int i = 0;
    affichage = strtok(tampon, "!");  
    //tant que la ligne n'est pas vide
    while(pv != NULL){
        strcpy(ligneRes[i],pv);
        pv = strtok(NULL, "!");
        i++;
    }
    for(int j = 0; j<i; j++){
    	pv = NULL;
    	int k = 0;
    	affichage = strtok(ligneRes[j], ";");  
    	//tant que la ligne n'est pas vide
    	while(pv != NULL){
        	switch(k){
        		case 0:
        			printf("Numéro du train : %s\n",pv);
        			break;
        		case 1:
        			printf("Ville de départ : %s\n",pv);
        			break;
        		case 2:
        			printf("Ville d'arrivée : %s\n",pv);
        			break;
        		case 3:
        			printf("Heure de départ : %s\n",pv);
        			break;
        		case 4:
        			printf("Heure d'arrivée : %s\n",pv);
        			break;
        		case 5:
        			printf("Prix du trajet : %s\n",pv);
        			break;
        		case 6:
        			printf("Option (REDUC/SUPPL) : %s\n",pv);
        			break;
        	}
        	pv = strtok(NULL, ";");
        	k++;
    	}
    }
	return 0;
}
