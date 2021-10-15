/** 
 * \file grille.c 
 * Fichier s'occupant des grilles.
 * \author Léon GALL
 */

#include "grille.h"

/**
 * \fn void init_grille_from_file (char * filename, grille* g);
 * \relatesalso grille
 * \param filename nom du fichier
 * \param g pointeur vers une grille
 * \brief Cette fonction alloue et initalise la grille g à partir d'un fichier.
 */
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	
	fclose (pfile);
	return;
}

/**
 * \fn void alloue_grille (int l, int c, grille* g);
 * \relatesalso grille
 * \param l nombre de lignes
 * \param c nombre de colonnes
 * \param g pointeur vers une grille
 * \brief Cette fonction alloue une grille de taille l*c, et initialise toutes les cellules à mortes.
 */
void alloue_grille (int l, int c, grille* g){
	g->nbl = l;
	g->nbc = c;

	g->cellules = (int**) malloc(sizeof(int*)*l);
	assert (g->cellules != NULL);

	for (int i=0; i<l; i++){
		g->cellules[i] = (int*) calloc(c,sizeof(int)); // Alloue et iitialise à 0.
		assert (g->cellules[i] != NULL);
	}
}

/**
 * \fn void libere_grille (grille* g);
 * \relatesalso grille
 * \param g pointeur vers une grille
 * \brief Cette fonction libère une grille.
 */
void libere_grille (grille* g){
	for (int i=0; i<g->nbl; i++)
		free(g->cellules[i]);
	free(g->cellules);
}

/**
 * \fn void copie_grille (grille gs, grille gd);
 * \relatesalso grille
 * \param gs une grille
 * \param gd une grille
 * \brief Cette fonction recopie gs dans gd (sans allocation).
 */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}
