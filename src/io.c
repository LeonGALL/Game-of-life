/** 
 * \file io.c 
 * Fichier s'occupant des entrées/sorties du programme.
 * \author Léon GALL
 */

#include "io.h"

/**
 * \fn void affiche_trait (int c);
 * \param c nombre de colonnes
 * \brief Cette fonction affiche le séparateur entre des lignes.
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

/**
 * \fn void affiche_ligne (int c, int* ligne);
 * \param c nombre de colonnes
 * \param ligne pointeur vers une ligne
 * \brief Cette fonction affiche une ligne.
 */
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| %c ",print_age(ligne[i]));
	printf("|\n");
	return;
}

/**
 * \fn void affiche_grille (grille g);
 * \relatesalso grille
 * \param g une grille
 * \brief Cette fonction affiche une grille.
 */
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

/**
 * \fn void affiche_temps (int temps);
 * \param temps temps d'évolution
 * \brief Cette fonction affiche le temps d'évolution.
 */
void affiche_temps (int temps){
	printf("\n\tTemps : %d\n",temps);
}

/**
 * \fn void affiche_tout (grille g, int temps);
 * \relatesalso grille
 * \param g une grille
 * \param temps temps d'évolution
 * \brief Cette fonction affiche un temps d'évolution et une grille.
 */
void affiche_tout (grille g, int temps){
	affiche_temps(temps);
	affiche_grille(g);
}

/**
 * \fn void efface_temps_grille (grille g);
 * \relatesalso grille
 * \param g une grille
 * \brief Cette fonction place le curseur au début de l'affichage du temps (au-dessus de la grille).
 */
void efface_temps_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 6);
}

/**
 * \fn void efface_grille (grille g);
 * \relatesalso grille
 * \param g une grille
 * \brief Cette fonction place le curseur au début de la grille.
 */
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

/**
 * \fn void efface(int l, int p);
 * \param l nombre de lignes de la grille
 * \param p nombre de lignes supplémentaires
 * \brief Cette fonction efface une grille.
 */
void efface(int l, int p){
	printf("\n\033[%dA",l*2+6+p); // déplace le curseur
	printf("\033[0J"); // efface de la position du curseur à la fin.
}

/**
 * \fn int scan(char tab[],int size);
 * \param tab tableau à remplir par effet de bord avec le nom du fichier
 * \param size taille du tableau
 * \return Retourne le nombre de lignes sautées lors de la saisie clavier
 * \brief Cette fonction lit les entrées standard et les place dans un tableau.
 */
int scan(char tab[],int size){
	char c;
	int nb_lgn=0,indice=0;

	while ((c = getchar()) == '\n' || c == ' ') // On se place à la première lettre du nom du fichier
		if (c=='\n') nb_lgn++; // On incrémente le nombre de lignes sautées lorsqu'il y en a.

	while ((c!='\n' && c!=' ') && indice<size-1){ // On note le caractère dans la chaîne
		tab[indice++]=c;
		c=getchar();
	}
	tab[indice]='\0';
	while (c!='\n') c=getchar(); // On vide le buffer

	return nb_lgn; // On retourne le nombre de lignes sautées.
}

/**
 * \fn void debut_jeu(grille *g, grille *gc);
 * \relatesalso grille
 * \param g pointeur vers une grille
 * \param gc pointeur vers une grille
 * \brief Cette fonction débute le jeu et gère les intéractions entre l'utilisateur et le jeu.
 */
void debut_jeu(grille *g, grille *gc){
	int temps = 0;
	compte_voisins_vivants = compte_voisins_vivants_cyclique; // Par défaut le comptage du voisinage se fait de façon cyclique
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				temps++;
				efface_temps_grille(*g);
				affiche_tout(*g,temps);
				break;
			}
			case 'n':
			{ // touche "n" pour une nouvelle catégorie --> usage n grille3.txt ou n \n grille3.txt
				char file[30],chemin[50];
				int i = scan(file,30);
				sprintf(chemin,"grilles/%s",file); // On rajoute le nom du répertoire.
				efface(g->nbl,i); // On efface la grille précédente.
				
				libere_grille(g);
				libere_grille(gc);

				init_grille_from_file(chemin,g);
				alloue_grille (g->nbl, g->nbc, gc);
				temps = 0;
				affiche_tout(*g,temps);
				break;
			}
			case 'c':
			{ // Touche "c" pour activer/désactiver le voisinage cyclique 
				if (compte_voisins_vivants == compte_voisins_vivants_cyclique){
					compte_voisins_vivants = compte_voisins_vivants_non_cyclique;
				} else {
					compte_voisins_vivants = compte_voisins_vivants_cyclique;
				}
				/* SUIVANT SI IL FAUT OU NON PASSER À L'ÉVOLUTION SUIVANTE DIRECTEMENT
				while ((c=getchar()) != '\n'); // On neutralise le saut à la ligne pour ne pas passer à l'evolution suivante
				printf("\n\e[2A");
				*/
				break;
			}
			case 'v':
			{ // Touche "v" pour activer/désactiver le vieillissement
				if (evolue == evolue_vieillissement) unset_vieillissement();
				else set_vieillissement();
				/* SUIVANT SI IL FAUT OU NON PASSER À L'ÉVOLUTION SUIVANTE DIRECTEMENT
				while ((c=getchar()) != '\n'); // On neutralise le saut à la ligne pour ne pas passer à l'evolution suivante
				printf("\n\e[2A");
				*/
			break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
