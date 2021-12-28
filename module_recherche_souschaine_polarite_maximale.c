#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

//Permet de mettre de changer l'affichage dans le terminal :
#define RED   "\x1B[31m"
#define CYN   "\x1B[36m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"
#define underscore  "\x1b[4m"
#define bright      "\x1b[1m"

void matrice_alignement(char* sequence1, char* sequence2, int taille_seq1, int taille_seq2, char mat_alignement[taille_seq2+2][taille_seq1+2]) {
    //Procédure 
    
    int i;
    int j;
    
    mat_alignement[1][1] = '0';

    for (j=2; j<taille_seq1+2; j++) { //On met la polarite aa 1 sur la première ligne de la matrice
        mat_alignement[0][j] = polarite(sequence1[j-2])+'0';
        mat_alignement[1][j] = '0';
    }
    for (i=2; i<taille_seq2+2; i++) { //On met la polarite de la aa 2 sur la première colonne de la matrice
        mat_alignement[i][0] = polarite(sequence2[i-2])+'0';
        mat_alignement[i][1] = '0';
    }

    for (i=2; i<taille_seq2+2; i++) { //On parcourt la matrice
        for (j=2; j<taille_seq1+2; j++) {
            if (mat_alignement[i][0] == mat_alignement[0][j]) { 
            	//Pour chaque position, si seq1=seq2, alors on augmente de 1*/
                mat_alignement[i][j] = mat_alignement[i-1][j-1]+1;
            }
            else mat_alignement[i][j] = '0';
        }
    }
}

void trouver_souschaine_maximale(int taille_seq1, int taille_seq2, char mat_alignement[taille_seq2+2][taille_seq1+2], int* taille_souschaine, int* debut_souschaine) {
    //Procédure qui récupère la position du début et de la foin de la sous_chaine maximale
    
    int i;
    int j;
    char taille='0';
    int debut=-1;
    for (i=2; i<taille_seq2+2; i++) { //On parcourt la matrice
        for (j=2; j<taille_seq1+2; j++) {
            if (mat_alignement[i][j] > taille) { //On cherche le chiffre le plus élevé dans la matrice, il correspond à la taille de chaque sous_chaîne
            	taille = mat_alignement[i][j];
            	debut = (j-2)-(taille-'0')+1;
            }
        }
    }

    *taille_souschaine = taille-'0';
    *debut_souschaine = debut;
}


void conversion_3_lettres(char aa, char* code_3lettres) {
    if (aa == 'E') {
        code_3lettres[0] = 'G';
        code_3lettres[1] = 'l';
        code_3lettres[2] = 'u'; }

    else if (aa == 'D') {
        code_3lettres[0] = 'A';
        code_3lettres[1] = 's';
        code_3lettres[2] = 'p'; }

    else if (aa == 'A') {
        code_3lettres[0] = 'A';
        code_3lettres[1] = 'l';
        code_3lettres[2] = 'a'; }
 
    else if (aa == 'R') {
        code_3lettres[0] = 'A';
        code_3lettres[1] = 'r';
        code_3lettres[2] = 'g'; }

    else if (aa == 'N') {
        code_3lettres[0] = 'A';
        code_3lettres[1] = 's';
        code_3lettres[2] = 'n'; }

    else if (aa == 'C') {
        code_3lettres[0] = 'C';
        code_3lettres[1] = 'y';
        code_3lettres[2] = 's'; }

    else if (aa == 'Q') {
        code_3lettres[0] = 'G';
        code_3lettres[1] = 'l';
        code_3lettres[2] = 'n'; }
    
    else if (aa == 'G') {
        code_3lettres[0] = 'G';
        code_3lettres[1] = 'l';
        code_3lettres[2] = 'y'; }

    else if (aa == 'H') {
        code_3lettres[0] = 'H';
        code_3lettres[1] = 'i';
        code_3lettres[2] = 's'; } 

    else if (aa == 'I') {
        code_3lettres[0] = 'I';
        code_3lettres[1] = 'l';
        code_3lettres[2] = 'e'; }

    else if (aa == 'L') {
        code_3lettres[0] = 'L';
        code_3lettres[1] = 'e';
        code_3lettres[2] = 'u'; }

    else if (aa == 'K') {
        code_3lettres[0] = 'L';
        code_3lettres[1] = 'y';
        code_3lettres[2] = 's'; }
    
    else if (aa == 'M') {
        code_3lettres[0] = 'M';
        code_3lettres[1] = 'e';
        code_3lettres[2] = 't'; }

    else if (aa == 'F') {
        code_3lettres[0] = 'P';
        code_3lettres[1] = 'h';
        code_3lettres[2] = 'e'; }

    else if (aa == 'P') {
        code_3lettres[0] = 'P';
        code_3lettres[1] = 'r';
        code_3lettres[2] = 'o'; }

    else if (aa == 'S') {
        code_3lettres[0] = 'S';
        code_3lettres[1] = 'e';
        code_3lettres[2] = 'r'; }

    else if (aa == 'T') {
        code_3lettres[0] = 'T';
        code_3lettres[1] = 'h';
        code_3lettres[2] = 'r'; }

    else if (aa == 'W') {
        code_3lettres[0] = 'T';
        code_3lettres[1] = 'r';
        code_3lettres[2] = 'p'; }

    else if (aa == 'Y') {
        code_3lettres[0] = 'T';
        code_3lettres[1] = 'y';
        code_3lettres[2] = 'r'; }

    else if (aa == 'V') {
        code_3lettres[0] = 'V';
        code_3lettres[1] = 'a';
        code_3lettres[2] = 'l'; }

}

void creation_sous_chaine(char* sequence1, char* sous_chaine_1lettre, char* sous_chaine_polarite, char* sous_chaine_3lettres, int taille_souschaine, int debut_souschaine) {
    //Procédure
    
    int i = 0;
    int k = 0;
    int j;
    char code_3lettres[4];

    for (j=debut_souschaine; j<debut_souschaine+taille_souschaine; j++) {
        sous_chaine_1lettre[i] = sequence1[j];
        sous_chaine_polarite[i] = polarite(sequence1[j])+'0';
        conversion_3_lettres(sequence1[j], code_3lettres); /*on récupère le code 3 lettres de l'aa*/
        sous_chaine_3lettres[k] = code_3lettres[0]; /*on le stocke dans le tableau sous_chaine_3_lettres*/
        sous_chaine_3lettres[k+1] = code_3lettres[1];
        sous_chaine_3lettres[k+2] = code_3lettres[2];
        sous_chaine_3lettres[k+3] = '-';
        i++;
        k+=4;
     }

    sous_chaine_1lettre[taille_souschaine] = '\0';
    sous_chaine_polarite[taille_souschaine] = '\0';
    sous_chaine_3lettres[taille_souschaine*3+taille_souschaine-1] = '\0';
}



void save_output(int taille_sous_chaine, char* sequence1, char* sequence2, char* sous_chaine1_lettre, char* sous_chaine_polarite, char* sous_chaine_3lettres) {
    //Procédure
    
    printf("Dans quel fichier voulez-vous stocker le résultat ?\n");
    char path_output[30];
    get_path_from_user(path_output);

    FILE* f = fopen(path_output, "w"); /* ouverture du fichier*/
		if (!f) {
			printf(RED "L'ouverture a échoué.\n" RESET);
			
			exit(EXIT_FAILURE);
		}
    
    int i;
    fprintf(f, "sequence1\t");
    i=0;
    while (sequence1[i] != '\0') {
        fputc(sequence1[i], f);
        i++;
    }
    fprintf(f, "\n");
    
    fprintf(f, "sequence2\t");
    i=0;
    while (sequence2[i] != '\0') {
        fputc(sequence2[i], f);
        i++;
    }
    fprintf(f, "\n\nRecherche de la sous-chaine maximale de la sequence 1 telle que la sequence 2 contient une serie d'acides aminés de polarite identique: (0:hydrophile, 1:hydrophobe)\n\n");
    
    i=0;
    while (sous_chaine_3lettres[i] != '\0') {
        printf("%c", sous_chaine_3lettres[i]);
        fputc(sous_chaine_3lettres[i], f);
        i++;
    }
    fprintf(f, "  (longueur = %d)", taille_sous_chaine);
    fprintf(f, "\n");

    i=0;
    while (sous_chaine1_lettre[i] != '\0') {
        fputc(sous_chaine1_lettre[i], f);
        i++;
    }
    fprintf(f, "\n");

    i=0;
    while (sous_chaine_polarite[i] != '\0') {
        fputc(sous_chaine_polarite[i], f);
        i++;
    }
    fclose(f);
}

void module_sous_chaine_polarite_maximale() {
    //Procédure
    
    char path_input[30];
    char path_input2[30];

	get_path_from_user(path_input); /*on demande à l'utilisateur le fichier de la séquence à étudier*/
    printf(CYN "Avec quelle séquence voulez-vous comparer ?\n" RESET);
	get_path_from_user(path_input2);

    int taille_seq1 = longueur_sequence(path_input); /*je recupère la longueur de la seq*/
	char sequence1[taille_seq1];
	extract_sequence(path_input, sequence1); /* je stocke mes 2 seq dans 2 tableaux*/
	
    int taille_seq2 = longueur_sequence(path_input2);
    char sequence2[taille_seq2];
	extract_sequence(path_input2, sequence2);

	char mat_alignement[taille_seq2 + 2][taille_seq1 + 2];

    matrice_alignement(sequence1, sequence2, taille_seq1, taille_seq2, mat_alignement); 

	int taille_souschaine=0;
	int debut_souschaine=0;

    trouver_souschaine_maximale(taille_seq1, taille_seq2, mat_alignement, &taille_souschaine, &debut_souschaine);
	
	char sous_chaine_1lettre[taille_souschaine+1];
    char sous_chaine_polarite[taille_souschaine+1];
    char sous_chaine_3lettres[taille_souschaine*3+taille_souschaine];
	creation_sous_chaine(sequence1, sous_chaine_1lettre, sous_chaine_polarite, sous_chaine_3lettres, taille_souschaine, debut_souschaine);
   
    save_output(taille_souschaine, sequence1, sequence2, sous_chaine_1lettre, sous_chaine_polarite, sous_chaine_3lettres);
}

