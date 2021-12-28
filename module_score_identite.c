#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

//Permet de mettre de changer l'affichage dans le terminal :
#define CYN   "\x1B[36m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"
#define underscore  "\x1b[4m"
#define bright      "\x1b[1m"

int nb_nucleotide_ident(char* sequence1, char* sequence2, int taille_seq) {
	//Fonction qui permet de compter entre deux séquences les nucléotides identiques.
	int i;
	int identique=0;
	for (i=0; i<taille_seq; i++) { 
		if (sequence1[i] == sequence2[i]) { //Je parcours mes séq et je compte le nb de différence entre les deux
			identique++;
		}
	}
	return identique;
}



void seq_id(int taille_seq, char* seq1, char* seq2, char* id) {
	//Procédure qui permet d'écrire les nucléotides identiques dans le terminal, et si ils sont différents met un -
	int i;
	for (i=0; i<taille_seq; i++) {
		if (seq1[i] == seq2[i]) { 
			id[i] = seq1[i]; 
		}
		else {
			id[i] = '-';
		}
	}
}

void module_score_id() {
	/* - Procédure qui demande à l'utilisateur deux fichiers contenant chacune une séquence.
	   - Les séquences doivent être de même taille. 
	   - Ce module permet de compter le nb de caractères identiques à la même place dans les 2 seéquences.*/
	char path_input[30];
    char path_input2[30];

	get_path_from_user(path_input); //On demande à l'utilisateur le fichier de la première séquence à étudier
    printf(CYN "Avec quelle séquence voulez-vous comparer ?\n" RESET);
	get_path_from_user(path_input2); //On demande à l'utilisateur le fichier de la deuxième séquence à étudier

	int i;
	
	int taille_seq = longueur_sequence(path_input); //Permet de récupérer la longueur de la séquence
	char seq1[taille_seq];
	extract_sequence(path_input, seq1); //Permet de stocker la première séquence dans un tableau
	char seq2[taille_seq];
	extract_sequence(path_input2, seq2); //Permet de stocker la deuxième séquence dans un tableau
	
	int ide = nb_nucleotide_ident(seq1, seq2, taille_seq); //Recupère le nb de nucléotides identiques entre les deux séquences 
	double score = ide*100/taille_seq;//Conversion en % de l'identité de séquence
	char id[taille_seq];
	seq_id(taille_seq, seq1, seq2, id); //Création de la seq id pour l'affichage

	//Affichage dans le terminal : 
	printf("\n" underscore bright "Identité de séquence:" RESET " \t%d/%d, soit %.2f %%.\n", ide, taille_seq, score);
	printf(BLU "seq1\t" RESET);

	for (i=0; i<taille_seq; i++) { printf("%c", seq1[i]); } printf("\n"); 
	printf(MAG "seq2\t" RESET);

	for (i=0; i<taille_seq; i++) { printf("%c", seq2[i]); } printf("\n");
	printf(YEL "id\t" RESET);

	for (i=0; i<taille_seq; i++) { printf("%c", id[i]); } printf("\n");
}

