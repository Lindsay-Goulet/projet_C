#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

double pourct_id(double taille_seq, int nb_id) {
	double id = nb_id*100/taille_seq; /*produit en croix pour calculer le pourcentage*/
	return id;
}

int nb_nucleotide_ident(char* sequence1, char* sequence2, int taille_seq) {
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
	int c;

    FILE* f = fopen(path_input, "r"); /* ouverture du fichier*/
	if (!f) {
		printf("L'ouverture a echoué.\n");
		exit(EXIT_FAILURE);
	}

	while ((c=fgetc(f)) != EOF) { /*je parcours tout le fichier et je compte les éléments*/
		if (c != '\n') {
			taille_seq++;
		}
	}
	
	return taille_seq; 
}

void seq_id(int taille_seq, char* seq1, char* seq2, char* id) {
	int i;
	for (i=0; i<taille_seq; i++) {
		if (seq1[i] == seq2[i]) { /*ça c'est pour écrire les séq dans le terminal. Je créé ma seq "id" donc je mets le nucléo quand il est identique et sinon je mets un - */
			id[i] = seq1[i];
		}
		else {
			id[i] = '-';
		}
	}
}

void module_score_id(const char* path_input, const char* path_input2) {
	int i;
	
	int taille_seq = longueur_sequence(path_input); /*je recupère la longueur de la seq*/
	char seq1[taille_seq];
	extract_sequence(path_input, seq1); /* je stocke mes 2 seq dans 2 tableaux*/
	char seq2[taille_seq];
	extract_sequence(path_input2, seq2);
	
	int ide = nb_nucleotide_ident(seq1, seq2, taille_seq); /* je compte les diff*/
	double score = pourct_id(taille_seq, ide); /*conversion en %*/
	char id[taille_seq];
	seq_id(taille_seq, seq1, seq2, id); /* création de la seq id pour l'affichage*/

	printf("Identité de séquence: %d/%d, soit %.2f %%.\n", ide, taille_seq, score);
	printf("seq1\t");

	for (i=0; i<taille_seq; i++) { printf("%c", seq1[i]); } printf("\n"); /*affichage des seq*/
	printf("seq2\t");

	for (i=0; i<taille_seq; i++) { printf("%c", seq2[i]); } printf("\n");
	printf("id\t");

	for (i=0; i<taille_seq; i++) { printf("%c", id[i]); } printf("\n");
}

int main('f1.txt') {
	printf("Avec quelle séquence voulez-vous comparer ?");
	char path_input2[30];
	get_path_from_user(char* path_input2);
	module_score_id(path_input, path_input2);
}