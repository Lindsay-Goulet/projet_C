#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

/* il fait #include tous nos fichiers .h*/


int main() {
	int numero_module=0;
	while (numero_module > 7 || numero_module < 1) {
	
        printf("Bonjour et bienvenue dans le logiciel d'analyse de séquences.\nQuel module voulez-vous utiliser ?\n1. Recherche de la séquence codante de taille maximale.\n2. Transcription d’une séquence ADN en séquence ARN.\n3. Traduction d’une séquence codante en séquence protéique.\n4. Calcul du score d’identité entre deux séquences.\n5. Calcul du score de similarité de polarité entre deux séquences protéiques.\n6. Recherche d’une séquence consensus à partir d’un alignement multiple.\n7. Recherche de la plus grande sous-chaîne de polarité commune à 2 séquences protéiques.\n");
        scanf("%d", &numero_module);
	
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