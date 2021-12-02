#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
=======
/*je teste les modifications*/
>>>>>>> 3ab869db60a8af5d4b74d649aaaa3c8f364a5fb3

int longueur_seq(char* fic) {
	int taille_seq=0;
	int el;

	FILE* f = fopen(fic, "r"); /* ouverture du fichier*/
	if (!f) {
		printf("L'ouverture a échoué.\n");
		exit(EXIT_FAILURE);
	}
	
	while (fscanf(f, "%lc", &el) != EOF) { /*je parcours tout le fichier et je compte les éléments*/
		taille_seq++;
	}
	
	return taille_seq-1;
}

void lire_seq(char* fic, int ls, char seq[ls]) {
	FILE* f = fopen(fic, "r"); /* ouverture du fichier*/
		if (!f) {
			printf("L'ouverture a echoué.\n");
			exit(EXIT_FAILURE);
		}
	fgets(seq, ls+1, f); /*je récupère dans le fichier f une chaîne de caractère de longueur ls que je stock dans mon tableau seq*/
}

<<<<<<< HEAD
int seq_codante(char argv[], int ls, char codon1[3]) {
=======
int seq_codante(char* argv, int ls, char* seq[ls], char* codon1[3]) {
>>>>>>> 3ab869db60a8af5d4b74d649aaaa3c8f364a5fb3
/*A optimiser quand fichier fait*/
/*Fonction qui retourne 1 si la séquence ADN est codante (longueur divisible par 3 et a un codon d'initiation)*/
	lire_seq(argv, 3, codon1); /*Je récupère les trois premiers nucléotides = premier codon de la séquence*/
	
	int booleen=0; /*Initie un booléen*/
	if (ls%3==0 && strcmp(codon1, "ATG") == 0){ /*Vérifie si séquence codante et si oui bool=1*/
		booleen=1;
	}
	return booleen; /*Retourne le booléen*/
}


void module_transcrit(char* argv[]) {
/*Procédure qui transcrit le brin d'ADN en ARN si le brin est un brin codant*/
/*NE PAS OUBLIER : Redemander à l'utilisateur une séquence si elle est non codante*/
	
	int ls = longueur_seq(argv[1]); /*Initie la longueur de la chaîne*/
	char atranscrire[ls]; 
	lire_seq(argv, ls, atranscrire); /*Récupère la séquence en entier*/

	int codante = seq_codante(argv, ls, atranscrire[ls], codon1[3]);
	if (codante == 0) 
		printf("Cette séquence n'est pas codante, vous ne pouvez donc pas utiliser ce module, essayez avec une autre séquence ou utilisez un autre module.");
	
	printf(atranscrire); /*juste pour vérifier que tout va bien quand ça marchera*/ 
	/*Mettre ici suppression d'un fichier transcrit existant = cleaner env travail ou renommer*/
	
	FILE * fp = fopen ("transcrit.txt", "a"); /*Ouverture d'un fichier transcrit.txt pour écrire dedans*/
	if (!fp) {
		printf ("L’ouverture a échoué.\n") ;
		exit ( EXIT_FAILURE );	
	}
	
	for (int i=0; i<ls; i++){ 
	 	if (strcmp(atranscrire[i], "T") == 0) /*Quand T -> U*/
	 		fprintf(fp, "U");
	 	else 
	 		fprintf(fp, atranscrire[i]); /*Quand autre, juste mettre le nucléotide*/
	 	if (i%80==0) /*Pour respecter le format fasta*/
	 		fprintf(fp, "\n");
	}
	fclose(fp); /*Fermeture du fichier*/
}



int main(int argc, char * argv[]) {
	module_transcrit(argv);
}	






