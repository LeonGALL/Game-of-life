/** 
 * \file io_cairo.c 
 * Fichier s'occupant des entrées/sorties du programme.
 * \author Léon GALL
 */
#include "io_cairo.h"

/**
 * \fn void affiche_grille_cairo (grille g, cairo_surface_t *surface, Size size);
 * \relatesalso grille
 * \param g une grille
 * \param surface un pointeur vers une surface cairo
 * \param size taille de la fenêtre
 * \brief Cette fonction affiche une grille.
 */
void affiche_grille_cairo(grille g, cairo_surface_t *surface, Size size){
  // Création d'un masque
	cairo_t *cr = cairo_create(surface);

	// On met l'arrière plan en noir
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);

  float position_x = (float) size.x/g.nbc;
  float position_y = (float) size.y/g.nbl;
  char age;
  // Cellules vivantes (blanc) et non viables (rouge).
  for (int i=0; i<g.nbl; i++){
    for (int j=0; j<g.nbc; j++){
      if (est_vivante(i,j,g)){
        cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
      	cairo_rectangle(cr,position_x*i,position_y*j,position_x,position_y);
        cairo_fill(cr);	
        if ((age=print_age(g.cellules[i][j])) != 'O') {
          cairo_text_extents_t te;
          char str[2];
          str[0]=age;
          str[1]='\0';
          cairo_set_source_rgb (cr, 0, 0, 0);
          cairo_set_font_size (cr, MIN(position_x,position_y)/3);
          cairo_text_extents (cr,str, &te);
          cairo_move_to(cr, position_x*i+((position_x-te.width)/2-te.x_bearing), position_y*j+((position_y-te.height)/2)-te.y_bearing);
          cairo_show_text (cr,str);
        }
      }
      else if (!est_viable(i,j,g)){
        cairo_set_source_rgb (cr, 1, 0, 0);
      	cairo_rectangle(cr,position_x*i,position_y*j,position_x,position_y);
	      cairo_fill(cr);	
      }
    }
  }

  cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
  for (int i=0; i<=g.nbc;i++){
    // COLONNES
    cairo_move_to (cr,position_x*i,0);
	  cairo_line_to(cr,position_x*i,size.y);
	  cairo_set_line_width (cr, 1);
	  cairo_stroke (cr);
  }
  for (int i=0; i<=g.nbl;i++){
    // LIGNES
    cairo_move_to (cr,0,position_y*i);
	  cairo_line_to(cr,size.x,position_y*i);
	  cairo_set_line_width (cr, 1);
	  cairo_stroke (cr);
  }

  // Destruction du masque
	cairo_destroy(cr);
}

/**
 * \fn void debut_jeu_cairo(grille *g, grille *gc);
 * \relatesalso grille
 * \param g pointeur vers une grille
 * \param gc pointeur vers une grille
 * \brief Cette fonction débute le jeu et gère les intéractions entre l'utilisateur et le jeu.
 */
void debut_jeu_cairo(grille *g, grille *gc){
  // Initialisation de l'interface graphique.
  // Elle est fortement inspirée de l'exemple donné en cours.
  Display *dpy = XOpenDisplay(NULL);
  assert(dpy != NULL);
  int screen = XDefaultScreen(dpy);
  Window rootWindow = XRootWindow(dpy,screen);
  Window win = XCreateSimpleWindow(dpy, rootWindow, 1, 1, SIZEX, SIZEY, 0, BlackPixel(dpy, screen), BlackPixel(dpy, screen));
  XStoreName(dpy, win, "Jeu de la vie");
	XSelectInput(dpy, win, StructureNotifyMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);
  // Pour la fermeture de la fenêtre sur l'appui de la croix rouge de fermeture de fenêtre
  Atom wmDeleteWindow = XInternAtom(dpy, "WM_DELETE_WINDOW", 1);
  XSetWMProtocols(dpy, win, &wmDeleteWindow, 1);
  // Creation de la surface cairo
	cairo_surface_t *surface = cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

  // taille courante de la fenêtre
  Size size;
  size.x=SIZEX;
  size.y=SIZEY;


  affiche_grille_cairo(*g,surface,size);

  // Boucle de jeu
  XEvent e;
  for (;;){
    affiche_grille_cairo(*g,surface,size);
    XNextEvent(dpy,&e);
    if (e.type == KeyPress){
      
    } else if (e.type == ButtonPress){
      
    }
    else if (e.type == ClientMessage){
      if (e.xclient.data.l[0] == wmDeleteWindow) // Si clic sur la fermeture de la fenêtre
        break;
    }
    else if (e.type == ConfigureNotify){
      size.x = e.xconfigure.width;
      size.y = e.xconfigure.height;
      cairo_xlib_surface_set_size(surface,size.x,size.y);
    }
  }

  // Destruction de la surface cairo
  cairo_surface_destroy(surface);
  // Fermeture de l'interface graphique
  XCloseDisplay(dpy);
}