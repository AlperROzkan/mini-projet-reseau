# mini-projet-reseau
Mini projet de réseau, mise en place d'un protocole que nous avons nous même imaginez, basé sur un réseau en anneau.

## Compilation
Compiler avec:

```bash
~$ make
```

## Lancer le programme
Exemple avec quatre terminaux:
* `./build/program 127.0.0.1 1111 127.0.0.2 2222`
* `./build/program 127.0.0.2 2222 127.0.0.3 3333`
* `./build/program 127.0.0.3 3333 127.0.0.4 4444`
* `./build/program 127.0.0.4 4444 127.0.0.1 1111`

C'est l'exemple typique du token ring.

### Arguments
`./build/program [mon ip] [port écoute] [ip suivant] [port envoie]`

On peut voir le paquet tourner entre les quatre terminaux
