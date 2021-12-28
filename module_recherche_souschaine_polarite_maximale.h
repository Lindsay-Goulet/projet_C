#ifndef module_recherche_souschaine_polarite_maximale
#define module_recherche_souschaine_polarite_maximale

void matrice_alignement(char* sequence1, char* sequence2, int taille_seq1, int taille_seq2, char mat_alignement[taille_seq2+2][taille_seq1+2]);

void trouver_souschaine_maximale(int taille_seq1, int taille_seq2, char mat_alignement[taille_seq2+2][taille_seq1+2], int* taille_souschaine, int* debut_souschaine);

void conversion_3_lettres(char aa, char* code_3lettres);

void creation_sous_chaine(char* sequence1, char* sous_chaine_1lettre, char* sous_chaine_polarite, char* sous_chaine_3lettres, int taille_souschaine, int debut_souschaine);

void save_output(int taille_sous_chaine, char* sequence1, char* sequence2, char* sous_chaine1_lettre, char* sous_chaine_polarite, char* sous_chaine_3lettres);

void module_sous_chaine_polarite_maximale();

#endif

