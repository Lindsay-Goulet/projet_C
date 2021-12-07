#include <stdio.h>
#include <stdlib.h>
#include "utiles.h"

void traduction(int taille_seq, char* seq_arn, char* seq_aa){
/*Procédure qui permet de traduire une séquence d'ARN*/
    int compteur_seq_aa=0;
    
    for (int i=0; i<taille_seq-2; i++) {
        
        if (seq_arn[i]=='G') {
            if (seq_arn[i+1]=='U') 
                seq_aa[compteur_seq_aa]=='V'; /*GU% = Valine*/
            else if (seq_arn[i+1]=='C')
                seq_aa[compteur_seq_aa]=='A'; /*GC% = Alanine*/
            else if (seq_arn[i+1]=='A'){
                if ((seq_arn[i+2]=='U') || (seq_arn[i+2]=='C'))
                    seq_aa[compteur_seq_aa]=='D'; /*GAU ou GAC = Acide aspartique*/
                else if ((seq_arn[i+2]=='A') || (seq_arn[i+2]=='G'))
                    seq_aa[compteur_seq_aa]=='E'; /*GAA ou GAG = Acide glutamique*/
            }
            else if (seq_arn[i+1]=='G')
                seq_aa[compteur_seq_aa]=='G'; /*GG% = Glycine*/
        }

        if (seq_arn[i]=='U'){
            if (seq_arn[i+1]=='G'){
                if ((seq_arn[i+2]=='U') || (seq_arn[i+2]=='C'))
                    seq_aa[compteur_seq_aa]=='C'; /*UGU ou UGC = Cystéine*/
                else if (seq_arn[i+2]=='A')
                    seq_aa[compteur_seq_aa]=='*'; /*UGA = STOP*/
                else if (seq_arn[i+2]=='G')
                    seq_aa[compteur_seq_aa]=='W'; /*UGG = Tryptophane*/
            }
            else if (seq_arn[i+1]=='C')
                seq_aa[compteur_seq_aa]=='S'; /*UC% = Sérine*/
            else if (seq_arn[i+1]=='U'){
                if ((seq_arn[i+2]=='U') || (seq_arn[i+2]=='C'))
                    seq_aa[compteur_seq_aa]=='F'; /*UUU ou UUC = Phénylalanine*/
                else if ((seq_arn[i+2]=='A') || (seq_arn[i+2]=='G'))
                    seq_aa[compteur_seq_aa]=='L'; /*UUA ou UUG = Leucine*/
            }
            else if (seq_arn[i+1]=='A'){
                if ((seq_arn[i+2]=='U') || (seq_arn[i+2]=='C'))
                    seq_aa[compteur_seq_aa]=='Y'; /*UAU ou UAC = Tyrosine*/
                else if ((seq_arn[i+2]=='A') || (seq_arn[i+2]=='G'))
                    seq_aa[compteur_seq_aa]=='*'; /*UAA ou UAG = STOP*/
            } 
        }

        if (seq_arn[i]=='C'){
            if (seq_arn[i+1]=='U') 
                seq_aa[compteur_seq_aa]='L'; /*CU% = Leucine*/
            else if (seq_arn[i+1]=='C')
                seq_aa[compteur_seq_aa]='P'; /*CC% = Proline*/
            else if (seq_arn[i+1]=='A'){
                if ((seq_arn[i+2]=='U') || (seq_arn[i+2]=='C'))
                    seq_aa[compteur_seq_aa]='H'; /*CAU ou CAC = Histidine*/
                else if ((seq_arn[i+2]=='A') || (seq_arn[i+2]=='G'))
                    seq_aa[compteur_seq_aa]='Q'; /*CAA ou CAG = Glutamine*/
            }
            else if (seq_arn[i+1]=='G')
                seq_aa[compteur_seq_aa]='R'; /*CG% = Arginine*/
        }

        if (seq_arn[i]=='A'){
            if (seq_arn[i+1]=='U'){
                if ((seq_arn[i+2]=='U') || (seq_arn[i+2]=='C') || (seq_arn[i+2]=='A'))
                    seq_aa[compteur_seq_aa]='I'; /*AUU ou AUC ou AUA = Isoleucine*/
                else if (seq_arn[i+2]=='G')
                    seq_aa[compteur_seq_aa]='M'; /*AUG = Méthionine*/
            }
            else if (seq_arn[i+1]=='C')
                seq_aa[compteur_seq_aa]='T'; /*AC% = Thréonine*/
            else if (seq_arn[i+1]=='A'){
                if ((seq_arn[i+2]=='U') || (seq_arn[i+2]=='C'))
                    seq_aa[compteur_seq_aa]='D'; /*AAU ou AAC = Acide aspartique*/
                else if ((seq_arn[i+2]=='A') || (seq_arn[i+2]=='G'))
                    seq_aa[compteur_seq_aa]='K'; /*AAA ou AAG = Lysine*/
            }
            else if (seq_arn[i+1]=='G'){
                if ((seq_arn[i+2]=='U') || (seq_arn[i+2]=='C'))
                    seq_aa[compteur_seq_aa]='S'; /*AGU ou AGC = Sérine*/
                else if ((seq_arn[i+2]=='A') || (seq_arn[i+2]=='G'))
                    seq_aa[compteur_seq_aa]='R'; /*AAA ou AAG = Arginine*/
            }
        }

    compteur_seq_aa++;
    
    if (seq_aa[compteur_seq_aa]=='*') 
        break; /*Car c'est un codon STOP*/
    }
}


void module_traduction_sequence() {
/*Procédure qui permet de créer un nouveau fichier avec le brin traduit*/
    char path_input[30];
    char path_output[30];

    get_path_from_user(path_input); 

    int taille_seq = longueur_sequence(path_input);
    char seq_arn[taille_seq];
    extract_sequence(path_input, seq_arn);

    char seq_aa[taille_seq/3];

    traduction(taille_seq, &seq_arn, &seq_aa); /*Création de la séquence traduite*/
    save_sequence(path_output, seq_aa); 
}