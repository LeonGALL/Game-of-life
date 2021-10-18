/** 
 * \file jeu.h
 * Fichier contenant les prototypes des fonctions de jeu.c.
 * \author Léon GALL
 */

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"


/**
 * \fn static inline int modulo(int i, int m);
 * \param i ligne
 * \param j colonne
 * \brief Cette fonction est un modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques.
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
int compte_voisins_vivants_cyclique (int i, int j, grille g);

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords ne sont pas cycliques.
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);

/**
 * \fn int (*compte_voisins_vivants) (int, int, grille);
 * \param \a int numéro de la ligne
 * \param \a int numéro de la colonne
 * \param \a grille grille
 * \return Retourne le nombre de voisins vivants.
 * \brief Pointeur de fonction. Pointera vers \b compte_voisins_vivants_cyclique ou vers \b compte_voisins_vivants_non_cyclique .
 */
int (*compte_voisins_vivants) (int, int, grille);

// fait évoluer la grille g d'un pas de temps
void evolue (grille *g, grille *gc);

#endif
