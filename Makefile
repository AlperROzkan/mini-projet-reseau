CC=gcc
OPTS=-Wall -pedantic -std=c11

objects=main.o \
		truc.o

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