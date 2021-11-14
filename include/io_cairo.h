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
#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include "grille.h"
#include "jeu.h"
#include "io.h"

#define SIZEY 500
#define SIZEX 500
#define MIN(X,Y) ((X<Y)?X:Y)

typedef struct {
  int x;
  int y;
} Size;

void affiche_grille_cairo(grille g, cairo_surface_t *surface, Size size);
void debut_jeu_cairo(grille *g, grille *gc);


#endif