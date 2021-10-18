/** 
 * \file jeu.h
 * Fichier contenant les prototypes des fonctions de jeu.c.
 * \author Léon GALL
 */

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"
#include "io.h"


/**
 * \fn static inline int modulo(int i, int m);
 * \param i ligne
 * \param j colonne
 * \brief Cette fonction est un modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques.
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 * \fn static inline int age (int i, int j, grille g);
 * \param i une ligne
 * \param j une colonne
 * \param g une grille
 * \return Retorune l'âge de la cellule.
 * \brief Cette fonction indique l'âge de la cellule.
 */
static inline int age (int i, int j, grille g){ return g.cellules[i][j]; }

/**
 * \fn static inline void vieillir (int i, int j, grille g);
 * \param i une ligne
 * \param j une colonne
 * \param g une grille
 * \brief Cette fonction fait vieillir une cellule.
 */
static inline void vieillir (int i, int j, grille g){ g.cellules[i][j]++; }

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

// fait évoluer la grille g d'un pas de temps sans vieillissement
void evolue_sans_vieillir (grille *g, grille *gc);

// fait évoluer la grille g d'un pas de temps avec vieillissement
void evolue_vieillissement (grille *g, grille *gc);

/**
 * \fn void (*evolue) (grille*, grille*);
 * \param \a grille un pointeur vers grille
 * \param \a grille un pointeur vers grille
 * \brief Pointeur de fonction. Pointera vers \b evolue_sans_vieillir ou vers \b evolue_vieillissement .
 */
void (*evolue) (grille*, grille*);

// Active le vieillissement
void set_vieillissement();

// Désactive le vieillissement
void unset_vieillissement();

#endif
