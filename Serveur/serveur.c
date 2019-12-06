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
}

void fils(int echange){
	printf("Un client s'est connecté.\n");
	char tampon[MAX];
	char listGare[MAX] = "";
	bool fin = true;
	char *pv;
	char commande[4][MAX];
	FILE *fichier = NULL;
	struct TabTrain tab_train;
	tab_train.taille = 0;
	lecture_fichier(fichier,&tab_train);
	
	int k = 1;
	sprintf(listGare,"%s%s",listGare, tab_train.trains[0].ville_dep);
	for(int i = 1; i < tab_train.taille;i++){
		char * c = strstr(listGare, tab_train.trains[i].ville_dep);
		if(c == NULL){
			sprintf(listGare,"%s,%s",listGare, tab_train.trains[i].ville_dep);
			k++;
		}
		if(k == 3){
			sprintf(listGare,"%s\n",listGare);
			k = 0;
		}
	}
	write(echange,listGare,strlen(listGare)+1);
	
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
					if(strcmp(commande[i-1],"2") == 0 )
						tab_res = duree_optimum(tab_res);
					else if(strcmp(commande[i-1],"1") == 0 )
						tab_res = meilleur_prix(tab_res);
					reponse(tab_res, echange);
					break;
				case 4:
					getTrainDep(tab_train, commande[0], commande[1], decoupe_horaire(commande[2]), &tab_res);
					reponse(tab_res, echange);
					break;
				case 5:
					getTrainDepArr(tab_train, commande[0], commande[1], decoupe_horaire(commande[2]), decoupe_horaire(commande[3]), &tab_res);
					
					if(strcmp(commande[i-1],"2") == 0 )
						tab_res = duree_optimum(tab_res);
					else if(strcmp(commande[i-1],"1") == 0 )
						tab_res = meilleur_prix(tab_res);
						
					reponse(tab_res, echange);
					break;
			}
        }
        
	}while(fin);	
	printf("Un client s'est déconnecté\n");
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
