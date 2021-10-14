/** 
 * \file io.h
 * Fichier contenant les prototypes des fonctions de io.c.
 * \author Léon GALL
 */

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

// affichage d'un trait horizontal
void affiche_trait (int c);

// affichage d'une ligne de la grille
void affiche_ligne (int c, int* ligne);

// affichage d'une grille
void affiche_grille (grille g);

// effacement d'une grille
void efface_grille (grille g);

// effacement d'une grille pour permettre l'affichage d'une différente
void efface(int n, int p);

// remplissage d'un tableau avec une chaine de caractère en entrée clavier
// retourne le nombre de sauts de lignes effectués.
int scan(char tab[],int size);

// debute le jeu
void debut_jeu(grille *g, grille *gc);

#endif
