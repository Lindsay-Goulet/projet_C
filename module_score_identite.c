#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

double pourct_id(double ls, int nb_id) {
	double id = nb_id*100/ls; /*produit en croix pour calculer le pourcentage*/
	return id;
}

int nb_nucleotide_ident(char* sequence1, char* sequence2, taille_seq) {
	int i;
	int identique=0;
	for (i=0; i<taille_seq; i++) { 
		if (sequence1[i] == sequence2[i]) { /*je parcours mes séq et je compte le nb de différence entre les deux */
			identique++;
		}
	}
	return identique;
}

int longueur_sequence(const char* path_input) {
    /*ajouter procédure qui supprime la ligne avant la sequence*/
    int taille_seq=0;

    FILE* f = fopen(fic, "r"); /* ouverture du fichier*/
	if (!f) {
		printf("L'ouverture a echoué.\n");
		exit(EXIT_FAILURE);
	}

	while (fgetc(f) != '\n' && != EOF) { /*je parcours tout le fichier et je compte les éléments*/
		if (el != '\n') {
			taille_seq++;
		}
	}
	
	return taille_seq; 
}