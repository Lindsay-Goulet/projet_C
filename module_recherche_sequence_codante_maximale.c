#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utiles.h"


void codons_start_stop_brin_sens(char* sequence, int taille_seq, int* start, int* stop, int* longueur) {
	int i;
	int st;
	int sp;
	int l;
	int longueur_maximale=0;
	for (i=0; i<taille_seq-2; i++) { /*on parcourt la séquence*/
		if ((sequence[i] == 'A') && (sequence[i+1] == 'T') && (sequence[i+2] == 'G')) { /*on a trouvé un codon start*/
			/*on cherche donc le codon stop le plus éloigné tq la distance entre les 2 est mutiple de 3*/
			st = i; /*début de codon start*/
			for (i=st+3; i<taille_seq-2;  i=i+3) {
				if (((sequence[i] == 'T' && sequence[i+1] == 'A' && sequence[i+2] == 'A') || (sequence[i] == 'T' && sequence[i+1] == 'A' && sequence[i+2] == 'G') || (sequence[i] == 'T' && sequence[i+1] == 'G' && sequence[i+2] == 'A'))) {
					sp=i; /*début du codon stop*/
					if ((l = abs(st-sp)+3) > longueur_maximale) {
						longueur_maximale = l; /*on prend le couple start-stop ayant la plus grande longueur*/
						*start = st; /*on modifie les valeurs de start et stop*/
						*stop = sp;
						*longueur = longueur_maximale;
			}
				}
			}
		}
	}
}

void codons_start_stop_brin_antisens(char* sequence, int taille_seq, int* start, int* stop, int* longueur) {
	int i;
	int st;
	int sp;
	int l;
	int longueur_maximale=0;
	for (i=0; i<taille_seq-2; i++) { /*on parcourt la séquence*/
		if (((sequence[i] == 'A' && sequence[i+1] == 'A' && sequence[i+2] == 'T') || (sequence[i] == 'G' && sequence[i+1] == 'A' 			&& sequence[i+2] == 'T') || (sequence[i] == 'A' && sequence[i+1] == 'G' && sequence[i+2] == 'T'))) { /*on a trouvé un codon stop*/
			/*on cherche donc le codon start le plus éloigné tq la distance entre les 2 est mutiple de 3*/
			sp = i+2; /*début de codon stop*/
			
			for (i=sp+1; i<taille_seq-2; i=i+3) {
				if ((sequence[i] == 'G') && (sequence[i+1] == 'T') && (sequence[i+2] == 'A'))  {
					st=i+2; /*début du codon start*/
					if ((l = abs(st-sp)+3) > longueur_maximale) {
						longueur_maximale = l; /*on prend le couple start-stop ayant la plus grande longueur*/
						*start = st; /*on modifie les valeurs de start et stop*/
						*stop = sp;
						*longueur = longueur_maximale;
					}
				}
			}
		}
			
	}
}

int codons_start_stop_ORF_max(char* sequence, int taille_seq, int* start, int* stop, int* taille) {
	int start_sens = -1;
	int stop_sens = -1;
	int start_antisens = -1;
	int stop_antisens = -1;
	int longueur_sens = -1;
	int longueur_antisens = -1;
	
	codons_start_stop_brin_sens(sequence, taille_seq, &start_sens, &stop_sens, &longueur_sens);
	codons_start_stop_brin_antisens(sequence, taille_seq, &start_antisens, &stop_antisens, &longueur_antisens);
	
	if (longueur_sens != -1 && longueur_antisens != -1) {
		
		if (longueur_sens >= longueur_antisens) {
			*start = start_sens;
			*stop = stop_sens;
			*taille = longueur_sens;	
			return 2;
		}
		else {
			*start = start_antisens;
			*stop = stop_antisens;
			*taille = longueur_antisens;
			return 1;
		}
	}
	else {
		if (longueur_sens != -1 && longueur_antisens == -1) {
			*start = start_sens;
			*stop = stop_sens;
			*taille = longueur_sens;
			return 2;
		}
		else {
			if (longueur_sens == -1 && longueur_antisens != -1)  {
				*start = start_antisens;
				*stop = stop_antisens;
				*taille = longueur_antisens;
				return 1;
			}
			else { 
				return 0;
			}
		}
	}
}

void creation_sequence_ORF_sens(int taille_seq_codante, char* sequence, int start, int stop, char* seq_cod) {
	int j=0;
	int i;
		for (i=start; i<stop+3; i++) {
			seq_cod[j] = sequence[i];
			j++;
		}
	seq_cod[taille_seq_codante] = '\0';
}

void creation_sequence_ORF_antisens(int taille_seq_codante, char* sequence, int start, int stop, char* seq_cod) {
	int j=taille_seq_codante-1;
	int i;
	for (i=stop-2; i<start+1; i++) {
		seq_cod[j] = sequence[i];
		j--;
	}
	seq_cod[taille_seq_codante] = '\0';
}

void module_recherche_sequence_codante_maximale() {
	int start;
	int stop;
	int taille_seq_codante;
   
    char path_input[30];
    char path_output[30];

    get_path_from_user(path_input);

    int taille_seq = longueur_sequence(path_input);
    char sequence[taille_seq+1];
	extract_sequence(path_input, sequence);
	
	int codante = codons_start_stop_ORF_max(sequence, taille_seq, &start, &stop, &taille_seq_codante); /*renvoie 2 si codant sur brin sens, 1 si codant sur brin antisens, 0 si non codant*/

	char seq_cod[taille_seq_codante+1];
			
	if (codante == 2) {
		creation_sequence_ORF_sens(taille_seq_codante, sequence, start, stop, seq_cod);
        printf("Entrez le nom du fichier de votre séquence codante maximale.\n");
        get_path_from_user(path_output);
		save_sequence(path_output, seq_cod);
	}
	else {
		if (codante == 1) {
			creation_sequence_ORF_antisens(taille_seq_codante, sequence, start, stop, seq_cod);
			printf("Entrez le nom du fichier de votre séquence codante maximale.\n");
            get_path_from_user(path_output);
            save_sequence(path_output, seq_cod);
		}
		else {
			printf("Erreur. La séquence n'est pas codante.");
		}
	}
}
	