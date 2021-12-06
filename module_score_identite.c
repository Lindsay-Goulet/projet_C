#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"



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

void module_score_id() {

	char path_input[30];
    char path_input2[30];

	get_path_from_user(path_input); /*on demande à l'utilisateur le fichier de la séquence à étudier*/
    printf("Avec quelle séquence voulez-vous comparer ?\n");
	get_path_from_user(path_input2);

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

