CFLAGS=-std=c99
pathClient = Client/
pathServeur = Serveur/
pathCommonSrc = Common/Sources/
pathCommonHead = Common/Headers/
pathCommonObj = Common/Objects/

all : lire_fichier.o reseau.o client serveur 

client.o : $(pathClient)client.c $(pathCommonHead)reseau.h $(pathClient)gestion_erreur_client.h
	gcc -c -Wall $(pathClient)client.c -o $(pathClient)client.o

serveur.o : $(pathServeur)serveur.c $(pathCommonHead)reseau.h $(pathServeur)lire_fichier.h $(pathServeur)serveur.h
	gcc -c -Wall $(pathServeur)serveur.c -o $(pathServeur)serveur.o
	
reseau.o : $(pathCommonSrc)reseau.c
	gcc -c -Wall $(pathCommonSrc)reseau.c -o $(pathCommonObj)reseau.o
	
gestion_erreur_client.o : $(pathClient)gestion_erreur_client.c
	gcc -c -Wall $(pathClient)gestion_erreur_client.c -o $(pathClient)gestion_erreur_client.o
	
lire_fichier.o : $(pathServeur)lire_fichier.c $(pathServeur)serveur.h $(pathServeur)lire_fichier.h
	gcc -c -Wall $(pathServeur)lire_fichier.c -o $(pathServeur)lire_fichier.o
	
serveur : $(pathCommonObj)reseau.o $(pathServeur)serveur.o $(pathServeur)lire_fichier.o
	gcc $(pathCommonObj)reseau.o $(pathServeur)serveur.o $(pathServeur)lire_fichier.o -o $(pathServeur)serveur
	
client : $(pathCommonObj)reseau.o $(pathClient)client.o $(pathClient)gestion_erreur_client.o
	gcc $(pathCommonObj)reseau.o $(pathClient)gestion_erreur_client.o $(pathClient)client.o -o $(pathClient)client
	
clean:
	rm -rf */*/*.o */*.o $(pathClient)client $(pathServeur)serveur

