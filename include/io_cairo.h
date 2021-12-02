/** 
 * \file io_cairo.h
 * Fichier contenant les prototypes des fonctions de io_cairo.c.
 * \author Léon GALL
 */

#ifndef _IO_CAIRO_H_
#define _IO_CAIRO_H_

#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <fontconfig/fontconfig.h>
#include <assert.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include "grille.h"
#include "jeu.h"
#include "io.h"

#define SIZEY 500 /**< \brief TAILLE INITIALE EN Y*/
#define SIZEX 500 /**< \brief TAILLE INITIALE EN X*/
#define FNAME_S 100 /**< \brief TAILLE INITIALE EN Y*/
#define MIN(X,Y) ((X<Y)?X:Y) /**< \brief MACRO QUI DONNE LE MINIMUM ENTRE DEUX NOMBRES*/

/**
 * \brief structure Size : taille en x et y.
 */
typedef struct {
  int x; /**< \brief x, abscisses*/
  int y; /**< \brief y, ordonnées*/
} Size;

// Affiche la grille
void affiche_cairo(grille g, cairo_surface_t *surface, Size size, int temps);

// Affiche une chaine de caractère
void affiche_str_cairo(cairo_surface_t *surface, Size size, float pos_x, float pos_y, char str[], int mode);

// Change une grille
int change_grille_cairo(grille* g, grille* gc, Window win, Display* dpy, cairo_surface_t* surface, Size* size, Atom* wmDeleteWindow);

// Quitte X11 et cairo
void quitter(cairo_surface_t *surface, Display* dpy);

#endif
