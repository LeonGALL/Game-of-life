/** 
 * \file jeu.c 
 * Fichier contenant les fonctions régissant l'évolution du jeu.
 * \author Léon GALL
 */

#include "jeu.h"

/**
 * \fn int compte_voisins_vivants_cyclique (int i, int j, grille g);
 * \param i numéro de la ligne
 * \param j numéro de la colonne
 * \param g grille
 * \return Retourne le nombre de voisins vivants.
 * \brief Cette fonction compte le nombre de voisins vivants de la cellule (i,j). Les bords sont cycliques.
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g){
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
 * \fn int compte_voisins_vivants_non_cyclique (int i, int j, grille g);
 * \param i numéro de la ligne
 * \param j numéro de la colonne
 * \param g grille
 * \return Retourne le nombre de voisins vivants.
 * \brief Cette fonction compte le nombre de voisins vivants de la cellule (i,j). Les bords ne sont pas cycliques.
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	if (i-1 >= 0){
		if (j-1 >= 0) v+= est_vivante(i-1,j-1,g);
		if (j >= 0 && j < c) v+= est_vivante(i-1,j,g);
		if (j+1 < c) v+= est_vivante(i-1,j+1,g);
	}
	if (i >= 0 && i < l){
		if (j-1 >= 0) v+= est_vivante(i,j-1,g);
		if (j+1 < c) v+= est_vivante(i,j+1,g);
	}
	if (i+1 < l){
		if (j-1 >= 0) v+= est_vivante(i+1,j-1,g);
		if (j >= 0 && j < c) v+= est_vivante(i+1,j,g);
		if (j+1 < c) v+= est_vivante(i+1,j+1,g);
	}

	return v; 
}

/**
 * \fn void evolue_sans_vieillir (grille *g, grille *gc);
 * \param g pointeur vers une grille
 * \param gc pointeur vers une grille
 * \brief Cette fonction fait évoluer la grille g d'un pas de temps, sans vieillissement.
 */
void evolue_sans_vieillir (grille *g, grille *gc){
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
				else set_vivante(i,j,*g); // On réinitialise son âge à 1 (au cas où elle avait déjà vieilli précédemment)
			}
			else if (est_viable(i,j,*g))
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}

/**
 * \fn void evolue_vieillissement (grille *g, grille *gc);
 * \param g pointeur vers une grille
 * \param gc pointeur vers une grille
 * \brief Cette fonction fait évoluer la grille g d'un pas de temps, avec vieillissement.
 */
void evolue_vieillissement (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = compte_voisins_vivants (i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				vieillir(i,j,*g);
				if ( (v!=2 && v!= 3) || age(i,j,*g)>=8) set_morte(i,j,*g);
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}

/**
 * \fn void set_vieillissement();
 * \brief Cette fonction active le vieillissement.
 */
void set_vieillissement(){
	print_age = print_age_vieillissement; 
	evolue = evolue_vieillissement;
}

/**
 * \fn void unset_vieillissement();
 * \brief Cette fonction désactive le vieillissement.
 */
void unset_vieillissement(){ 
	print_age = print_age_sans_vieillissement; 
	evolue = evolue_sans_vieillir; 
}
