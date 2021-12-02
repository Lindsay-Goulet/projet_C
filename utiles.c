#include <stdio.h>
#include <stdlib.h>

void get_path_from_user(char* path_input) {
	printf("Saisissez le nom de votre fichier FASTA");
	scanf("%40s", path_input);
}

void extract_sequence(const char* path_input, char* sequence) {
/* ajouter procédure qui supp ligne inutile */
	char ligne[81];
    FILE* f = fopen(path_input, "r"); /* ouverture du fichier*/
	    	if (!f) {
		    	printf("L'ouverture a echoué.\n");
			    exit(EXIT_FAILURE);
		    }
    while (fgets(ligne, 81, f) != NULL)  {
    	printf("%s", ligne );
        /* comment stocker dans variable ?*/
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

