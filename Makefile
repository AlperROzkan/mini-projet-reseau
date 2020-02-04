CC=gcc
OPTS=-Wall -pedantic -std=c11

objects=client.o \
		envoyer.o \
		programmePC1.o \
		programmePC2.o \
		recevoir.o \
		serveur.o

all: main

main: build $(objects) PC1 PC2
	@echo project compiled

PC1: client.c envoyer.c recevoir.c serveur.c programmePC1.c
	$(CC) $(OPTS) -o build/$@ $^

PC2: client.c envoyer.c recevoir.c serveur.c programmePC2.c
	$(CC) $(OPTS) -o build/$@ $^

# pour créer tous les fichiers à compiler
#%.o: %.c
#	$(CC) $(OPTS) -c $< -o build/$@

# création du dossier de build
build:
	@mkdir build

# cible de nettoyage de build
clean:
	rm -rf build