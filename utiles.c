#include <stdio.h>
#include <stdlib.h>

void get_path_from_user(char* path_input) {
	printf("Saisissez le nom de votre fichier FASTA.");
	scanf("%40s", path_input);
}

void get_module_number_from_user(int* module_number) {
	while (numero_module > 7 || numero_module < 1) {
        printf("Quel module voulez-vous utiliser ?\n1. Recherche de la séquence codante de taille maximale.\n2. Transcription d’une séquence ADN en séquence ARN.\n3. Traduction d’une séquence codante en séquence protéique.\n4. Calcul du score d’identité entre deux séquences.\n5. Calcul du score de similarité de polarité entre deux séquences protéiques.\n6. Recherche d’une séquence consensus à partir d’un alignement multiple.\n7. Recherche de la plus grande sous-chaîne de polarité commune à 2 séquences protéiques.\n");
        scanf("%d", module_number);
}

void extract_sequence(const char* path_input, char* sequence) {
/* ajouter procédure qui supp ligne inutile */
	char ligne[82];
	int i=0;
	int j;
    FILE* f = fopen(path_input, "r"); /* ouverture du fichier*/
	    	if (!f) {
		    	printf("L'ouverture a echoué.\n");
			    exit(EXIT_FAILURE);
		    }
    while (fgets(ligne, 81, f))  {
    	j=0;
    	while (ligne[j] != '\0' && ligne[j] != '\n') {
    		printf("%c", ligne[j]);
		sequence[i] = ligne[j];			
		i++;
		j++;
		}
	
   }
}

void save_sequence(const char* path_output, char* sequence) {
    int i=0;

    FILE* f = fopen(path_output, "w"); /* ouverture du fichier*/
		if (!f) {
			printf("L'ouverture a echoué.\n");
			exit(EXIT_FAILURE);
		}
	while (sequence[i] != '\0') { /*on parcourt toute la séquence stockée dans la variable séquence*/
        	fputc(sequence[i], f);
        	i++;
        	if (i%80 == 0) { /*quand on arrive au 80e caractère, on passe à la ligne*/
            		fprintf(f, "\n");
        }
    }
}

