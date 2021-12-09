#ifndef module_sequence_consensus
#define module_sequence_consensus


int longueur_seq(const char* path_input);

int nombre_sequences(const char* path_input);

void extract_sequences(const char* path_input, int long_seq, int nb_seq, char sequences[nb_seq][long_seq]);

int pourcentage(int nb_seq, double nb_nucleo);

void seq_consensus_par_position(char* seq_consensus, int position, int nb_seq, int nbA, int nbT, int nbG, int nbC);

void sequence_consensus(int long_seq, int nb_seq, char sequences[nb_seq][long_seq], char* seq_consensus);

void module_recherche_sequence_consensus();


#endif