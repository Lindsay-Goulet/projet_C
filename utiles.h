#ifndef utiles
#define utiles

void get_path_from_user(char* path_input);
 /* cette prodécure demande à l'utilisateur le nom de son fichier FASTA (avec l'extension .fa) et le stocke
dans une variable.*/

void extract_sequence(const char* path_input, char* sequence);
/*cette prodédure stocke la séquence du fichier FASTA dans la variable séquence*/

void save_sequence(const char* path_output, char* sequence);
/* cette procédure écrit dans un fichier la séquence contenue dans la variable sequence en renvoyant à la ligne 
tous les 80 caractères, comme dans le format FASTA */

void get_module_number_from_user(int* module_number);

int longueur_sequence(const char* path_input);

int polarite(char aa);

double pourct_id(double taille_seq, int nb_id);


void transfo_fichier_Fasta(char* path_input);
/* cette prodécure prend en argument un fichier et le remplace par un fichier contenant uniquement la 
sequence (une ligne). 
Exemple : 
on donne un fichier du type :
    >NG_011471 Homo sapiens
    ACTG.....ACTG (80 caractères par ligne)
    ACTG.....ACTG
Et il remplace ce fichier par :
     ACTG.....ACTGACTG.....ACTG  */



#endif