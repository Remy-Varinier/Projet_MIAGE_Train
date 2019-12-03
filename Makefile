CFLAGS=-std=c99
pathClient = Client/
pathServeur = Serveur/
pathCommonSrc = Common/Sources/
pathCommonHead = Common/Headers/
pathCommonObj = Common/Objects/

all : reseau.o client serveur 

client.o : $(pathClient)client.c $(pathCommonHead)reseau.h
	gcc -c -Wall $(pathClient)client.c -o $(pathClient)client.o

serveur.o : $(pathServeur)serveur.c $(pathCommonHead)reseau.h
	gcc -c -Wall $(pathServeur)serveur.c -o $(pathServeur)serveur.o
	
reseau.o : $(pathCommonSrc)reseau.c
	gcc -c -Wall $(pathCommonSrc)reseau.c -o $(pathCommonObj)reseau.o
	
serveur : $(pathCommonObj)reseau.o $(pathServeur)serveur.o
	gcc $(pathCommonObj)reseau.o $(pathServeur)serveur.o -o $(pathServeur)serveur
	
client : $(pathCommonObj)reseau.o $(pathClient)client.o
	gcc $(pathCommonObj)reseau.o $(pathClient)client.o -o $(pathClient)client
	
clean:
	rm -rf */*/*.o */*.o $(pathClient)client $(pathServeur)serveur

