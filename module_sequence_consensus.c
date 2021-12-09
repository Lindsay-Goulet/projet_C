#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"

int longueur_seq(const char* path_input) {
    int longueur_seq=0;
    FILE* f = fopen(path_input, "r"); /* ouverture du fichier*/
		if (!f) {
			printf(RED "L'ouverture a échoué.\n" RESET);
			exit(EXIT_FAILURE);
		}

	while (fgetc(f) != '\n') longueur_seq++;
	return longueur_seq;
}

int nombre_sequences(const char* path_input) {
    int nombre_seq=0;
    int c;
    FILE* f = fopen(path_input, "r"); /* ouverture du fichier*/
		if (!f) {
			printf(RED "L'ouverture a échoué.\n" RESET);
			exit(EXIT_FAILURE);
		}

	while ((c = fgetc(f)) != EOF) 
        if (c == '\n') nombre_seq++;

	return nombre_seq;
}

void extract_sequences(const char* path_input, int long_seq, int nb_seq, char sequences[nb_seq][long_seq]) {

    int l = 0;
    int c = 0;
    int el;
    
    FILE* f = fopen(path_input, "r"); /* ouverture du fichier*/
		if (!f) {
			printf(RED "L'ouverture a échoué.\n" RESET);
			exit(EXIT_FAILURE);
		}
        
	while ((el=fgetc(f)) != EOF) {
		sequences[l][c] = el;
		c++;
		if (c==long_seq) {
			c = 0;
			l++;
		}
	}
    fclose(f);
}

int pourcentage(int nb_seq, double nb_nucleo) {
    double pct = nb_nucleo/nb_seq*100;
    if (pct == 100) return 3;
    else if (pct >= 80) return 2;
    else if (pct >= 60) return 1;
    else return 0;
}

void seq_consensus_par_position(char* seq_consensus, int position, int nb_seq, int nbA, int nbT, int nbG, int nbC) {
    int pA = pourcentage(nb_seq, nbA);
    int pT = pourcentage(nb_seq, nbT);
    int pC = pourcentage(nb_seq, nbC);
    int pG = pourcentage(nb_seq, nbG);

    if (pA == 3)
        seq_consensus[position] = 'A';
    else if (pT == 3) 
            seq_consensus[position] = 'T';
    else if (pC == 3) 
            seq_consensus[position] = 'C';
    else if (pG == 3) 
            seq_consensus[position] = 'G';

    if (pA == 2 || pT == 2 || pC == 2 || pG == 2)
        seq_consensus[position] = '*';

    if (pA == 1 || pT == 1 || pC == 1 || pG == 1)
        seq_consensus[position] = '-';
    
    if (pA == 0|| pT == 0 || pC == 0 || pG == 0)
        seq_consensus[position] = ' ';

   
}
    
void sequence_consensus(int long_seq, int nb_seq, char sequences[nb_seq][long_seq], char* seq_consensus) {
    int l;
    int c;
    int nbA;
    int nbT;
    int nbC;
    int nbG;

    for (c=0; c<long_seq; c++) { /*on prend une position dans la sequence*/
        nbA = 0;
        nbT = 0;
        nbC = 0;
        nbG = 0;
        for (l=0; l<nb_seq; l++) { /*on compte pour chaque position le nombre de A, T, C, G*/
            if (sequences[l][c] == 'A') nbA++;
            else if (sequences[l][c] == 'T') nbT++;
            else if (sequences[l][c] == 'C') nbC++;
            else nbG++;

            seq_consensus_par_position(seq_consensus, c, nb_seq, nbA, nbT, nbG, nbC);
        }
    }
}


void module_recherche_sequence_consensus() {

    char path_input[30];
    char path_output[30];

    get_path_from_user(path_input);

    int long_seq = longueur_seq(path_input);
    int nb_seq = nombre_sequences(path_input);

    char sequences[nb_seq][long_seq];
    char seq_consensus[long_seq];

    extract_sequences(path_input, long_seq, nb_seq, sequences);

    sequence_consensus(long_seq, nb_seq, sequences, seq_consensus);

    printf("Entrez le nom du fichier de votre séquence consensus.\n");
    get_path_from_user(path_output);
    save_sequence(path_output, seq_consensus);

}