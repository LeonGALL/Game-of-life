/** 
 * \file io.c 
 * Fichier contenant les fonctions régissant l'évolution du jeu.
 * \author Léon GALL
 */

#include "jeu.h"

/**
 * \fn int compte_voisins_vivants (int i, int j, grille g);
 * \param i numéro de la ligne
 * \param j numéro de la colonne
 * \param g grille
 * \return Retourne le nombre de voisins vivants.
 * \brief Cette fonction compte le nombre de voisins vivants de la cellule (i,j). Les bords sont cycliques.
 */
int compte_voisins_vivants (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

/**
 * \fn void evolue (grille *g, grille *gc);
 * \param g pointeur vers une grille
 * \param gc pointeur vers une grille
 * \brief Cette fonction fait évoluer la grille g d'un pas de temps.
 */
void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = compte_voisins_vivants (i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}
