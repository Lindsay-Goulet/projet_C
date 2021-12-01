#include <stdio.h>
#include <stdlib.h>

#include "module_score.c"

int seq_codante(char* argv[]) {
/*A optimiser quand fichier fait*/
/*Fonction qui retourne 1 si la séquence ADN est codante (longueur divisible par 3 et a un codon d'initiation)*/
	int ls = longueur_seq(argv[1]); /*Initie la longueur de la chaîne*/
	char codon1[3]; 
	lire_seq(argv, 3, codon1); /**/
	
	int booleen=0;
	if (ls%3==0 && codon1=='ATG'){ 
		booleen=1;
	}
	return booleen;
}


void module_transcrit(char** argv[]) {

/*Redemander à l'utilisateur une séquence si elle est non codante*/
	int ls = longueur_seq(argv); /*i!!!!!!nitie la longueur de la chaîne*/
	char atranscrire[ls];
	lire_seq(argv, ls, atranscrire);
	
	printf(atranscrire);
	/*Mettre ici suppression d'un fichier transcrit existant*/
	
	FILE * fp = fopen ("transcrit.txt", "a"); /*Regarder pour trouver u moyer de changer le nom du fichier ou cleaner env travail*/
	if (!fp) {
		printf ("L’ouverture a échoué.\n") ;
		exit ( EXIT_FAILURE );	
	}
	
	for (int i=0; i<ls; i++){
	 	if (atranscrire[i]=="T")
	 		fprintf(fp, "U");
	 	else 
	 		fprintf(fp, atranscrire[i]);
	 	if (i%80==0)
	 		fprintf(fp, "\n");
	}
	fclose(fp);
}



int main(int argc, char * argv[]) {
	module_transcrit(argv);
}	






