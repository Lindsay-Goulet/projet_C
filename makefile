
CC = gcc
CFLAGS = -Wall

all : log_analyse_seq 

log_analyse_seq : utiles.o module_transcription.o module_traduction.o module_score_polarite.o module_score_identite.o module_recherche_sequence_codante_maximale.o module_sequence_consensus.o main.o
	$(CC) utiles.o module_transcription.o module_traduction.o module_score_polarite.o module_score_identite.o module_recherche_sequence_codante_maximale.o module_sequence_consensus.o main.o -o log_analyse_seq

utiles.o : utiles.c 
	$(CC) -c utiles.c $(CFLAGS)

module_transcription.o : module_transcription.c utiles.h
	$(CC) -c module_transcription.c $(CFLAGS)

module_traduction.o : module_traduction.c utiles.h
	$(CC) -c module_traduction.c $(CFLAGS)

module_score_polarite.o : module_score_polarite.c utiles.h
	$(CC) -c module_score_polarite.c $(CFLAGS)

module_score_identite.o : module_score_identite.c utiles.h
	$(CC) -c module_score_identite.c $(CFLAGS)

module_recherche_sequence_codante_maximale.o : module_recherche_sequence_codante_maximale.c utiles.h
	$(CC) -c module_recherche_sequence_codante_maximale.c $(CFLAGS)

module_sequence_consensus.o : module_sequence_consensus.c utiles.h
	$(CC) -c module_sequence_consensus.c $(CFLAGS)

main.o : main.c utiles.h module_transcription.h module_traduction.h module_score_polarite.h module_score_identite.h module_recherche_sequence_codante_maximale.h module_sequence_consensus.h
	$(CC) -c main.c $(CFLAGS)

clean :
	rm -f *.o 

mrproper : clean
	rm -f log_analyse_seq 