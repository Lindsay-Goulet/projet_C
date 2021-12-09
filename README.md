## Projet C
# Logiciel d’analyse de séquences

Ce projet vise la mise en œuvre d’un logiciel d’analyse de séquences génomiques et protéiques eucaryotes, mettant à
disposition de l’utilisateur des modules complémentaires pouvant s’enchaîner à la manière d’un pipeline :

1. Recherche de la séquence codante de taille maximale – niveau : 3
2. Transcription d’une séquence ADN en séquence ARN – niveau : 1
3. Traduction d’une séquence codante en séquence protéique – niveau : 2
4. Calcul du score d’identité entre deux séquences – niveau : 1
5. Calcul du score de similarité de polarité entre deux séquences protéiques – niveau : 2
6. Recherche d’une séquence consensus à partir d’un alignement multiple – niveau : 3
7. Recherche de la plus grande sous-chaîne de polarité commune à 2 séquences protéiques – niveau : 4

Chaque module peut être considéré comme un sous-projet indépendant, vous pouvez les réaliser dans l’ordre que
vous voulez. Le niveau de difficulté de chaque module est symbolisé par un numéro de niveau, augmentant avec la
difficulté. Une bonne réalisation des modules de niveau 1 et 2 vous assurera la moyenne. Toute créativité complétant
avantageusement le logiciel (affichage amélioré, fonctionnalités supplémentaires, ...) sera prise en compte dans la
notation.

Le logiciel doit accueillir l’utilisateur avec un menu présentant les différents modules possibles, afin de lui permettre
d’en choisir un.

Pour utiliser notre logiciel :
    - il faut se mettre dans le répertoire courant avec le terminal
    - taper : make 
    - taper ./log_analyse_seq