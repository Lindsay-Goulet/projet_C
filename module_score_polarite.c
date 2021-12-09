#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

#define CYN   "\x1B[36m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define RESET "\x1B[0m"
#define bright "\x1b[1m"
#define underscore  "\x1b[4m" /*Souligné*/

int nb_aa_polarite(int taille_seq, char* sequence1, char* sequence2) {
	int i;
	int nb_ide=0;
	for (i=0; i<taille_seq; i++) { 
		if (polarite(sequence1[i]) != -9) { /*si l'aa n'est pas "-"*/
			if (polarite(sequence1[i]) == polarite(sequence2[i])) { /*je parcours mes séq et je compte le nb de différence entre les deux */
				nb_ide++;
			}
		}
	}
	return nb_ide;
}

void seq_id_pol(int taille_seq, char* sequence1, char* sequence2, char* id) {
	int i;
    int p;
	for (i=0; i<taille_seq; i++) {
		if ((p=polarite(sequence1[i])) == polarite(sequence2[i])) { /*ça c'est pour écrire les séq dans le terminal. Je créé ma seq "id" donc je mets le nucléo quand il est identique et sinon je mets un - */
			id[i] = p+'0';
		}
		else {
			id[i] = '-';
		}
	}
}


void module_score_pol() {
	char path_input[30];
    char path_input2[30];

	get_path_from_user(path_input); /*on demande à l'utilisateur le fichier de la séquence à étudier*/
    printf(CYN "Avec quelle séquence voulez-vous comparer ?\n" RESET);
	get_path_from_user(path_input2);

	int i;
	
	int taille_seq = longueur_sequence(path_input); /*je recupère la longueur de la seq*/
	char seq1[taille_seq];
	extract_sequence(path_input, seq1); /* je stocke mes 2 seq dans 2 tableaux*/
	char seq2[taille_seq];
	extract_sequence(path_input2, seq2);
	
	int ide = nb_aa_polarite(taille_seq, seq1, seq2); /* je compte les diff*/
	double score = pourct_id(taille_seq, ide); /*conversion en %*/
	char id[taille_seq];
	seq_id_pol(taille_seq, seq1, seq2, id); /* création de la seq id pour l'affichage*/

	printf("\n" bright underscore "Similarité de polarité: " RESET "\t%d/%d, soit %.2f %%.\n", ide, taille_seq, score);
	printf("0 : hydrophiles, 1 : hydrophobes, - : différents\n");
	printf(BLU "seq1\t" RESET);

	for (i=0; i<taille_seq; i++) { printf("%c", seq1[i]); } printf("\n"); /*affichage des seq*/
	printf(MAG "seq2\t" RESET);

	for (i=0; i<taille_seq; i++) { printf("%c", seq2[i]); } printf("\n");
	printf(YEL "id\t" RESET );

	for (i=0; i<taille_seq; i++) { printf("%c", id[i]); } printf("\n");
}

