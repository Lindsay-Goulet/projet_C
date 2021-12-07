#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

void transcription(char* sequence, int taille_seq) {
    int i;
    for (i=0; i<taille_seq; i++) {
        if (sequence[i] == 'T') {
            sequence[i] = 'U';
        }
    }
}

int verification_sequence(char* path_input, char* sequence, int taille_seq) {
    extract_sequence(path_input, sequence);

    if ((sequence[0] == 'A') && (sequence[1] == 'T') && (sequence[2] == 'G') && (taille_seq%3 == 0)) {
        return 1;

    }

    else { 
        return 0;
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
            printf("Entrez le nom du fichier de votre séquence transcrite.\n");
            get_path_from_user(path_output);
            transcription(sequence, taille_seq);
            save_sequence(path_output, sequence);
        }
        else {
            printf("Erreur, séquence non codante.\nDonnez un autre fichier.\n");
        }
    }
    while(v == 0);
}