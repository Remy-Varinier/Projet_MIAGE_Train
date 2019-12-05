#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/uio.h>

#include "../Common/Headers/reseau.h"
#include "serveur.h"
#include "lire_fichier.h"
#include "fonctions_trains.h"

void reponse(struct TabTrain tab, int echange){
	char resultat[MAX] = ""; 
	for(int i = 0; i < tab.taille;i++){
		struct Train t = tab.trains[i];
		struct Horaire h = minutesVersHeures(duree(t));
		sprintf(resultat,"%s%d;%s;%s;%02dh%02d;%02dh%02d;%02dh%02d;%.2f;%s;%.2f!", resultat,t.num_train, t.ville_dep, t.ville_arr,t.h_depart.heure, t.h_depart.minute, t.h_arrivee.heure, t.h_arrivee.minute, h.heure, h.minute,t.prix, t.option, option(t));
	}
	int taille = strlen(resultat);
	if(resultat[taille-1] == '!'){
		resultat[taille-1] = '\0';
	}
	write(echange,resultat,strlen(resultat)+1);
	printf("%s    nb: \n",resultat);
}

void fils(int echange){
	printf("Un client s'est connecté.\n");
	char tampon[MAX];
	bool fin = true;
	char *pv;
	char commande[4][MAX];
	FILE *fichier = NULL;
	struct TabTrain tab_train;
	tab_train.taille = 0;
	lecture_fichier(fichier,&tab_train);
	
	do{
		int lu = read(echange, tampon, MAX);
		fin = strcmp(tampon,"exit") != 0;
		struct TabTrain tab_res;
		tab_res.taille = 0;
		if(fin){
			int i = 0;
            pv=NULL;
            i=0;
            pv = strtok(tampon, ";");
            
            //tant que la ligne n'est pas vide
            while(pv != NULL){
                strcpy(commande[i],pv);
                pv = strtok(NULL, ";");
                i++;
            }
            switch(i){
				case 3:
					listBonnesVilles(tab_train, commande[0], commande[1], &tab_res);
					reponse(tab_res, echange);
					break;
				case 4:
					getTrainDep(tab_train, commande[0], commande[1], decoupe_horaire(commande[2]), &tab_res);
					reponse(tab_res, echange);
					break;
				case 5:
					getTrainDepArr(tab_train, commande[0], commande[1], decoupe_horaire(commande[2]), decoupe_horaire(commande[3]), &tab_res);
					reponse(tab_res, echange);
					break;
			}
            for(int k = 0; k<tab_res.taille;k++){
				printf("%d:%d\n",tab_res.trains[k].h_depart.heure,tab_res.trains[k].h_depart.minute);
			}
        }
        
	}while(fin);	
}

int main(int argc,char *argv[]){
	pid_t id;
	int ecoute = socketServeur(atoi(argv[1]));
	printf("Connexion... \n");
	do{
		int echange = accept(ecoute,NULL, NULL);
		id = fork();
		if(id == 0){
			fils(echange);
			close(ecoute);
			exit(0);
		}
	}while(true);
	return 0;
}
