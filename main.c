#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"
#include "module_transcription.h"
#include "module_score_identite.h"
#include "module_score_polarite.h"

/* il faut #include tous nos fichiers .h*/


int main() {
	int module_number=0;
    char path_input[30];
    char path_output[30];
    printf("Bonjour et bienvenue dans le logiciel d'analyse de séquences.\n");
	get_module_number_from_user(&module_number); /*on demande à l'utilisateur le module qu'il veut utiliser*/

	switch(module_number)
    {
        case 1: {
            get_path_from_user(path_input); /*on demande à l'utilisateur le fichier de la séquence à étudier*/
            printf("Choisissez le nom de votre fichier pour la séquence transcrite.\n");
            get_path_from_user(path_output);
            module_transcription(path_input, path_output);
            break;
        }
        case 2: {
           	/*instruction*/;
            break;
        }
        case 3: {
            /*instruction*/;
            break;
        }
        case 4: {
            get_path_from_user(path_input); /*on demande à l'utilisateur le fichier de la séquence à étudier*/
            printf("Avec quelle séquence voulez-vous comparer ?\n");
	        char path_input2[30];
	        get_path_from_user(path_input2);
	        module_score_id(path_input, path_input2);
            break;
        }
        case 5: {
            get_path_from_user(path_input); /*on demande à l'utilisateur le fichier de la séquence à étudier*/
            printf("Avec quelle séquence voulez-vous comparer ?\n");
	        char path_input2[30];
	        get_path_from_user(path_input2);
            module_score_pol(path_input, path_input2);
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
            printf("Erreur ! Aucun module ne correspond à votre demande.\nRéessayez.\n\n");
        }
    }
}
