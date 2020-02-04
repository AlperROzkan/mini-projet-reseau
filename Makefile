CC=gcc -Wall -pedantic -std=c11

all: main

main: build %.o
	@echo erith.img created

# pour créer tous les fichiers à compiler
%.o: %.c 
	$(CC) -c $< -o build/$@

# création du dossier de build
build:
	@mkdir build

# cible de nettoyage de build
clean:
	rm -rf build