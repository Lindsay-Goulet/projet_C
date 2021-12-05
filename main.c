#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

/* il fait #include tous nos fichiers .h*/


int main() {
	int module_number=0;
    char path_input[30];
    printf("Bonjour et bienvenue dans le logiciel d'analyse de séquences.");
    get_path_from_user(path_input); /*on demande à l'utilisateur la séquence à étudier*/
	get_module_number_from_user(module_number); /*on demande à l'utilisateur le module qu'il veut utiliser*/
	
	    switch(numero_module)
        {
            case 1:
                /*instruction*/;
                break;

            case 2:
           	    /*instruction*/;
                break;

            case 3:
                /*instruction*/;
                break;

            case 4:
                /*instruction*/;
                break;
            
            case 5:
                /*instruction*/;
                break;
            
            case 6:
                /*instruction*/;
                break;
            
            case 7:
                /*instruction*/;
                break;

            /* si aucun des 7 */
            default:
                printf("Erreur ! Aucun module ne correspond à votre demande.\nRéessayez.\n\n");
        }
    }
}