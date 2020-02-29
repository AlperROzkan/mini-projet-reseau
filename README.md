# mini-projet-reseau
Mini projet de réseau, mise en place d'un protocole que nous avons nous même imaginez, basé sur un réseau en anneau.

Notre solution est disponible ici: https://docs.google.com/document/d/1zClrGa1IK80svNk5Ph1HbfgBGhPtSqRx7kItxv6QHrM/edit?usp=sharing

## Compilation
Compiler avec:

```bash
~$ cd mini-projet-reseau
~/mini-projet-reseau/$ MODE=Release
~/mini-projet-reseau/$ cmake . -Bbuild -DCMAKE_BUILD_TYPE=$MODE
~/mini-projet-reseau/$ cmake --build build --config $MODE
```

## Lancer le programme
Exemple avec quatre terminaux:
* `./build/connect 127.000.000.001 1111 127.000.000.002 2222`
* `./build/connect 127.000.000.002 2222 127.000.000.003 3333`
* `./build/connect 127.000.000.003 3333 127.000.000.004 4444`
* `./build/connect 127.000.000.004 4444 127.000.000.001 1111`

C'est l'exemple typique du token ring.

### Arguments
`./build/connect [mon ip] [port écoute] [ip suivant] [port envoie]`

*Nota bene*: Le paramètre `mon ip` est utile au programme pour qu'il savoir si un paquet lui est destiné.

On peut voir le paquet tourner entre les quatre terminaux
