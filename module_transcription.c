#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

#define RED   "\x1B[31m"
#define CYN   "\x1B[36m"
#define RESET "\x1B[0m"

void transcription(char* sequence, int taille_seq) {
    int i;
    for (i=0; i<taille_seq; i++) {
        if (sequence[i] == 'T') {
            sequence[i] = 'U';
        }
    }
}

void module_transcription_sequence() {
    char path_input[30];
    char path_output[30];
    int v;

    do {

        get_path_from_user(path_input);

        int taille_seq = longueur_sequence(path_input);
        char sequence[taille_seq];
	    extract_sequence(path_input, sequence);

        v = verification_sequence(path_input, sequence, taille_seq);

        if (v == 1) {
            printf(CYN "Entrez le nom du fichier de votre séquence transcrite.\n" RESET);
            get_path_from_user(path_output);
            transcription(sequence, taille_seq);
            save_sequence(path_output, sequence);
        }
        else {
            printf(RED "Erreur, séquence non codante.\nDonnez un autre fichier.\n" RESET);
        }
    }
    while(v == 0);
}