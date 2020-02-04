CC=gcc
OPTS=-Wall -pedantic -std=c11

objects=client.o \
		envoyer.o \
		programmePC1.o \
		programmePC2.o \
		recevoir.o \
		serveur.c

all: main

main: build $(objects)
	@echo project compiled

# pour créer tous les fichiers à compiler
%.o: %.c 
	$(CC) $(OPTS) -c $< -o build/$@

# création du dossier de build
build:
	@mkdir build

# cible de nettoyage de build
clean:
	rm -rf build