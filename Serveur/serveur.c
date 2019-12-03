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

void fils(int echange){
	printf("une co\n");
	char tampon[MAX];
	bool fin = true;
	char *pv;
	char commande[4][MAX];
	do{
		int lu = read(echange, tampon, MAX);
		printf("J'ai lu : %s, int : %d\n", tampon, lu);
		fin = strcmp(tampon,"exit") != 0;
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
            FILE *fichier = NULL;
			struct TabTrain tab_train;
			tab_train.taille = 0;
			lecture_fichier(fichier,&tab_train);

			struct TabTrain tab_res;
			tab_res.taille = 0;

            switch(i){
				case 2:
					listBonnesVilles(tab_train, commande[0], commande[1], &tab_res);
					break;
				case 3:
					listHoraire(tab_train, commande[0], commande[1], decoupe_horaire(commande[2]), &tab_res);
					break;
				case 4:
					listTrancheHoraire(tab_train, commande[0], commande[1], decoupe_horaire(commande[2]), decoupe_horaire(commande[3]), &tab_res);
					break;
			}
            for(int k = 0; k<i;k++){
				printf("%s\n",commande[k]);
			}
        }
        
	}while(fin);	
}

int main(int argc,char *argv[]){
	pid_t id;
	int ecoute = socketServeur(atoi(argv[1]));
	do{
		printf("en attente de co : \n");
		int echange = accept(ecoute,NULL, NULL);
		printf("connecté : \n");
		id = fork();
		if(id == 0){
			fils(echange);
			close(ecoute);
			exit(0);
		}
	}while(true);
	return 0;
}
