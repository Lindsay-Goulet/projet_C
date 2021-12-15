#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

//Permet de mettre de changer l'affichage dans le terminal :
#define CYN   "\x1B[36m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define RESET "\x1B[0m"
#define bright "\x1b[1m"
#define underscore  "\x1b[4m" 

int nb_aa_polarite(int taille_seq, char* sequence1, char* sequence2) {
	//Fonction qui permet de compter entre deux séquences le nb d'aa de polarité identique
	
	int i;
	int nb_ide=0;
	for (i=0; i<taille_seq; i++) { 
		if (polarite(sequence1[i]) != -9) { //Utilisation d'une fonction de utiles.c qui renvoie 1 si aa polaire et 0 sinon;
		//Si GAP polarité = -9, comme ça on regarde les polarités sans les GAP
			if (polarite(sequence1[i]) == polarite(sequence2[i])) { //Parcours les séq et compte le nb de différence entre les deux
				nb_ide++; //Compteur
			}
		}
	}
	return nb_ide;
}

void seq_id_pol(int taille_seq, char* sequence1, char* sequence2, char* id) {
	//Procédure qui permet 

	int i;
    int p;
	for (i=0; i<taille_seq; i++) {
		if ((p=polarite(sequence1[i])) == polarite(sequence2[i])) { //Création de la seq "id" qui s'affichera dans le terminal afin de voir la comparaison de polarité des deux séquences.
			id[i] = p+'0'; //Convertir des int en char avec p qui peut être 0 si hydrophiles et 1 si hydrophobes
		}
		else {
			id[i] = '-'; //- si pas la même polarité
		}
	}
}


void module_score_pol() {
	/* - Procédure qui demande à l'utilisateur deux fichiers contenant chacune une séquence.
	   - Les séquences doivent être de même taille. 
	   - Ce module permet de comparer la polarité des deux séquences.*/

	char path_input[30];
    char path_input2[30];

	get_path_from_user(path_input); //On demande à l'utilisateur le fichier de la première séquence à étudier
    printf(CYN "Avec quelle séquence voulez-vous comparer ?\n" RESET);
	get_path_from_user(path_input2); //On demande à l'utilisateur le fichier de la deuxième séquence à étudier
	
	int taille_seq = longueur_sequence(path_input); //Récupère la longueur de la seq
	char seq1[taille_seq];
	extract_sequence(path_input, seq1); //Stocke les 2 seq dans 2 tableaux
	char seq2[taille_seq];
	extract_sequence(path_input2, seq2);
	
	int ide = nb_aa_polarite(taille_seq, seq1, seq2); //Compte les polarités identiques
	double score = ide*100/taille_seq;  //Conversion en %
	char id[taille_seq];
	seq_id_pol(taille_seq, seq1, seq2, id); //Création de la seq id pour l'affichage

	printf("\n" bright underscore "Similarité de polarité: " RESET "\t%d/%d, soit %.2f %%.\n", ide, taille_seq, score);
	printf("0 : hydrophiles, 1 : hydrophobes, - : différents\n");
	printf(BLU "seq1\t" RESET);

	int i; //Compteur pour l'affichage de chaque élément

	//Affichage des deux séquences et de la séquence "id" qui compare les polarités.
	for (i=0; i<taille_seq; i++) { printf("%c", seq1[i]); } printf("\n"); 
	printf(MAG "seq2\t" RESET);

	for (i=0; i<taille_seq; i++) { printf("%c", seq2[i]); } printf("\n");
	printf(YEL "id\t" RESET );

	for (i=0; i<taille_seq; i++) { printf("%c", id[i]); } printf("\n");
}

