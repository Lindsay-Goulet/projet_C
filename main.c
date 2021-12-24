#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"
#include "module_recherche_sequence_codante_maximale.h"
#include "module_transcription.h"
#include "module_score_identite.h"
#include "module_score_polarite.h"
#include "module_traduction.h"
#include "module_sequence_consensus.h"


//Pour changer l'affichage dans le terminal grâce aux paramètres SGR (ANSI)
//Colorer les lettres
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

//Colorer le fond 
#define BGblack     "\x1b[40m"
#define BGred       "\x1b[41m"
#define BGgreen     "\x1b[42m"
#define BGyellow    "\x1b[43m"
#define BGblue      "\x1b[44m"
#define BGmagent    "\x1b[45m"
#define BGcyan      "\x1b[46m"
#define BGwhite     "\x1b[47m"
#define BGazure     "\x1B[48;2;240;255;255m" //3 dernières lettres = RGB

//Changer le type d'écriture 
#define bright      "\x1b[1m" //Gras
#define underscore  "\x1b[4m" //Souligné
#define blink       "\x1b[5m" //Clignotant
#define reverse     "\x1b[7m" //Fond blanc, écrit en noir

int main() {
    char rep;
    char module_number;
    printf("\n\t\t\t"BGazure bright CYN "Bonjour et bienvenue dans le logiciel d'analyse de séquences." RESET "\n");
    do {
        do {
	        get_module_number_from_user(&module_number); //On demande à l'utilisateur le module qu'il veut utiliser

	        switch(module_number)
            {
                case '1': {
                    module_recherche_sequence_codante_maximale();
                    break;
                }
                case '2': {
                    module_transcription_sequence();
                    break;
                }
                case '3': {
                    module_traduction_sequence();
                    break;
                }
                    case '4': {
	                module_score_id();
                    break;
                }
                case '5': {
                    module_score_pol();
                    break;
                }
                case '6': {
                    module_recherche_sequence_consensus();
                    break;
                }
                case '7': {
                    module_sous_chaine_polarite_maximale();
                    break;
                }
                case 'q' : {
                    printf(bright MAG blink "Fin du programme. Merci à bientôt :)\n" RESET);
                    exit(EXIT_FAILURE);
                }
                //Si aucune des propositions précédentes
                default: {
                    printf(RED "\nErreur ! Aucun module ne correspond à votre demande.\nRéessayez.\n\n" RESET );
                }
            }
        }
        //Pour utiliser un autre module
        while (module_number > '7' || module_number < '1');
        printf("\nVoulez-vous utiliser un autre module ? (o/n)\n");
        scanf("\n%c", &rep);
    }
    while (rep == 'o' );
    if (rep == 'n') {
        printf(bright MAG blink "Fin du programme. Merci à bientôt :)\n" RESET);
    }
}
