#include <stdio.h>
#include <stdlib.h>

#define APOLAIRE 1
#define POLAIRE 0

typedef enum Polarite {
polaire, apolaire
} Polarite;

typedef struct AcideAmine {
	char nom ;
	int polarite ;
} AA;

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

double pourct_id(double ls, int nb_ide) {
	double id = nb_ide*100/ls; /*produit en croix pour calculer le pourcentage*/
	return id;
}

int polarite(char aa) {
	if ((aa == 'C') || (aa == 'Y') || (aa == 'T') || (aa == 'S') || (aa == 'N') || (aa == 'Q') || (aa == 'H') || (aa == 'K') || (aa == 'R') || (aa == 'D') || (aa == 'E')) {
		return 0; /*retourne pol*/
	}
	else 
		return 1; /*retourne apol */
}

void lire_seq_prot(char* fic, int ls, AA seq[ls]) {
	int i=0;
	int el;
	FILE* f = fopen(fic, "r"); /* ouverture du fichier*/
		if (!f) {
			printf("L'ouverture a echoué.\n");
			exit(EXIT_FAILURE);
		}
	while (fscanf(f , "%lc", &el) != EOF) {
		seq[i].nom = el;
		if (seq[i].nom != '-') {
			seq[i].polarite = polarite(seq[i].nom);
		}
		else {
			seq[i].polarite = -9;
		}
		i++;
	}
}

int nb_id(int ls, AA seq1[ls], AA seq2[ls]) {
	int i;
	int nb_ide=0;
	for (i=0; i<ls; i++) { 
		if (seq1[i].polarite != -9) { /*si l'aa n'est pas "-"*/
			if (seq1[i].polarite == seq2[i].polarite) { /*je parcours mes séq et je compte le nb de différence entre les deux */
				nb_ide++;
			}
		}
	}
	return nb_ide;
}

void seq_id(int ls, AA seq1[ls], AA seq2[ls], char id[ls]) {
	int i;
	for (i=0; i<ls; i++) {
		if (seq1[i].polarite == seq2[i].polarite){
			char charValue=seq1[i].polarite+'0';
			id[i] = charValue;
		}
		else {
			id[i] = '-';
		}
	}
}

void module_score_pol(char* argv[]) {
	int i;
	
	int ls = longueur_seq(argv[1]); /*je recupère la longueur de la seq*/
	AA seq1[ls];
	lire_seq_prot(argv[1], ls, seq1);
	AA seq2[ls];
	lire_seq_prot(argv[2], ls, seq2);
	
	int ide = nb_id(ls, seq1, seq2); /* je compte les diff*/
	double score = pourct_id(ls, ide); /*conversion en %*/
	char id[ls];
	seq_id(ls, seq1, seq2, id); /* création de la seq id pour l'affichage*/
	printf("Similarité de polarité: %d/%d, soit %.2f %%.\n", ide, ls, score);
	printf("0 : hydrophiles, 1 : hydrophobes, - : différents\n");
	printf("seq1\t");
	for (i=0; i<ls; i++) { printf("%c", seq1[i].nom); } printf("\n"); /*affichage des seq*/
	printf("seq2\t");
	for (i=0; i<ls; i++) { printf("%c", seq2[i].nom); } printf("\n");
	printf("id\t");
	for (i=0; i<ls; i++) { printf("%c", id[i]); } printf("\n");
}

int main(int argc , char * argv[]) {
	module_score_pol(argv);
}
