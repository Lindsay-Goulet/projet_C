#include <stdio.h>
#include <stdlib.h>

#define underscore  "\x1b[4m" /*Souligné*/
#define blink       "\x1b[5m" /*Clignotant*/
#define CYN   "\x1B[36m"
#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define bright      "\x1b[1m" 
#define BLU   "\x1B[34m"

/*
module_sequence_consensus.o : module_sequence_consensus.c utiles.h
	$(CC) -c module_sequence_consensus.c $(CFLAGS)

module_recherche_sous_chaine_polarite.o : module_recherche_sous_chaine_polarite.c utiles.h
	$(CC) -c module_sous_chaine_polarite.c $(CFLAGS)

*/

void get_path_from_user(char* path_input) {
/*Procédure qui permet à l'utilisateur d'entrer le fichier*/
	printf("Saisissez le nom de votre fichier FASTA : ");
	scanf("%40s", path_input);
}

void get_module_number_from_user(char* module_number) {
	    printf("\nQuel module voulez-vous utiliser ?\n1. Recherche de la séquence codante de taille maximale.\n2. Transcription d’une séquence ADN en séquence ARN.\n3. Traduction d’une séquence codante en séquence protéique.\n4. Calcul du score d’identité entre deux séquences.\n5. Calcul du score de similarité de polarité entre deux séquences protéiques.\n6. Recherche d’une séquence consensus à partir d’un alignement multiple.\n7. Recherche de la plus grande sous-chaîne de polarité commune à 2 séquences protéiques.\nq : Quitter.\nModule : ");
        scanf("\n%c", module_number);
}

void extract_sequence(const char* path_input, char* sequence) {
/*Procédure qui extrait la séquence du fichier pour la mettre dans un tableau séquence*/
/*ajouter une procédure qui supp ligne inutile */
	char ligne[81];
	int i=0;
	int j;
    FILE* f = fopen(path_input, "r"); /* ouverture du fichier*/
	    	if (!f) {
		    	printf(RED "L'ouverture a échoué.\n" RESET);
			    exit(EXIT_FAILURE);
		    }
    while (fgets(ligne, 81, f))  {
    	j=0;
    	while (ligne[j] != '\n' && ligne[j] != '\0') {
			sequence[i] = ligne[j];			
			i++;
			j++;
		}
	sequence[i] = '\0';
   }
   fclose(f);
}

void save_sequence(const char* path_output, char* sequence) {
/*Procédure enregistre une séquence dans un nouveau fichier*/
    int i=0;

    FILE* f = fopen(path_output, "w"); /* ouverture du fichier*/
		if (!f) {
			printf(RED "L'ouverture a échoué.\n" RESET);
			exit(EXIT_FAILURE);
		}
	while (sequence[i] != '\0') { /*on parcourt toute la séquence stockée dans la variable séquence*/
        	fputc(sequence[i], f);
        	i++;
        	if ((i+1)%80 == 0) { /*quand on arrive au 80e caractère, on passe à la ligne*/
            		fprintf(f, "\n");
        	}
    }
	fclose(f);
}

int longueur_sequence(const char* path_input) {
    /*ajouter procédure qui supprime la ligne avant la sequence*/
    int taille_seq=0;
	int c;

    FILE* f = fopen(path_input, "r"); /* ouverture du fichier*/
	if (!f) {
		printf(RED "L'ouverture a échoué.\n" RESET);
		exit(EXIT_FAILURE);
	}

	while (fscanf(f, "%lc", &c) != EOF) { /*je parcours tout le fichier et je compte les éléments*/
		if (c != '\n' && c!= '\0') {
			taille_seq++;
		}
	}
	
	fclose(f);
	return taille_seq; 
}

int polarite(char aa) {
	if ((aa == 'C') || (aa == 'Y') || (aa == 'T') || (aa == 'S') || (aa == 'N') || (aa == 'Q') || (aa == 'H') || (aa == 'K') || (aa == 'R') || (aa == 'D') || (aa == 'E')) {
		return 0; /*retourne pol*/
	}
	else 
		return 1; /*retourne apol */
}

double pourct_id(double taille_seq, int nb_id) {
	double id = nb_id*100/taille_seq; /*produit en croix pour calculer le pourcentage*/
	return id;
}

int verification_sequence(char* path_input, char* sequence, int taille_seq) {
    extract_sequence(path_input, sequence);

    if ((sequence[0] == 'A') && ((sequence[1] == 'T') || (sequence[1] == 'U')) && (sequence[2] == 'G') 
	&& (taille_seq%3 == 0) 
	&& ((sequence[taille_seq-3] == 'T' && sequence[taille_seq-2] == 'G' && sequence[taille_seq-1] == 'A') 
	|| (sequence[taille_seq-3] == 'T' && sequence[taille_seq-2] == 'A' && sequence[taille_seq-1] == 'A') 
	|| (sequence[taille_seq-3] == 'T' && sequence[taille_seq-2] == 'A' && sequence[taille_seq-1] == 'G'))) {
        return 1;
/*ne pas oublier les U*/
    }

    else { 
        return 0;
    }
}



