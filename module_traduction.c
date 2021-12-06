#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

#define nb_aa 64


int main() {

    char path_input[30];

    int taille_seq = longueur_sequence(path_input);
    char seq_arn[taille_seq];
    extract_sequence(path_input, seq_arn);

    char seq_aa[taille_seq/3];

    int compteur_seq_aa=0;

    for (int i=0; i<taille_seq-2; i++) {
        
        if (tab[i]=="G") {
            if (tab[i+1]=="U") 
                seq_aa[compteur_seq_aa]=="V"; /*GU% = Valine*/
            else if (tab[i+1]=="C")
                seq_aa[compteur_seq_aa]=="A"; /*GC% = Alanine*/
            else if (tab[i+1]=="A"){
                if ((tab[i+2]=="U") || (tab[i+2]=="C"))
                    seq_aa[compteur_seq_aa]=="D"; /*GAU ou GAC = Acide aspartique*/
                else if ((tab[i+2]=="A") || (tab[i+2]=="G"))
                    seq_aa[compteur_seq_aa]=="E"; /*GAA ou GAG = Acide glutamique*/
            }
            else if (tab[i+1]=="G")
                seq_aa[compteur_seq_aa]=="G"; /*GG% = Glycine*/
        }

        if (tab[i]=="U"){
            else if (tab[i+1]=="G"){
                if ((tab[i+2]=="U") || (tab[i+2]=="C"))
                    seq_aa[compteur_seq_aa]=="C"; /*UGU ou UGC = Cystéine*/
                else if (tab[i+2]=="A")
                    seq_aa[compteur_seq_aa]=="*"; /*UGA = STOP*/
                else if (tab[i+2]=="G")
                    seq_aa[compteur_seq_aa]=="W"; /*UGG = Tryptophane*/
            }
            else if (tab[i+1]=="C")
                seq_aa[compteur_seq_aa]=="S"; /*UC% = Sérine*/
            else if (tab[i+1]=="U"){
                if ((tab[i+2]=="U") || (tab[i+2]=="C"))
                    seq_aa[compteur_seq_aa]=="F"; /*UUU ou UUC = Phénylalanine*/
                else if ((tab[i+2]=="A") || (tab[i+2]=="G"))
                    seq_aa[compteur_seq_aa]=="L"; /*UUA ou UUG = Leucine*/
            }
            else if (tab[i+1]=="A"){
                if ((tab[i+2]=="U") || (tab[i+2]=="C"))
                    seq_aa[compteur_seq_aa]=="Y"; /*UAU ou UAC = Tyrosine*/
                else if ((tab[i+2]=="A") || (tab[i+2]=="G"))
                    seq_aa[compteur_seq_aa]=="*"; /*UAA ou UAG = STOP*/
            } 
        }

        if (tab[i]=="C"){
            if (tab[i+1]=="U") 
                seq_aa[compteur_seq_aa]=="L"; /*CU% = Leucine*/
            else if (tab[i+1]=="C")
                seq_aa[compteur_seq_aa]=="P"; /*CC% = Proline*/
            else if (tab[i+1]=="A"){
                if ((tab[i+2]=="U") || (tab[i+2]=="C"))
                    seq_aa[compteur_seq_aa]=="H"; /*CAU ou CAC = Histidine*/
                else if ((tab[i+2]=="A") || (tab[i+2]=="G"))
                    seq_aa[compteur_seq_aa]=="Q"; /*CAA ou CAG = Glutamine*/
            }
            else if (tab[i+1]=="G")
                seq_aa[compteur_seq_aa]=="R"; /*CG% = Arginine*/
        }

        if (tab[i]=="A"){
            if (tab[i+1]=="U"){
                if ((tab[i+2]=="U") || (tab[i+2]=="C") || (tab[i+2]=="A"))
                    seq_aa[compteur_seq_aa]=="I"; /*AUU ou AUC ou AUA = Isoleucine*/
                else if (tab[i+2]=="G")
                    seq_aa[compteur_seq_aa]=="M"; /*AUG = Méthionine*/
            }
            else if (tab[i+1]=="C")
                seq_aa[compteur_seq_aa]=="T"; /*AC% = Thréonine*/
            else if (tab[i+1]=="A"){
                if ((tab[i+2]=="U") || (tab[i+2]=="C"))
                    seq_aa[compteur_seq_aa]=="D"; /*AAU ou AAC = Acide aspartique*/
                else if ((tab[i+2]=="A") || (tab[i+2]=="G"))
                    seq_aa[compteur_seq_aa]=="K"; /*AAA ou AAG = Lysine*/
            }
            else if (tab[i+1]=="G"){
                if ((tab[i+2]=="U") || (tab[i+2]=="C"))
                    seq_aa[compteur_seq_aa]=="S"; /*AGU ou AGC = Sérine*/
                else if ((tab[i+2]=="A") || (tab[i+2]=="G"))
                    seq_aa[compteur_seq_aa]=="R"; /*AAA ou AAG = Arginine*/
            }
        }
    compteur_seq_aa++;
    }

}