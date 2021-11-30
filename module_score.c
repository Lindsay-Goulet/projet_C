#include <stdio.h>
#include <stdlib.h>

int longueur_seq(char* fic) {
	int taille_seq=0;
	int el;

	FILE* f = fopen(fic, "r"); /* ouverture du fichier*/
	if (!f) {
		printf("L'ouverture a echoué.\n");
		exit(EXIT_FAILURE);
	}
	
	while (fscanf(f, "%lc", &el) != EOF) { /*je parcours tout le fichier et je compte les éléments*/
		taille_seq++;
	}
	
	return taille_seq-1; 
}

double pourct_id(double ls, int nb_id) {
	double id = nb_id*100/ls; /*produit en croix pour calculer le pourcentage*/
	return id;
}

void lire_seq(char* fic, int ls, char seq[ls]) {
	FILE* f = fopen(fic, "r"); /* ouverture du fichier*/
		if (!f) {
			printf("L'ouverture a echoué.\n");
			exit(EXIT_FAILURE);
		}
	fgets(seq, ls+1, f); /*je récupère dans le fichier f une chaîne de caractère de longueur ls que je stock dans mon tableau seq*/
}

int nb_id(int ls, char seq1[ls], char seq2[ls]) {
	int i;
	int nb_ide=0;
	for (i=0; i<ls; i++) { 
		if (seq1[i] == seq2[i]) { /*je parcours mes séq et je compte le nb de différence entre les deux */
			nb_ide++;
		}
	}
	return nb_ide;
}

void seq_id(int ls, char seq1[ls], char seq2[ls], char id[ls]) {
	int i;
	for (i=0; i<ls; i++) {
		if (seq1[i] == seq2[i]) { /*ça c'est pour écrire les séq dans le terminal. Je créé ma seq "id" donc je mets le nucléo quand il est identique et sinon je mets un - */
			id[i] = seq1[i];
		}
		else {
			id[i] = '-';
		}
	}
}

void module_score_id(char* argv[]) {
	int i;
	
	int ls = longueur_seq(argv[1]); /*je recupère la longueur de la seq*/
	char seq1[ls];
	lire_seq(argv[1], ls, seq1); /* je stocke mes 2 seq dans 2 tableaux*/
	char seq2[ls];
	lire_seq(argv[2], ls, seq2);
	
	int ide = nb_id(ls, seq1, seq2); /* je compte les diff*/
	double score = pourct_id(ls, ide); /*conversion en %*/
	char id[ls];
	seq_id(ls, seq1, seq2, id); /* création de la seq id pour l'affichage*/
	printf("Identité de séquence: %d/%d, soit %.2f %%.\n", ide, ls, score);
	printf("seq1\t");
	for (i=0; i<ls; i++) { printf("%c", seq1[i]); } printf("\n"); /*affichage des seq*/
	printf("seq2\t");
	for (i=0; i<ls; i++) { printf("%c", seq2[i]); } printf("\n");
	printf("id\t");
	for (i=0; i<ls; i++) { printf("%c", id[i]); } printf("\n");
}
	

int main(int argc , char * argv[]) {
	module_score_id(argv);
	
}	
