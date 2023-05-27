#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * \brief Programme sur le jeu du puissance 4
 * 
 * \author VASSEUR Gwendal  
 * 
 * \date 10 novembre 2022 
 * 
 * Ce programme va permettre à 2 utilisateurs de jouer au jeu du puissance 4
 * 
 * 
*/

/**déclaration d'un pion pour le joueur 1*/
const char PION_A ='X'; 

/**déclaration d'un pion pour le joueur 2*/
const char PION_B ='O'; 

/**Caractère vide qui servira pour savoir si un joueur à gagné*/
const char INCONNU =' '; 

/** Caractère vide qui servira à initialiser le tableau à vide*/
const char VIDE =' '; 

/** entier qui permet de vérifier si il y a un vainqueur*/
const int P4 = 3; 

/**
 * \def NBLIG
 * \brief nombre de ligne maximale du tableau
*/

#define NBLIG  6

/**
 * \def NBCOL
 * \brief nombre de colonne maximale du tableau
*/
#define NBCOL  7

/**colonne de départ */
const int COLONNE_DEBUT =NBCOL/2; 

/**
 * \typedef t_tableau
 * \brief Type tableau de NBLIG ligne et NBCOL colonne
 * 
 * le type t_tableau permet de créer la grille de jeu du puissance 4
*/
typedef char t_tableau[NBLIG][NBCOL];

/*********************************************************
 * prototype des fonctions disponibles dans ce programme *
**********************************************************/

void init_grille(t_tableau );/** Initialise la grille */
void afficher_grille(t_tableau, char, int );/** Affiche la grille*/
bool grille_pleine(t_tableau);/**Renvoie vrai si grille pleine ou faux sinon*/
void jouer(t_tableau, char , int *, int *)/** Permet de jouer*/;
int choisir_colonne(t_tableau,char , int );/**Permet de choisir une colonne*/
int trouver_ligne(t_tableau,int );/**Trouver la ligne correspondant à la colonne choisi*/
bool estVainqueur(t_tableau,int , int );/**Renvoie vrai si 4 pions alligné à partir d'un point ou faux sinon*/
void fin_de_partie(char );/**affiche le gagant de la partie ou match nul*/

/****************************************
 *          PROGRAMME PRINCIPAL         *
*****************************************/

/**
 * \fn int main()   
 * \brief Programme principal
 * \return Code  de sortie du programme: sortie normale).
 * 
 * Le programme utilise les fonctions crées afin de pouvoir jouer au jeu du puissance 4
*/

int main() 
{
    char vainqueur;
    int ligne, colonne;
    t_tableau grille;

    init_grille(grille);
    vainqueur = INCONNU;
    afficher_grille(grille, PION_A, COLONNE_DEBUT);   
    
    while  ((vainqueur == INCONNU) &&  !(grille_pleine(grille))){
        jouer(grille,PION_A,&ligne, &colonne);
        afficher_grille(grille,PION_B, COLONNE_DEBUT);
        if (estVainqueur(grille,ligne,colonne)){
            vainqueur= PION_A;

        }else if (!grille_pleine(grille))
            {
                jouer(grille,PION_B,&ligne, &colonne);
                afficher_grille(grille, PION_A,COLONNE_DEBUT);
                if(estVainqueur(grille,ligne,colonne)){
                    vainqueur = PION_B;
                }
            }
    }
    fin_de_partie(vainqueur);
    return EXIT_SUCCESS;
} 

/**
 * \fn init_grille(t_tableau tab)
 * 
 * \brief procédure qui permet d'initialiser la grille
 * 
 * \param tab : paramètre d'entrée/sortie qui représente le tableau à initialiser
 * 
 * Consiste à initialiser la grille en assignant à chaque case la constante VIDE
*/
void init_grille(t_tableau tab){
    for (int i =0; i< NBLIG;i++){
        for(int y =0; y <NBCOL; y++){
            tab[i][y]= VIDE;
        }
    }
}
/**
 * \fn afficher_grille(t_tableau tab, char pion, int colonne)
 * 
 * \brief procédure qui permet d'afficher la grille
 * 
 * \param tab : paramètre d'entrée/sortie qui représente le tableau à afficher
 * \param pion : paramètre d'entrée qui représente le pion à afficher au-dessus de la grille
 * \param colonne : paramètre d'entrée qui représente la l'indice de la colonne où afficher le pion 
 * 
 * Permet d'afficher la grille ainsi que le pion placer au-dessus de la grille
*/

void afficher_grille(t_tableau tab, char pion, int colonne){
    
    system("clear");
    int tab2[NBCOL]={0,1,2,3,4,5,6};
    char tab3[NBCOL];
    for (int i =0; i < NBCOL; i++){
        tab3[i] = ' ';
    }
    tab3[colonne]=pion;
    printf("   | %d | %d | %d | %d | %d | %d | %d | \n", tab2[0],tab2[1], tab2[2],tab2[3], tab2[4],tab2[5], tab2[6]);
    printf("   | %c | %c | %c | %c | %c | %c | %c |", tab3[0],tab3[1], tab3[2],tab3[3], tab3[4],tab3[5], tab3[6]);
    int a =0;
    printf("\n--------------------------------");
    for (int x =0; x < NBLIG;x++){
            
            printf("\n %d | %c | %c | %c | %c | %c | %c | %c |  \n",a,tab[x][0],tab[x][1],tab[x][2],tab[x][3],tab[x][4],tab[x][5],tab[x][6]);
            a++;
        }
}

/**
 * \fn grille_pleine(t_tableau tab)
 * 
 * \brief fonction qui regarde si la grille est pleine ou non
 * 
 * \param tab : paramètre d'entrée/sortie qui représente la grille de jeu
 * 
 * \return  true si le tableau est plein, false sinon
 * 
 * Consiste à vérifier si une grille est pleine en regardant chaque case, si toutes les cases sont occupés
 * la fonction retourne donc true
*/

bool grille_pleine(t_tableau tab){
   bool plein = true;
    int i = 0;
    while (plein && i<NBCOL){
        if (tab[0][i] == VIDE){
            plein = false;
        }
        i++;
    }
    return plein;
}

/**
 * \fn jouer(t_tableau tab, char pion, int *ligne, int *colonne)
 * 
 * \brief procédure qui permet de jouer au jeu du puissance 4
 * 
 * \param tab : paramètre d'entrée/sortie qui représente la grille de jeu
 * \param pion : paramètre d'entrée qui représente le pion à jouer
 * \param ligne : paramètre de sortie qui représente l'indice de la ligne où est tombé le pion
 * \param colonne : paramètre de sortie qui représente l'indice de la colonne où est tombé le pion
 * 
 * permet de jouer au puissance 4 en utilisant deux autres fonctions :
 * choisir_colonne et trouver_ligne, afin que le joueur choisisse une case où 
 * faire tomber son pion
*/

void jouer(t_tableau tab, char pion, int *ligne, int *colonne){
    *colonne = choisir_colonne(tab, pion, COLONNE_DEBUT);
    *ligne = trouver_ligne(tab,*colonne);
    tab[*ligne][*colonne]=pion;
}

/**
 * \fn choisir_colonne(t_tableau tab,char pion, int colonne)
 * 
 * \brief fonction qui permet au joueur de choisir une colonne
 * 
 * \param tab : paramètre d'entrée/sortie qui représente la grille de jeu
 * \param pion : paramètre d'entrée qui représente un caractère représentant le pion à tester 
 * \param colonne : paramètre d'entrée qui représente l'indice de la colonne de départ où se trouve initialement le pion
 * 
 * \return l'indice de la colonne choisi par le joueur
 * 
 * Permet au joueur de déplacer son pion avec 'd' et 'q' et de choisir une colonne
 * en appuyant sur la barre espace
*/

int choisir_colonne(t_tableau tab,char pion, int colonne){
    char choix;
    ;
    do{
        printf("Choisisez d pour avancer votre pion à droite et q pour avancer à gauche \n et appuyez sur la barre 'ESPACE' valider le choix \n");
        scanf("%c", &choix);
        if ((choix == 'd')&& (colonne < 6)) {
            colonne++;
        }
        else if ((choix == 'q')&& (colonne > 0)){
            colonne--;
        }else{
            colonne = colonne;
        }
        afficher_grille(tab, pion, colonne);

    }while(choix != VIDE);

    if (tab[0][colonne] != VIDE){
        return choisir_colonne(tab,pion,colonne);
    }
    return colonne;

}

/**
 * \fn trouver_ligne(t_tableau tab,int colonne)
 * 
 * \brief fonction qui trouve la première case non occupé de la colonne
 * 
 * \param tab :paramètre d'entrée/sortie représente la grille de jeu
 * \param colonne :paramètre d'entrée qui représente l'indice de la colonne dans laquelle le pion doit tomber
 * 
 * \return l'indice de la ligne où le pion devra être ajouté ou -1 si colonne pleine
 * 
 * Consiste à trouver la première case non occupée de la colonne en vérifiant si chaque ligne
 * de la colonne n'est pas occupé par un pion. 
 * 
 */

int trouver_ligne(t_tableau tab,int colonne){
    int ligne = -1;
    int i =0;
        while((tab[i][colonne] !=PION_A || tab[i][colonne] !=PION_B) && (i <NBLIG)){
            if (tab[i][colonne]==' '){
                ligne++;
            }
            i++;
        }
    return ligne;
}
/**
 * \fn estVainqueur(t_tableau tab,int ligne, int colonne)
 * 
 * \brief Fonction qui vérifie si 4 pions sont allignés horizontalement, verticalement ou diagonalement
 * 
 * \param tab : paramètre d'entrée/sortie qui représente la grille de jeu
 * \param ligne  : paramètre d'entrée qui représente l'indice de la ligne à partir de laquelle rechercher une série de 4 pions allignés
 * \param colonne : paramètre d'entrée qui  représente l'indice de la colonne à partir de laquelle rechercher une série de 4 pions allignés
 * 
 * \return true si 4 pions allignés, false sinon
 * 
 * Consiste à vérifier si 4 pions sont allignés horizontalement, verticalement ou diagonalement à partir de la ligne et de la colonne
 * mit en paramètre.
 * 
 */

bool estVainqueur(t_tableau tab,int ligne, int colonne){
    bool vainqueur = false;
    int compt =0;
    int c = colonne -P4;
    int l = ligne-P4;
    char test_joueur=tab[ligne][colonne];

    // test horizontal
    while (!vainqueur && c < NBLIG){
        if(tab[ligne][c]== test_joueur && tab[ligne][c+1]== test_joueur){
            compt++; 
            if (compt ==P4){
                vainqueur = true;
            }  
        }
        else{
            compt =0;
        }
        c++;
    }
    
    //test vertical
    compt =0;
    while (!vainqueur && l < NBLIG){
        if(tab[l][colonne]== test_joueur && tab[l+1][colonne]==test_joueur ){
            compt++;   
            if(compt ==P4){
                
                vainqueur = true;
            }
        }else{
            compt =0;
        }
        l++;
    }
    // test diagonal
    compt =0;
    c=colonne -P4;
    l=ligne -P4;
    while (!vainqueur &&(c <colonne +P4 && l <ligne +P4)){
        if (tab[l][c]==test_joueur && tab[l+1][c+1]==test_joueur){
            compt++;
            if(compt == P4){
                vainqueur = true;
            }

        }else{
            compt =0;
        }
        c++;
        l++;
    }
    for (int i = 0; i < NBCOL - P4; i++) {
        for (int j = P4; j < NBCOL; j++) {
            if (tab[i][j] == test_joueur && tab[i + 1][j - 1] == test_joueur && tab[i + 2][j - 2] == test_joueur && tab[i + 3][j - 3] == test_joueur
            ) {
                vainqueur = true;
            }
        }
    }
    return vainqueur; 
}

/**
 * \fn fin_de_partie(char pion)
 * 
 * \brief procédure qui affiche si gagnant ou match nul
 * 
 * \param pion : paramètre d'entrée qui représente le pion gagant ou vide si match nul
 * 
 * Permet d'afficher suivant le pion donné en paramètre si il y a un gagant ou bien
 * si il y a match nul.
 * 
 */

void fin_de_partie(char pion){
    if (pion ==PION_A){
        printf("Le vainqueur est le joueur X \n");
    }else if ( pion ==PION_B){
        printf("Le vainqueur est le joueur O \n");
    }else{
        printf("Il y a match nul");
    }
}

