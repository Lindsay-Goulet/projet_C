#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

#define CYN   "\x1B[36m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"
#define underscore  "\x1b[4m"
#define bright      "\x1b[1m"

void matrice_alignement(char* sequence1, char* sequence2, int taille_seq1, int taille_seq2, char mat_alignement[taille_seq2+2][taille_seq1+2]) {
    int i;
    int j;
    
    mat_alignement[1][1] = '0';
    mat_alignement[0][0] = '0';
    mat_alignement[0][1] = '0';
    mat_alignement[1][0] = '0';

    for (j=2; j<taille_seq1+2; j++) { /*on met la polarite sequence 1 sur la première ligne de la matrice*/
        mat_alignement[0][j] = polarite(sequence1[j-2])+'0';
        mat_alignement[1][j] = '0';
    }
    for (i=2; i<taille_seq2+2; i++) { /*on met la polarite de la sequence 2 sur la première colonne de la matrice*/
        mat_alignement[i][0] = polarite(sequence2[i-2])+'0';
        mat_alignement[i][1] = '0';
    }

    for (i=2; i<taille_seq2+2; i++) { /*on parcourt la matrice*/
        for (j=2; j<taille_seq1+2; j++) {
            if (mat_alignement[i][0] == mat_alignement[0][j]) { 
            	/*pour chaque position, si seq1=seq2, alors on augmente de 1*/
                mat_alignement[i][j] = mat_alignement[i-1][j-1]+1;
            }
            else mat_alignement[i][j] = '0';
        }
    }
}

void trouver_souschaine_maximale(int taille_seq1, int taille_seq2, char mat_alignement[taille_seq2+2][taille_seq1+2], int* taille_souschaine, int* debut_souschaine) {
    int i;
    int j;
    char taille='0';
    int debut=-1;
    for (i=2; i<taille_seq2+2; i++) { /*on parcourt la matrice*/
        for (j=2; j<taille_seq1+2; j++) {
            if (mat_alignement[i][j] > taille) {
            	taille = mat_alignement[i][j];
            	debut = (j-2)-(taille-'0')+1;
            }
        }
    }

    *taille_souschaine = taille-'0';
    *debut_souschaine = debut;
}
    
void creation_sous_chaine(char* sequence1, char* sous_chaine_1lettre, char* sous_chaine_polarite, char* sous_chaine_3lettres, int taille_souschaine, int debut_souschaine) {
    sous_chaine_1lettre[taille_souschaine] = '\0';
    sous_chaine_polarite[taille_souschaine] = '\0';
    sous_chaine_1lettre[taille_souschaine*3] = '\0';
    int i = 0;
    int j;


    for (j=debut_souschaine; j<debut_souschaine+taille_souschaine; j++) {
        sous_chaine_1lettre[i] = sequence1[j];
        sous_chaine_polarite[i] = polarite(sequence1[j])+'0';
       /* sous_chaine_3lettres[i] = ??? ; */
        i++;
     }
}

void save_output(char* sequence1, char* sequence2, char* sous_chaine1_lettre, char* sous_chaine_polarite, char* sous_chaine_3lettres) {
    printf("Dans quel fichier voulez-vous stocker le résultat ?\n");
    char path_output[30];
    get_path_from_user(path_output);

    FILE* f = fopen(path_input, "w"); /* ouverture du fichier*/
		if (!f) {
			printf(RED "L'ouverture a échoué.\n" RESET);
			
			exit(EXIT_FAILURE);
		}
    
    int i;
    fprintf(f, "sequence1\t");
    while (sequence1[i] != '\0' {
        fprintf(f, sequence1[i]);
    }
    fprint("\n");
    
    fprintf(f, "sequence2\t");
    while (sequence2[i] != '\0' {
        fprintf(f, sequence2[i]);
    }
    fprint("\n\nRecherche de la sous-chaîne maximale de la séquence 1 telle que la séquence 2 contient
une série d’acides aminés de polarité identique: (0:hydrophile, 1:hydrophobe)\n\n");
    
    while (sous_chaine_3lettres[i] != '\0' {
        fprintf(f, sous_chaine_3lettres[i]);
    }
    fprint("\n");

    while (sous_chaine1_lettre[i] != '\0' {
        fprintf(f, sous_chaine1_lettre[i]);
    }
    fprint("\n");

    while (sous_chaine_polarite[i] != '\0' {
        fprintf(f, sous_chaine_polarite[i]);
    }
    fclose(f);
}



void module_sous_chaine_polarite_maximale() {
    char path_input[30];
    char path_input2[30];

	get_path_from_user(path_input); /*on demande à l'utilisateur le fichier de la séquence à étudier*/
    printf(CYN "Avec quelle séquence voulez-vous comparer ?\n" RESET);
	get_path_from_user(path_input2);

    int taille_seq1 = longueur_sequence(path_input); /*je recupère la longueur de la seq*/
	char sequence1[taille_seq1];
	extract_sequence(path_input, seq1); /* je stocke mes 2 seq dans 2 tableaux*/
	
    int taille_seq2 = longueur_sequence(path_input2);
    char sequence2[taille_seq2];
	extract_sequence(path_input2, seq2);

	char mat_alignement[taille_seq2 + 2][taille_seq1 + 2];

    matrice_alignement(sequence1, sequence2, taille_seq1, taille_seq2, mat_alignement); 

	int taille_souschaine=0;
	int debut_souschaine=0;

    trouver_souschaine_maximale(taille_seq1, taille_seq2, mat_alignement, &taille_souschaine, &debut_souschaine);
	
	char sous_chaine_1lettre[taille_souschaine+1];
    char sous_chaine_polarite[taille_souschaine+1];
    char sous_chaine_3lettres[taille_souschaine*3+1]
	creation_sous_chaine(sequence1, taille_seq1 sous_chaine_1lettre, sous_chaine_polarite, sous_chaine_3lettres, taille_souschaine, debut_souschaine);
   
    save_output(sequence1, sequence2, sous_chaine1_lettre, sous_chaine_polarite, sous_chaine_3lettres);
}

