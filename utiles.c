#include <stdio.h>
#include <stdlib.h>

#define max(a,b) (a>=b?a:b)

//Permet de mettre de changer l'affichage dans le terminal :
#define underscore  "\x1b[4m" /*Souligné*/
#define blink       "\x1b[5m" /*Clignotant*/
#define CYN   "\x1B[36m"
#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define bright      "\x1b[1m" 
#define BLU   "\x1B[34m"


void get_path_from_user(char* path_input) {
	//Procédure qui permet à l'utilisateur d'entrer le fichier qu'il veut que le logiciel analyse
	
	printf(CYN "Saisissez le nom de votre fichier : " RESET);
	scanf("%40s", path_input);
}

void get_module_number_from_user(char* module_number) {
	//Procédure qui permet à l'utilisateur de choisir le module qu'il veut utiliser ou s'il veut quitter le logiciel
	//Et qui permet aussi l'affichage dans le terminal des différents choix qui s'offre à l'utilisateur
	
	printf(CYN underscore "\nQuel module voulez-vous utiliser ?"RESET"\n1. Recherche de la séquence codante de taille maximale.\n2. Transcription d’une séquence ADN en séquence ARN.\n3. Traduction d’une séquence codante en séquence protéique.\n4. Calcul du score d’identité entre deux séquences.\n5. Calcul du score de similarité de polarité entre deux séquences protéiques.\n6. Recherche d’une séquence consensus à partir d’un alignement multiple.\n7. Recherche de la plus grande sous-chaîne de polarité commune à 2 séquences protéiques.\nq : Quitter.\n"BLU blink bright"Module : "RESET);
    scanf("\n%c", module_number);
}

void supp_premiere_ligne(const char* path_input) {
	//Procédure qui supprime la ligne d'information du fichier FASTA (commence par >) 
	int caractere_ligne=0;
	
	FILE* f = fopen(path_input, "r"); //Ouverture du fichier de l'utilisateur
		if (!f) {
			printf(RED "L'ouverture a échoué.\n" RESET);
			
			exit(EXIT_FAILURE);
		}

	while (fgetc(f) != '\n') caractere_ligne++;
	rewind(f); //Permet de revenir au début du fichier pour ensuite supprimer la ligne d'information
	int taille_ligne = max(caractere_ligne, 80);
	char ligne[taille_ligne+1];
		
	FILE* f2 = fopen("fichier_temporaire.fa", "w"); //Ouverture du fichier temporaire 
		if (!f2) {
			printf(RED "L'ouverture a échoué.\n" RESET);
			exit(EXIT_FAILURE);
		}
		
	while (fgets(ligne, taille_ligne+1, f)) {
		if (ligne[0] != '>') {
			fputs(ligne, f2);
		}
	}
			
	fclose(f);
	fclose(f2);
	
	remove(path_input);
	rename("fichier_temporaire.fa", path_input);	
}

void extract_sequence(const char* path_input, char* sequence) {
//Procédure qui extrait la séquence du fichier pour la mettre dans un tableau séquence

	supp_premiere_ligne(path_input);

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
//Procédure enregistre une séquence dans un nouveau fichier au format FASTA
    int i=0;

    FILE* f = fopen(path_output, "w"); /* ouverture du fichier*/
		if (!f) {
			printf(RED "L'ouverture a échoué.\n" RESET);
			exit(EXIT_FAILURE);
		}
	while (sequence[i] != '\0') { //On parcourt toute la séquence stockée dans la variable séquence
        	fputc(sequence[i], f);
        	i++;
        	if (i%80 == 0) { //Quand on arrive au 80e caractère, on passe à la ligne pour respecter le format FASTA
            		fprintf(f, "\n");
        	}
    }
	fclose(f);
}

int longueur_sequence(const char* path_input) {
    //Fonction qui renvoie la longueur de la séquence
    int taille_seq=0;
	int c;

    FILE* f = fopen(path_input, "r"); //Ouverture du fichier
	if (!f) {
		printf(RED "L'ouverture a échoué.\n" RESET);
		exit(EXIT_FAILURE);
	}

	while (fscanf(f, "%lc", &c) != EOF) { //Parcours tout le fichier et compte les éléments
		if (c != '\n' && c!= '\0') {
			taille_seq++;
		}
	}
	
	fclose(f);
	return taille_seq; 
}

int polarite(char aa) {
	//Fonction qui retourne 0 si l'acide aminé est polaire et 1 sinon.
	if ((aa == 'C') || (aa == 'Y') || (aa == 'T') || (aa == 'S') || (aa == 'N') || (aa == 'Q') || (aa == 'H') || (aa == 'K') || (aa == 'R') || (aa == 'D') || (aa == 'E')) {
		return 0; //aa polaire
	}
	else 
		return 1; /*aa apolaire */
}

int verification_sequence(char* path_input, char* sequence, int taille_seq) {
	//Fonction qui renvoie 1 si la séquence est codante et 0 sinon.
    extract_sequence(path_input, sequence);

    if ((sequence[0] == 'A') && ((sequence[1] == 'T') || (sequence[1] == 'U')) && (sequence[2] == 'G') 
	&& (((sequence[taille_seq-3] == 'T' || sequence[taille_seq-3] == 'U') && sequence[taille_seq-2] == 'G' && sequence[taille_seq-1] == 'A') 
	|| ((sequence[taille_seq-3] == 'T' || sequence[taille_seq-3] == 'U') && sequence[taille_seq-2] == 'A' && sequence[taille_seq-1] == 'A') 
	|| ((sequence[taille_seq-3] == 'T' || sequence[taille_seq-3] == 'U') && sequence[taille_seq-2] == 'A' && sequence[taille_seq-1] == 'G'))
	&& (taille_seq%3 == 0)) {
        return 1; //codante

    }

    else { 
        return 0; //Non codante
    }
}



