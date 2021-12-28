#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

#define CYN   "\x1B[36m"
#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define BLU   "\x1B[34m"

void codons_start_stop_brin_sens(char* sequence, int taille_seq, int* start, int* stop, int* longueur) {
	//Procédure qui permet de trouver le couple de codons START et STOP de la séquence ADN dans le brin sens de la plus grande longueur

	int i;
	int j;
	int st;
	int sp;
	int l;
	int longueur_maximale=0;
	
	for (i=0; i<taille_seq-2; i++) { //On parcourt la séquence

		if ((sequence[i] == 'A') && (sequence[i+1] == 'T') && (sequence[i+2] == 'G')) { //codon START
			st = i; //Si START trouvé st prend la valeur i càd l'endroit où est le début du codon START
			j = st+3; //Pour continuer après le codon START afin de trouve un STOP
			
			while ((j<taille_seq-2) && !(((sequence[j] == 'T' && sequence[j+1] == 'A' && sequence[j+2] == 'A') 
			|| (sequence[j] == 'T' && sequence[j+1] == 'A' && sequence[j+2] == 'G') 
			|| (sequence[j] == 'T' && sequence[j+1] == 'G' && sequence[j+2] == 'A'))))
				j+=3; //Tant que pas de STOP on continue à parcourir la séquence 

			if (((sequence[j] == 'T' && sequence[j+1] == 'A' && sequence[j+2] == 'A') 
			|| (sequence[j] == 'T' && sequence[j+1] == 'A' && sequence[j+2] == 'G') 
			|| (sequence[j] == 'T' && sequence[j+1] == 'G' && sequence[j+2] == 'A'))) {/*on a trouvé un codon stop*/
				sp = j; //Si STOP trouvé sp prend la valeur j càd l'endroit où est le début du codon STOP

				if ((l = abs(st-sp)+3) > longueur_maximale) {
					longueur_maximale = l; //On prend le couple start-stop ayant la plus grande longueur
					*start = st; //On modifie les valeurs de start, stop et longueur_maximale
					*stop = sp;
					*longueur = longueur_maximale;
					
				}
			}
		}	
	}
}

void codons_start_stop_brin_antisens(char* sequence, int taille_seq, int* start, int* stop, int* longueur) {
	//Procédure qui permet de trouver le couple de codons START et STOP de la séquence ADN dans le brin antisens de la plus grande longueur 
	//Pour les commentaires : voir les commentaires de la procédure codons_start_stop_brin_sens

	int i;
	int j;
	int st;
	int sp;
	int l;
	int longueur_maximale=0;
	
	for (i=taille_seq-1; i>1; i--) { /*on parcourt la séquence*/
		
		if ((sequence[i] == 'T') && (sequence[i-1] == 'A') && (sequence[i-2] == 'C')) { //ATG devient TAC sur le brin antisens
			st = i;
			j = st-3;
			
			while ((j>1) && !(((sequence[j] == 'A' && sequence[j-1] == 'T' && sequence[j-2] == 'T') 
			|| (sequence[j] == 'A' && sequence[j-1] == 'T' && sequence[j-2] == 'C') 
			|| (sequence[j] == 'A' && sequence[j-1] == 'C' && sequence[j-2] == 'T'))))
				j-=3;

			if (((sequence[j] == 'A' && sequence[j-1] == 'T' && sequence[j-2] == 'T') 
			|| (sequence[j] == 'A' && sequence[j-1] == 'T' && sequence[j-2] == 'C') 
			|| (sequence[j] == 'A' && sequence[j-1] == 'C' && sequence[j-2] == 'T'))) {
				sp = j;

				if ((l = abs(st-sp)+3) > longueur_maximale) {
					longueur_maximale = l; 
					*start = st; 
					*stop = sp;
					*longueur = longueur_maximale;
					
				}
			}
		}	
	}
}

void sequence_complementaire(char * sequence, int taille_seq) {
	//Procédure qui permet de créer la séquence complémentaire 

	int i;
	for (i=0; i<taille_seq; i++) {
		if (sequence[i] == 'A') sequence[i] = 'T';
		else if (sequence[i] == 'T') sequence[i] = 'A';
		else if (sequence[i] == 'C') sequence[i] = 'G';
		else if (sequence[i] == 'G') sequence[i] = 'C';
	}
}

int codons_start_stop_ORF_max(char* sequence, int taille_seq, int* start, int* stop, int* taille) {
	//Fonction qui permet de sélectionner la plus grande ORF parmis celles trouvés dans les brins sens et antisens 

	int start_sens = -1;
	int stop_sens = -1;
	int start_antisens = -1;
	int stop_antisens = -1;
	int longueur_sens = -1;
	int longueur_antisens = -1;
	
	codons_start_stop_brin_sens(sequence, taille_seq, &start_sens, &stop_sens, &longueur_sens); //On récupère les codons START, STOP et la longueur de l'ORF dans les brins sens et antisens 
	codons_start_stop_brin_antisens(sequence, taille_seq, &start_antisens, &stop_antisens, &longueur_antisens);
	
	if (longueur_sens != -1 && longueur_antisens != -1) {
		
		if (longueur_sens >= longueur_antisens) { 
			*start = start_sens;
			*stop = stop_sens;
			*taille = longueur_sens;	
			return 2; //2 si ORF trouvée dans le brin sens
		}
		else {
			*start = start_antisens;
			*stop = stop_antisens;
			*taille = longueur_antisens;
			return 1; //1 si ORF trouvée dans le brin antisens
		}
	}
	else {
		if (longueur_sens != -1 && longueur_antisens == -1) {
			*start = start_sens;
			*stop = stop_sens;
			*taille = longueur_sens;
			return 2; //2 si ORF trouvée dans le brin sens
		}
		else {
			if (longueur_sens == -1 && longueur_antisens != -1)  {
				*start = start_antisens;
				*stop = stop_antisens;
				*taille = longueur_antisens;
				return 1; //1 si ORF trouvée dans le brin antisens
			}
			else { 
				return 0; //0 si aucune ORF n'est trouvée et donc que la séquence n'est pas codante
			}
		}
	}
}

void creation_sequence_ORF_sens(int taille_seq_codante, char* sequence, int start, int stop, char* seq_cod) {
	//Procédure qui permet de créer un tableau de caractères contenant l'ORF dans le brin sens
	int j=0;
	int i;
		for (i=start; i<stop+3; i++) {
			seq_cod[j] = sequence[i];
			j++;
		}
	seq_cod[taille_seq_codante] = '\0';
}

void creation_sequence_ORF_antisens(int taille_seq_codante, char* sequence, int start, int stop, char* seq_cod) {
	//Procédure qui permet de créer un tableau de caractères contenant l'ORF dans le brin antisens
	int j=taille_seq_codante-1;
	int i;
	for (i=stop-2; i<start+1; i++) {
		seq_cod[j] = sequence[i];
		j--;
	}
	sequence_complementaire(seq_cod, taille_seq_codante); //Prend la séquence complémentaire de l'ORF qui a été mis dans le bon sens (5' -> 3')
	seq_cod[taille_seq_codante] = '\0';
}

void module_recherche_sequence_codante_maximale() {
	/* - Procédure qui demande en entrée un fichier contenant une séquence ADN au format FASTA.
	   - Recherche dans la séquence ADN la plus grande séquence codante
	   - Et renvoie dans un fichier cette CDS*/

	int start;
	int stop;
	int taille_seq_codante;
   
    char path_input[30];
    char path_output[30];

    get_path_from_user(path_input); //Demande la séquence ADN à tester

    int taille_seq = longueur_sequence(path_input); //Initialise la longueur de la séquence
    char sequence[taille_seq+1];
	extract_sequence(path_input, sequence); //Permet de stocker la séquence ADN dans un tableau
	
	int codante = codons_start_stop_ORF_max(sequence, taille_seq, &start, &stop, &taille_seq_codante); //Renvoie 2 si codant sur brin sens, 1 si codant sur brin antisens, 0 si non codant
	char seq_cod[taille_seq_codante+1];

	//Si l'ORF se trouve sur le brin sens
	if (codante == 2) {
		creation_sequence_ORF_sens(taille_seq_codante, sequence, start, stop, seq_cod);
        printf(BLU "Entrez le nom du fichier de votre séquence codante maximale.\n" RESET);
        get_path_from_user(path_output);
		save_sequence(path_output, seq_cod);
	}

	//Si l'ORF se trouve sur le brin antisens
	else {
		if (codante == 1) {
			creation_sequence_ORF_antisens(taille_seq_codante, sequence, start, stop, seq_cod);
			printf(BLU "Entrez le nom du fichier de votre séquence codante maximale.\n" RESET);
            get_path_from_user(path_output);
            save_sequence(path_output, seq_cod);
		}

		//Si codante==0 et donc qu'aucun ORF n'a été trouvé (séquence non codante)
		else {
			printf(RED "Erreur. La séquence n'est pas codante." RESET);
		}
	}
}
	