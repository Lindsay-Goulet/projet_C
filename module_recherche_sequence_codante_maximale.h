#ifndef module_sequence_codante_maximale
#define module_sequence_codante_maximale

void codons_start_stop_brin_sens(char* sequence, int taille_seq, int* start, int* stop, int* longueur);

void codons_start_stop_brin_antisens(char* sequence, int taille_seq, int* start, int* stop, int* longueur);

int codons_start_stop_ORF_max(char* sequence, int taille_seq, int* start, int* stop, int* taille);

void creation_sequence_ORF_sens(int taille_seq_codante, char* sequence, int start, int stop, char* seq_cod);

void creation_sequence_ORF_antisens(int taille_seq_codante, char* sequence, int start, int stop, char* seq_cod)

void module_recherche_sequence_codante_maximale();

#endif
