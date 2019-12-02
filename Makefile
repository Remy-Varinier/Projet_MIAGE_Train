pathClient = Client/
pathServeur = Serveur/
pathCommonSrc = Common/Sources/
pathCommonHead = Common/Headers/

all : client serveur

client.o : $(pathClient)client.c $(pathCommonHead)reseau.h
	gcc -c -Wall $(pathClient)client.c

serveur.o : $(pathServeur)serveur.c $(pathCommonHead)reseau.h
	gcc -c -Wall $(pathServeur)serveur.c
	
reseau.o : $(pathCommonSrc)reseau.c
	gcc -c -Wall $(pathCommonSrc)reseau.c
	
serveur : reseau.o serveur.o
	gcc  reseau.o serveur.o -o $(pathServeur)serveur
	
client : reseau.o client.o
	gcc  reseau.o client.o -o $(pathClient)client
	
clean:
	rm -rf *.o $(pathClient)client $(pathServeur)serveur

