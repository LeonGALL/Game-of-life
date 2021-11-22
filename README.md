# Jeu de la Vie

Bienvenue dans le projet de technique de développement du troisième semestre de licence d'informatique.

## Description

Le Jeu de la Vie (ou _Game of Life_) est, en réalité, un automate cellulaire défini en 1970 par le mathématicien anglais John Conway afin de tenter de résoudre un problème soulevé par un mathématicien, père de l’informatique, John Von Neumann.

Ce n’est pas à proprement parler un jeu : il ne nécessite pas l’intervention d’un joueur humain, hormis pour fixer les conditions initiales du jeu. Il se compose d’un univers dans lequel évoluent des cellules vivantes suivant des règles d’évolution précises.

Dans la version originale décrite par John Conway, l’univers est défini sur une grille à deux dimensions, de taille variable, où chaque case est une cellule pouvant prendre deux états différents : morte ou vivante.

Le passage d’un état à l’autre est guidé par les règles d’évolution suivantes :

- Une cellule morte au temps _t_ devient vivante au temps _t + 1_ si et seulement si elle a exactement 3 cellules vivantes dans son voisinage.
- Une cellule vivante au temps _t_ reste vivante au temps _t + 1_ si et seulement si elle a exactement 2 ou 3 cellules vivantes dans son voisinage, sinon elle meurt.
- Le voisinage utilisé est le 8-voisinage : pour une cellule donnée, ses voisines sont les 8 cellules qui l’entourent.

A partir de ces règles de base beaucoup d’extensions ont été proposées mais le jeu garde le même principe : il se déroule suivant un nombre de pas de temps théoriquement infini. À chaque pas de temps _t_, on évalue, pour chaque cellule, l’état de la cellule au pas de temps _t + 1_ en fonction des règles d’évolution des cellules.

Vous pourrez obtenir de plus vastes précisions sur ce jeu dans la vidéo de présentation [suivante](https://youtu.be/S-W0NX97DB0).

_Description issue du [document de présentation du projet](https://moodle.unistra.fr/pluginfile.php/557566/mod_resource/content/0/Sujets_de_TP/presentation.pdf)._

## Niveaux

La programmation de ce projet s'est décomposée en 5 niveaux :

- [x] [Niveau 1](https://moodle.unistra.fr/pluginfile.php/557570/mod_resource/content/5/GoL_niveau1.pdf)
- [x] [Niveau 2](https://moodle.unistra.fr/pluginfile.php/557571/mod_resource/content/7/GoL_niveau2.pdf)
- [x] [Niveau 3](https://moodle.unistra.fr/pluginfile.php/557572/mod_resource/content/5/GoL_niveau3.pdf)
- [x] [Niveau 4](https://moodle.unistra.fr/pluginfile.php/557573/mod_resource/content/5/GoL_niveau4.pdf)
- [ ] [Niveau 5](https://moodle.unistra.fr/pluginfile.php/557576/mod_resource/content/8/GoL_niveau5.pdf)

À chaque niveau correspond un numéro de version, comme expliqué dans la rubrique suivante.

## Versionnement

Le versionnement à l'aide de tags peut se lire de cette façon : \<NIVEAU\>.0.\<VERSION\>

- Le niveau se lit au début : 1 représentera le niveau 1, ...
- La version de ce niveau se lit à la fin : la première version sera numérotée 0 (non noté), la seconde 1, ... _(et oui, les informaticiens commencent le compte à 0_ :wink:_)_

La dernière version d'un niveau est donc celle avec le numéro de \<VERSION\> le plus haut.

## Utilisation
### Compilation et lancement du jeu

Pour compiler ce jeu, deux modes sont disponibles :

#### Mode terminal

Si vous ne possédez pas les ressources nécessaires pour lancer la compilation du jeu graphique, ou bien que vous préférez simplement le mode en ligne de commandes, vous avez la possibilité de compiler en utilisant :

```bash
make MODE=TEXTE
```

#### Mode graphique

Sinon, vous pouvez utiliser la commande `make` pour compiler la version graphique du jeu. C'est bien plus agréable à regarder que la version en ligne de commande...

#### Lancement

Après compilation, indépendament de son mode, pour lancer le jeu, il faut entrer la commande suivante :
```bash
./bin/main <CHEMIN FICHIER GRILLE>
```
En général, ce sera :
```bash
./bin/main grilles/grille<NUMERO>.txt
```

### Contrôle des conditions de jeu

#### Mode terminal

- Touche <kbd>q</kbd> pour quitter le jeu.
- Touche <kbd>n</kbd> pour entrer le nom d'une nouvelle grille.
```bash
n <CHEMIN FICHIER GRILLE>
```
- Touche <kbd>c</kbd> pour activer/désactiver le calcul de voisinage cyclique. Initialement, il est activé.
- Touche <kbd>v</kbd> pour activer/désactiver le vieillissement des cellules. Initialement, il est désactivé.
- Touche <kbd>enter</kbd> pour évoluer d'un pas de temps.

#### Mode graphique

- Touche <kbd>n</kbd> pour entrer le nom d'une nouvelle grille.
- Touche <kbd>c</kbd> pour activer/désactiver le calcul de voisinage cyclique. Initialement, il est activé.
- Touche <kbd>v</kbd> pour activer/désactiver le vieillissement des cellules. Initialement, il est désactivé.
- Clic <kbd>Clic droit</kbd> pour évoluer d'un pas de temps.
- Touche <kbd>enter</kbd> pour évoluer d'un pas de temps.

_Lorsque vous êtes sur le menu d'ouverture d'une nouvelle grille, un clic droit vous fera sortir de ce menu, et revenir à la grille chargée précédemment._
- Clic <kbd>Clic gauche</kbd> pour quitter le jeu.
- Touche <kbd>q</kbd> pour quitter le jeu.

## Contribution

Ce projet est strictement personnel. Une contribution de votre part pourrait nous envoyer en conseil de discipline.

## Auteurs

Les codes de ce projet ont été écrits par [Léon GALL](@lgall), ainsi que par l'équipe pédagogique de la licence informatique.
