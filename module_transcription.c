#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

#define RED   "\x1B[31m"
#define CYN   "\x1B[36m"
#define RESET "\x1B[0m"

void transcription(char* sequence, int taille_seq) {
    //Procédure qui transcrit une séquence, remplace les T par des U.
    int i;
    for (i=0; i<taille_seq; i++) {
        if (sequence[i] == 'T') {
            sequence[i] = 'U';
        }
    }
}

void module_transcription_sequence() {
    //Procédure qui permet de créer un nouveau fichier avec le brin transcrit
    
    char path_input[30];
    char path_output[30];
    int v;

    do {

        get_path_from_user(path_input); //Demande le fichier à transcrire

        int taille_seq = longueur_sequence(path_input);
        char sequence[taille_seq];
	    extract_sequence(path_input, sequence); //Permet de stocker la séquence dans un tableau

        v = verification_sequence(path_input, sequence, taille_seq); //Permet de vérifier si la séquence est codante

        if (v == 1) { //Si la séquence est codante
            printf(CYN "Entrez le nom du fichier de votre séquence transcrite.\n" RESET);
            get_path_from_user(path_output); //Demande à l'utilisateur le nom du fichier de sortie
            transcription(sequence, taille_seq); //Création de la séquence transcrite
            save_sequence(path_output, sequence); //Permet de sauvegarder la nouvelle séquence transcrite dans un fichier
        }
        else { //Si la séquence est non codante
            printf(RED "Erreur, séquence non codante.\nDonnez un autre fichier.\n" RESET);
        }
    }
    while(v == 0); //Faire toutes les instructions passées tant que la séquence n'est pas codante
}