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
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
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
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
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
	printf("\n\033[%dA",l*2+5+p); // déplace le curseur
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
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'n':
			{ // touche n pour une nouvelle catégorie
				char file[30],chemin[50];
				int i = scan(file,30);
				sprintf(chemin,"grilles/%s",file); // On rajoute le nom du répertoire.
				efface(g->nbl,i); // On efface la grille précédente.
				
				libere_grille(g);
				libere_grille(gc);

				init_grille_from_file(chemin,g);
				alloue_grille (g->nbl, g->nbc, gc);

				affiche_grille(*g);
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
