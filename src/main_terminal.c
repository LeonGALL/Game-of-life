/** 
 * \file main_terminal.c 
 * Fichier principal.
 * \author Léon GALL
 */

#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

/**
 * \fn int main (int argc, char ** argv);
 * \param argc nombre d'éléments dans argv
 * \param argv tableau de chaines de caractères
 * \return Retourne l'état de sortie du programme
 * \brief Cette fonction est appelée au lancement du programme. Nécessite un argument : le nom du fichier de grille.
 */
int main (int argc, char ** argv) {
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>\n");
		return 1;
	}
	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	unset_vieillissement(); // Par défaut, le vieillissement est désactivé.
	affiche_tout(g,0); // On affiche le temps (initial d'où 0) et la grille.
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
