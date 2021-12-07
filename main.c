#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"
#include "module_recherche_sequence_codante_maximale.h"
#include "module_transcription.h"
#include "module_score_identite.h"
#include "module_score_polarite.h"
#include "module_traduction.h"

/* il faut #include tous nos fichiers .h*/

int main() {
    char rep;
    int module_number;
    printf("Bonjour et bienvenue dans le logiciel d'analyse de séquences.\n");
    do {
        do {
	        get_module_number_from_user(&module_number); /*on demande à l'utilisateur le module qu'il veut utiliser*/

	        switch(module_number)
            {
                case 1: {
                    module_recherche_sequence_codante_maximale();
                    break;
                }
                case 2: {
                    module_transcription_sequence();
                    break;
                }
                case 3: {
                    module_traduction_sequence();
                    break;
                }
                    case 4: {
	                module_score_id();
                    break;
                }
                case 5: {
                    module_score_pol();
                    break;
                }
                case 6: {
                    /*instruction*/;
                    break;
                }
                case 7: {
                    /*instruction*/;
                    break;
                }
                /* si aucun des 7 */
                default: {
                    printf("\nErreur ! Aucun module ne correspond à votre demande.\nRéessayez.\n\n");
                }
            }
        }
        while (module_number > 7 || module_number < 1);
        printf("\nVoulez-vous utiliser un autre module ? (o/n)\n");
        scanf("\n%c", &rep);
    }
    while (rep == 'o' );
    if (rep == 'n') {
        printf("Fin du programme.\n");
    }
}
