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

#define SIZEY 500
#define SIZEX 500
#define FNAME_S 100
#define MIN(X,Y) ((X<Y)?X:Y)

typedef struct {
  int x;
  int y;
} Size;

void affiche_cairo(grille g, cairo_surface_t *surface, Size size, int temps);
void affiche_str_cairo(cairo_surface_t *surface, Size size, float pos_x, float pos_y, char str[], int mode);
int change_grille_cairo(grille* g, grille* gc, Window win, Display* dpy, cairo_surface_t* surface, Size* size, Atom* wmDeleteWindow);
void quitter(cairo_surface_t *surface, Display* dpy);

#endif