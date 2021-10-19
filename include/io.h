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

/**
 * \fn static inline char print_age_sans_vieillissement(int e);
 * \param e une cellule
 * \return Retourne le caractère à afficher. ('O')
 * \brief Cette fonction retourne le caractère à afficher.
 */
static inline char print_age_sans_vieillissement(int e){ return 'O'; }

/**
 * \fn static inline char print_age_vieillissement(int e);
 * \param e une cellule
 * \return Retourne le caractère à afficher. (Age de la cellule)
 * \brief Cette fonction retourne le caractère à afficher.
 */
static inline char print_age_vieillissement(int e){ return (char) (e+'0'); }

/**
 * \fn char (*print_age) (int);
 * \param int age d'une cellule.
 * \return Retourne le caractère à afficher.
 * \brief Pointeur de fonction. Pointera vers \b print_age_vieillissement ou vers \b print_age_sans_vieillissement .
 */
char (*print_age) (int);

// affichage du temps
void affiche_temps (int temps);

// affichage du temps et de la grille
void affiche_tout (grille g, int temps);

// effacement du temps et de la grille
void efface_temps_grille (grille g);

// effacement d'une grille
void efface_grille (grille g);

// effacement du temps d'évolution et d'une grille pour permettre l'affichage d'une différente
void efface(int n, int p);

// remplissage d'un tableau avec une chaine de caractère en entrée clavier
// retourne le nombre de sauts de lignes effectués.
int scan(char tab[],int size);

// debute le jeu
void debut_jeu(grille *g, grille *gc);

#endif
