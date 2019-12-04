CFLAGS=-std=c99
pathClient = Client/
pathServeur = Serveur/
pathCommonSrc = Common/Sources/
pathCommonHead = Common/Headers/
pathCommonObj = Common/Objects/

all : lire_fichier.o reseau.o client serveur 

client.o : $(pathClient)client.c $(pathCommonHead)reseau.h $(pathClient)gestion_erreur_client.h
	gcc -c -Wall $(pathClient)client.c -o $(pathClient)client.o

serveur.o : $(pathServeur)serveur.c $(pathCommonHead)reseau.h $(pathServeur)lire_fichier.h $(pathServeur)serveur.h $(pathServeur)fonctions_trains.h
	gcc -c -Wall $(pathServeur)serveur.c -o $(pathServeur)serveur.o
	
reseau.o : $(pathCommonSrc)reseau.c $(pathCommonHead)reseau.h
	gcc -c -Wall $(pathCommonSrc)reseau.c -o $(pathCommonObj)reseau.o
	
gestion_erreur_client.o : $(pathClient)gestion_erreur_client.c $(pathClient)gestion_erreur_client.h
	gcc -c -Wall $(pathClient)gestion_erreur_client.c -o $(pathClient)gestion_erreur_client.o
	
lire_fichier.o : $(pathServeur)lire_fichier.c $(pathServeur)serveur.h $(pathServeur)lire_fichier.h
	gcc -c -Wall $(pathServeur)lire_fichier.c -o $(pathServeur)lire_fichier.o

fonctions_trains.o : $(pathServeur)fonctions_trains.c $(pathServeur)fonctions_trains.h $(pathServeur)serveur.h $(pathServeur)module_heure.h
	gcc -c -Wall $(pathServeur)fonctions_trains.c -o $(pathServeur)fonctions_trains.o

module_heure.o : $(pathServeur)module_heure.c $(pathServeur)serveur.h
	gcc -c -Wall $(pathServeur)module_heure.c -o $(pathServeur)module_heure.o
	
serveur : $(pathCommonObj)reseau.o $(pathServeur)serveur.o $(pathServeur)lire_fichier.o $(pathServeur)fonctions_trains.o $(pathServeur)module_heure.o
	gcc $(pathCommonObj)reseau.o $(pathServeur)serveur.o $(pathServeur)lire_fichier.o $(pathServeur)fonctions_trains.o $(pathServeur)module_heure.o -o $(pathServeur)serveur
	
client : $(pathCommonObj)reseau.o $(pathClient)client.o $(pathClient)gestion_erreur_client.o
	gcc $(pathCommonObj)reseau.o $(pathClient)gestion_erreur_client.o $(pathClient)client.o -o $(pathClient)client
	
clean:
	rm -rf */*/*.o */*.o $(pathClient)client $(pathServeur)serveur

