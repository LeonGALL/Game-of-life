/** 
 * \file grille.h
 * Fichier contenant les prototypes des fonctions de grille.c.
 * \author Léon GALL
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * \brief structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
 */
typedef struct {
  int nbl; /**< \brief nombre de lignes*/
  int nbc; /**< \brief nombre de colonnes*/
  int** cellules; /**< \brief grille*/
} grille;
 
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
void alloue_grille (int l, int c, grille* g);

// libère une grille
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
void init_grille_from_file (char * filename, grille* g);

/**
 * \fn static inline void set_vivante(int i, int j, grille g);
 * \param i ligne
 * \param j colonne
 * \param g une grille
 * \brief Cette fonction rend vivante la cellule (i,j) de la grille g.
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/**
 * \fn static inline void set_vivante(int i, int j, grille g);
 * \param i ligne
 * \param j colonne
 * \param g une grille
 * \brief Cette fonction rend morte la cellule (i,j) de la grille g.
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

/**
 * \fn static inline void set_vivante(int i, int j, grille g);
 * \param i ligne
 * \param j colonne
 * \param g une grille
 * \brief teste si la cellule (i,j) de la grille g est vivante.
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] == 1;}

// recopie gs dans gd (sans allocation)
void copie_grille (grille gs, grille gd);

#endif
