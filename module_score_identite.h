#ifndef module_score_identite
#define module_score_identite

double pourct_id(double taille_seq, int nb_id);

int nb_nucleotide_ident(char* sequence1, char* sequence2, int taille_seq);

int longueur_sequence(const char* path_input);

void seq_id(int taille_seq, char* seq1, char* seq2, char* id);

void module_score_id(const char* path_input, const char* path_input2);


#endif