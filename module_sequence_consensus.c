#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

//Permet de mettre de changer l'affichage dans le terminal :
#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define CYN   "\x1B[36m"

int longueur_seq(const char* path_input) {
    //Fonction qui permet d'avoir la longueur de la séquence
    int longueur_seq=0;
    FILE* f = fopen(path_input, "r"); //Ouverture du fichier
		if (!f) {
			printf(RED "L'ouverture a échoué.\n" RESET);
			exit(EXIT_FAILURE);
		}

	while (fgetc(f) != '\n') longueur_seq++;
	return longueur_seq;
}

int nombre_sequences(const char* path_input) {
    //Fonction qui retourne le nombre de séquence du fichier FASTA d'alignement multiple
    int nombre_seq=0;
    int c;
    FILE* f = fopen(path_input, "r"); //Ouverture du fichier
		if (!f) {
			printf(RED "L'ouverture a échoué.\n" RESET);
			exit(EXIT_FAILURE);
		}

	while ((c = fgetc(f)) != EOF) 
        if (c == '\n') nombre_seq++;

	return nombre_seq;
}

void extract_sequences(const char* path_input, int long_seq, int nb_seq, char sequences[nb_seq][long_seq]) {
    //Procédure qui permet d'extraire les séquences du fichier d'alignement multiple en les mettant dans un tableau de caractères
    //Dans ce tableau, chaque ligne est une nouvelle séquence
    int l = 0;
    int c = 0;
    int el;
    
    FILE* f = fopen(path_input, "r"); //Ouverture du fichier
		if (!f) {
			printf(RED "L'ouverture a échoué.\n" RESET);
			exit(EXIT_FAILURE);
		}
        
	while ((el=fgetc(f)) != EOF) {
        if (el != '\n') {
		    sequences[l][c] = el;
		    c++;
        }
		if (c==long_seq) {
			c = 0;
			l++;
		}
	}
    fclose(f);
}

int pourcentage(int nb_seq, double nb_nucleo) {
    //Fonction qui retourne 3 si le pourcentage d'alignement d'un caractère est 100%, 2 si au moins 80%, 1 si au moins 60%, 0 sinon.
    double pct = nb_nucleo/nb_seq*100;
    if (pct == 100) return 3;
    else if (pct >= 80) return 2;
    else if (pct >= 60) return 1;
    else return 0;
}

void seq_consensus_par_position(char* seq_consensus, int position, int nb_seq, int nbA, int nbT, int nbG, int nbC) {
    //Procédure qui permet pour une position donnée d'afficher le caractères correspondant au taux d'apparition d'un aa 
    
    //Pourcentage d'apparition de chaque nucléotide à une position donnée
    int pA = pourcentage(nb_seq, nbA); 
    int pT = pourcentage(nb_seq, nbT);
    int pC = pourcentage(nb_seq, nbC);
    int pG = pourcentage(nb_seq, nbG);

    //Conditions pour taux d'apparition = 100%, affichage du nucléotide
    if (pA == 3)
        seq_consensus[position] = 'A';
    else if (pT == 3) 
            seq_consensus[position] = 'T';
    else if (pC == 3) 
            seq_consensus[position] = 'C';
    else if (pG == 3) 
            seq_consensus[position] = 'G';

    //Conditions pour taux d'apparition = 80%, affichage d'une *
    else if (pA == 2 || pT == 2 || pC == 2 || pG == 2)
        seq_consensus[position] = '*';

    //Conditions pour taux d'apparition = 60%, affichage d'un -
    else if (pA == 1 || pT == 1 || pC == 1 || pG == 1)
        seq_consensus[position] = '-';
    
    //Conditions pour taux d'apparition < 60%, affichage d'un espace ' '
    else if (pA == 0|| pT == 0 || pC == 0 || pG == 0)
        seq_consensus[position] = ' ';
   
}
    
void sequence_consensus(int long_seq, int nb_seq, char sequences[nb_seq][long_seq], char* seq_consensus) {
    //Procédure qui permet de construire et d'afficher dans le nouveau fichier la séquence consensus 
    
    int l; //Compteur de colonnes
    
    int c; //Compteur de lignes
    
    //Nombre de chaque nucléotide pour une position donnée
    int nbA; 
    int nbT;
    int nbC;
    int nbG;

    for (c=0; c<long_seq; c++) { //On prend une position dans la séquence
        //Initialise le nb de nucléotide à 0
        nbA = 0;
        nbT = 0;
        nbC = 0;
        nbG = 0;
        
        for (l=0; l<nb_seq; l++) { //On compte pour chaque position le nombre de A, T, C, G*/
            if (sequences[l][c] == 'A') nbA++;
            else if (sequences[l][c] == 'T') nbT++;
            else if (sequences[l][c] == 'C') nbC++;
            else if (sequences[l][c] == 'G') nbG++;

            //Permet de calculer le % d'apparition pour chaque position et retourne le chiffre correspondant (0, 1, 2, 3)
            //Puis construit la séquence consensus au fur et à mesure que les compteurs l et c avancent
            seq_consensus_par_position(seq_consensus, c, nb_seq, nbA, nbT, nbG, nbC); 
        }
    }
}

void module_recherche_sequence_consensus() {
/* - Procédure qui demande en entrée un fichier contenant un alignement de séquences au format FASTA.
   - Regarde le pourcentage d'identité pour chaque position de l'alignement
   - Et renvoie un caractère en fonction du pourcentage.*/ 

    char path_input[30];
    char path_output[30];

    get_path_from_user(path_input); //Demande le fichier d'alignement multiple à analyser

    int long_seq = longueur_seq(path_input); //Retourne la longueur des séquences
    int nb_seq = nombre_sequences(path_input); //Retourne le nb de séquences

    char sequences[nb_seq][long_seq]; //Crée un tableau du nb de séquences en lignes et de la longueur des séquences en colonnes
    char seq_consensus[long_seq]; //Crée un tableau qui accueillera la séquence consensus

    extract_sequences(path_input, long_seq, nb_seq, sequences); //Extrait les séquences du fichier FASTA pour les mettre dans le tableau créé précédemment

    sequence_consensus(long_seq, nb_seq, sequences, seq_consensus); //Construit la séquence consensus dans le tableau créé précédemment

    printf(CYN "Entrez le nom du fichier de votre séquence consensus."RESET"\n" );
    get_path_from_user(path_output); //Demande le nom du fichier de sortie à l'utilisateur
    save_sequence(path_output, seq_consensus); //Puis y insère la séquence consensus

}