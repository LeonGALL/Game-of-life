/** 
 * \file io_cairo.c 
 * Fichier s'occupant des entrées/sorties du programme.
 * \author Léon GALL
 */
#include "io_cairo.h"

/**
 * \fn int change_grille_cairo(grille* g, grille* gc, Window win, Display* dpy, cairo_surface_t* surface, Size* size, Atom* wmDeleteWindow);
 * \relatesalso grille
 * \param g un pointeur vers grille
 * \param gc un pointeur vers grille
 * \param win Le X11 window
 * \param dpy Le X11 display
 * \param surface un pointeur vers une surface cairo
 * \param size un pointeur sur la taille de la fenêtre
 * \param wmDeleteWindow permet la fermeture de la fenêtre
 * \return Retourne le status de sortie de la fonction.
 * \brief Cette fonction se charge de changer une grille.
 */
int change_grille_cairo(grille* g, grille* gc, Window win, Display* dpy, cairo_surface_t* surface, Size* size, Atom* wmDeleteWindow){
  // Entrées clavier
  XIM im = XOpenIM(dpy, NULL, NULL, NULL);
  XIC ic;
  char keyBuf[FNAME_S];
  for (int i=0; i<FNAME_S; i++) keyBuf[i]='\0'; // On remplit le tableau avec des caractères de fin de chaîne
  int index=0;
  int count;
  // Event
  XEvent e;
  for (;;){
    affiche_cairo(*g,surface,*size,-1);
    affiche_str_cairo(surface,*size,(float)(size->x)/g->nbc, (float) (size->y)/g->nbl,(keyBuf[0]!='\0')?keyBuf:"Saisissez le nom d'une grille",(keyBuf[0]!='\0')?0:1);
    XNextEvent(dpy,&e);
    // Cas touche pressée
    if (e.type == KeyPress){
      ic = XCreateIC(im, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, XNClientWindow, win, NULL); 
      if ((count = Xutf8LookupString(ic,&e.xkey, keyBuf+index, FNAME_S, NULL, NULL))!=0) {
        if (keyBuf[index]==0xd) { // Si retour à la ligne
          keyBuf[index]='\0';
          if (keyBuf[0]=='\0') continue;
          break;
        } else if (keyBuf[index]==0x8){ // Suppression
          if (index>0) --index;
          if (((keyBuf[index]>>8)&0xffffff)==0xffffff)keyBuf[index--]='\0'; // Si il s'agit d'un caractère composé ('é' par exemple)
          keyBuf[index]='\0';
        } else {
          index+=count;
          if (index >= FNAME_S) {
            fprintf(stderr,"Stack overflow\n");
            break;
          }
        }
      }
    } else if (e.type == ButtonPress){
      // Cas clic
      if (e.xbutton.button==1){ // Left clic
        return 2; // On retourne à l'état précédent (utile si l'appui sur 'n' était une erreur)
      } else if (e.xbutton.button==3){ // Right clic
        // On quitte X11 et cairo
        quitter(surface,dpy);
        return -1;
      }
    } else if (e.type == ClientMessage){
      // Cas clic de sortie
        if (e.xclient.data.l[0] == *wmDeleteWindow) {  // Si clic sur la fermeture de la fenêtre
          // On quitte X11 et cairo
          quitter(surface,dpy);
          return -1;
        }
    } else if (e.type == ConfigureNotify){
      // Cas de modification de la taille
      size->x = e.xconfigure.width;
      size->y = e.xconfigure.height;
      cairo_xlib_surface_set_size(surface,size->x,size->y);
    }
  }
  // On vide l'ancienne grille
  libere_grille(g);
	libere_grille(gc);
  // Traitement de la chaîne
  int first=0, last=FNAME_S-1, i=0;
  for (; first<FNAME_S; first++){
    if (keyBuf[first]!=' ') break;
  }
  for (;last>0;last--){
    if (keyBuf[last]!='\0'&&keyBuf[last]!=' ') break;
  }
  char file[FNAME_S];
  if (first >= last) file[0]='\0';
  else 
    for (;first<=last;i++,first++)
      file[i]=keyBuf[first];
  file[i]='\0';
  // Initialisation de la nouvelle grille
  init_grille_from_file(file,g);
	alloue_grille (g->nbl, g->nbc, gc);
  return 1;
}

/**
 * \fn void quitter(cairo_surface_t *surface, Display* dpy);
 * \param surface un pointeur vers une surface cairo
 * \param dpy Le X11 display
 * \brief Cette fonction quitte cairo et X11 proprement.
 */
void quitter(cairo_surface_t *surface, Display* dpy){
  // Destruction de la surface cairo
  cairo_surface_destroy(surface);
  // Fermeture de l'interface graphique
  XCloseDisplay(dpy);
  // Gestion des fuites de mémoires cairo.
  FcFini();
  cairo_debug_reset_static_data();
}

/**
 * \fn void affiche_str_cairo(cairo_surface_t *surface, Size size, float pos_x, float pos_y, char str[], int mode);
 * \param surface un pointeur vers une surface cairo
 * \param size taille de la fenêtre
 * \param pos_x largeur d'une bande
 * \param pos_y hauteur d'une bande
 * \param str chaîne de caractères
 * \param mode mode d'affichage (si 1 alors opacité diminuée)
 * \brief Cette fonction affiche une chaîne de caratère.
 */
void affiche_str_cairo(cairo_surface_t *surface, Size size, float pos_x, float pos_y, char str[], int mode){
  cairo_t *cr = cairo_create(surface);
  cairo_text_extents_t te;
  if (mode==1) cairo_set_source_rgba (cr, 1, 1, 1,0.6);
  else cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_set_font_size (cr, MIN(pos_x,pos_y)/3);
  cairo_text_extents (cr,str, &te);
  cairo_move_to(cr,size.x*0.11,size.y-((pos_y-te.height)/2));
  cairo_show_text (cr,str);
	cairo_destroy(cr);
}



/**
 * \fn void affiche_cairo(grille g, cairo_surface_t *surface, Size size, int temps);
 * \relatesalso grille
 * \param g une grille
 * \param surface un pointeur vers une surface cairo
 * \param size taille de la fenêtre
 * \param temps Le temps d'évolution (si -1 alors il s'agit d'un changement de fichier)
 * \brief Cette fonction affiche la grille, et le temps d'évolution.
 */
void affiche_cairo(grille g, cairo_surface_t *surface, Size size, int temps){
  // Création d'un masque
	cairo_t *cr = cairo_create(surface);

	// On met l'arrière plan en noir
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);

  float position_x = (float) size.x/g.nbc; // largeur d'une bande
  float position_y = (float) size.y/(g.nbl+1); // hauteur d'une bande

  // Affichage du temps d'évolution
  int ecart_dessus = (temps != -1)?1:0;
  if (temps != -1){
    cairo_text_extents_t text_temps;
    char text_tps[20];
    sprintf(text_tps,"ÉVOLUTION : %d",temps);
    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_set_font_size (cr, MIN(position_x,position_y)/3);
    cairo_text_extents (cr,text_tps, &text_temps);
    cairo_move_to(cr,((size.x-text_temps.width)/2-text_temps.x_bearing),((position_y-text_temps.height)/2)-text_temps.y_bearing);
    cairo_show_text (cr,text_tps);
  } else {
    cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
    cairo_rectangle(cr,size.x*0.1,position_y*(g.nbl+0.1),size.x*0.8,position_y*0.8);
    cairo_stroke(cr);	
  }

  char age;
  // Cellules vivantes (blanc) et non viables (rouge).
  for (int i=0; i<g.nbl; i++){
    for (int j=0; j<g.nbc; j++){
      if (est_vivante(i,j,g)){
        cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
      	cairo_rectangle(cr,position_x*j,position_y*(i+ecart_dessus),position_x,position_y);
        cairo_fill(cr);	
        // Si vieillissement : affichage de l'âge
        if ((age=print_age(g.cellules[i][j])) != 'O') {
          cairo_text_extents_t te;
          char str[2];
          str[0]=age;
          str[1]='\0';
          cairo_set_source_rgb (cr, 0, 0, 0);
          cairo_set_font_size (cr, MIN(position_x,position_y)/3);
          cairo_text_extents (cr,str, &te);
          cairo_move_to(cr, position_x*j+((position_x-te.width)/2-te.x_bearing), position_y*(i+ecart_dessus)+((position_y-te.height)/2)-te.y_bearing);
          cairo_show_text (cr,str);
        }
      }
      else if (!est_viable(i,j,g)){
        cairo_set_source_rgb (cr, 1, 0, 0);
      	cairo_rectangle(cr,position_x*j,position_y*(i+ecart_dessus),position_x,position_y);
	      cairo_fill(cr);	
      }
    }
  }

  // Affichage du contour (lignes et colonnes) de la grille
  cairo_set_source_rgba (cr, 0.5, 0.5, 0.5,0.8);
  for (int i=0; i<=g.nbc;i++){
    // COLONNES
    cairo_move_to (cr,position_x*i,(ecart_dessus)?position_y:0);
	  cairo_line_to(cr,position_x*i,(ecart_dessus)?size.y:(size.y-position_y));
	  cairo_set_line_width (cr, 1);
	  cairo_stroke (cr);
  }
  for (int i=0; i<=g.nbl;i++){
    // LIGNES
    cairo_move_to (cr,0,position_y*(i+ecart_dessus));
	  cairo_line_to(cr,size.x,position_y*(i+ecart_dessus));
	  cairo_set_line_width (cr, 1);
	  cairo_stroke (cr);
  }

  // Destruction du masque
	cairo_destroy(cr);
}



/**
 * \fn void debut_jeu(grille *g, grille *gc);
 * \relatesalso grille
 * \param g pointeur vers une grille
 * \param gc pointeur vers une grille
 * \brief Cette fonction débute le jeu et gère les intéractions entre l'utilisateur et le jeu.
 */
void debut_jeu(grille *g, grille *gc){
  // Initialisation de l'interface graphique.
  Display *dpy = XOpenDisplay(NULL);
  assert(dpy != NULL);
  int screen = XDefaultScreen(dpy);
  Window win = XCreateSimpleWindow(dpy, XRootWindow(dpy,screen), 1, 1, SIZEX, SIZEY, 0, BlackPixel(dpy, screen), BlackPixel(dpy, screen));
  XStoreName(dpy, win, "Jeu de la vie");
	XSelectInput(dpy, win, StructureNotifyMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);
  // Pour la fermeture de la fenêtre sur l'appui de la croix de fermeture de fenêtre
  Atom wmDeleteWindow = XInternAtom(dpy, "WM_DELETE_WINDOW", 1);
  XSetWMProtocols(dpy, win, &wmDeleteWindow, 1);
  // Creation de la surface cairo
	cairo_surface_t *surface = cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);
  // taille courante de la fenêtre
  Size size;
  size.x=SIZEX;
  size.y=SIZEY;
  // temps d'évolution
  int temps = 0;
  affiche_cairo(*g,surface,size,temps);
  // De base le compte des voisins est cyclique
  compte_voisins_vivants = compte_voisins_vivants_cyclique;

  // Boucle de jeu
  XEvent e;
  for (;;){
    affiche_cairo(*g,surface,size,temps);
    XNextEvent(dpy,&e);
    if (e.type == KeyPress){
      // Cas touche pressée
      switch (XLookupKeysym((XKeyEvent*) &e, 0)){
      case 'c':
        // Touche "c" pour activer/désactiver le voisinage cyclique
        if (compte_voisins_vivants == compte_voisins_vivants_cyclique){
					compte_voisins_vivants = compte_voisins_vivants_non_cyclique;
				} else {
					compte_voisins_vivants = compte_voisins_vivants_cyclique;
				}
        break;
      case 'v':
        // Touche "v" pour activer/désactiver le vieillissement
        if (evolue == evolue_vieillissement) unset_vieillissement();
				else set_vieillissement();
        break;
      case 'n':
        // Touche "n" pour changer de grille
        switch (change_grille_cairo(g,gc,win,dpy,surface,&size,&wmDeleteWindow)){
          case -1:
            return;
          case 1:
            temps = 0;
        }
        break;
      case 'q':
        // Touche "q" pour quitter
        // On quitte X11 et cairo
        quitter(surface,dpy);
        return;
      case 0xff0d:
        // Retour à la ligne
        evolue(g,gc);
				temps++;
        break;
      }
    } else if (e.type == ButtonPress){
      // Cas clic
      if (e.xbutton.button==1){ // Left clic
        evolue(g,gc);
				temps++;
      } else if (e.xbutton.button==3){ // Right clic
        break;
      }
    } else if (e.type == ClientMessage){
      // Cas clic de sortie
        if (e.xclient.data.l[0] == wmDeleteWindow) break; // Si clic sur la fermeture de la fenêtre
    }
    else if (e.type == ConfigureNotify){
      // Cas de modification de la taille
      size.x = e.xconfigure.width;
      size.y = e.xconfigure.height;
      cairo_xlib_surface_set_size(surface,size.x,size.y);
    }
  }

  // On quitte X11 et cairo
  quitter(surface,dpy);
}