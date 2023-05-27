#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// les constantes
#define NB_LIGNES 6
#define NB_COLONNES 7
#define PION_A 'X'
#define PION_B 'O'
#define VIDE ' '
#define INCONNU ' '
#define start 0
#define max_vide 2

// les types
typedef int Grille[NB_LIGNES][NB_COLONNES];

// prototypes des fonctions
void initGrille(Grille laGrille);
void afficher(Grille laGrille, char pion);
bool grillePleine(Grille laGrille);
void jouer_a(Grille laGrille, char pion, int *ligne, int *colonne);
void jouer_b(Grille laGrille, char pion, int *, int *);
int choisirColonne(Grille laGrille, char pion);
int chercherLigne(Grille laGrille, int col);
bool estVainqueur(Grille laGrille, int lig, int col);
void finDePartie(char vainqueur);

void choisir_colonne(Grille laGrille, char pion, int *ligne, int *colonne);
int jouer_centre(Grille laGrille);
bool regarder(Grille tab, int, char, int *lig, int *col);
bool bloquer_joueur(Grille laGrille, char, int *lig, int *col);
bool trouver_pion(Grille tab, int, char, int *lig, int *col);

int main(void)
{

    int ligne;
    int colonne;

    Grille laGrille;
    char vainqueur = INCONNU;

    initGrille(laGrille);
    afficher(laGrille, PION_A);
    while (vainqueur == INCONNU && !grillePleine(laGrille))
    {

        jouer_a(laGrille, PION_A, &ligne, &colonne);
        afficher(laGrille, PION_B);
        if (estVainqueur(laGrille, ligne, colonne))
        {
            vainqueur = PION_A;
        }
        else if (!grillePleine(laGrille))
        {

            jouer_b(laGrille, PION_B, &ligne, &colonne);
            afficher(laGrille, PION_A);
            if (estVainqueur(laGrille, ligne, colonne))
            {
                vainqueur = PION_B;
            }
        }
    }
    finDePartie(vainqueur);
    system(EXIT_SUCCESS);
}




void initGrille(Grille laGrille)
{
    int l, c;
    for (l = 0; l < NB_LIGNES; l++)
    {
        for (c = 0; c < NB_COLONNES; c++)
        {
            laGrille[l][c] = VIDE;
        }
    }
}

void afficher(Grille laGrille, char pion)
{
    int l, c;
    system("clear");
    printf("\t");
    printf("  %c\n", pion);
    printf("\t");

    for (c = 0; c < NB_COLONNES; c++)
    {
        printf("----");
    }
    printf("-\n");
    for (l = 0; l < NB_LIGNES; l++)
    {
        printf("\t");
        for (c = 0; c < NB_COLONNES; c++)
        {
            printf("| %c ", laGrille[l][c]);
        }
        printf("|\n");
        printf("\t");
        for (c = 0; c < NB_COLONNES; c++)
        {
            printf("----");
        }
        printf("-\n");
    }
    printf("\t");
    for (c = 0; c < NB_COLONNES; c++)
    {
        printf("  %d ", c);
    }
    printf("\n\n");
}

bool grillePleine(Grille laGrille)
{
    bool pleine = true;
    int c = 0;
    while (pleine && c < NB_COLONNES)
    {
        if (laGrille[0][c] == VIDE)
        {
            pleine = false;
        }
        c++;
    }
    return pleine;
}

void jouer_a(Grille laGrille, char pion, int *ligne, int *colonne)
{
    *ligne = -1;
    do
    {
        *colonne = choisirColonne(laGrille, pion);
        *ligne = chercherLigne(laGrille, *colonne);
    } while (*ligne == -1);
    laGrille[*ligne][*colonne] = pion;
}

void jouer_b(Grille laGrille, char pion, int *ligne, int *colonne)
{

    choisir_colonne(laGrille, pion, (&*ligne), (&*colonne));
    laGrille[*ligne][*colonne] = pion;
}

int choisirColonne(Grille laGrille, char pion)
{
    int col;

    do
    {
        printf("Numero de colonne ? ");
        scanf("%d", &col);
    } while (col < 0 || col > 6);
    return col;
}

int chercherLigne(Grille laGrille, int col)
{
    int ligne = -1;

    while (ligne < NB_LIGNES - 1 && laGrille[ligne + 1][col] == VIDE)
    {
        ligne++;
    }
    return ligne;
}

bool estVainqueur(Grille laGrille, int lig, int col)
{
    // consiste Ã  regarder si une ligne de 4 pions s'est formÃ©e autour du pion qui vient de tomber en (lig, col)
    char lePion = laGrille[lig][col];
    int cpt, i, j;

    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    while (i < NB_LIGNES && laGrille[i][col] == lePion)
    {
        cpt++;
        i++;
    }
    if (cpt >= 4)
    {
        return true;
    }
    // regarder l'horizontale, en comptant le nombre de pions Ã  l'Est et Ã  l'Ouest
    j = col;
    cpt = 0;
    // on regarde Ã  l'est
    while (j >= 0 && laGrille[lig][j] == lePion)
    {
        cpt++;
        j--;
    }
    j = col + 1;
    // on regarde Ã  l'ouest
    while (j < NB_COLONNES && laGrille[lig][j] == lePion)
    {
        cpt++;
        j++;
    }
    if (cpt >= 4)
    {
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Ouest
    while (j >= 0 && i >= 0 && laGrille[i][j] == lePion)
    {
        cpt++;
        i--;
        j--;
    }
    i = lig + 1;
    j = col + 1;
    // on regarde au Sud Est
    while (i < NB_LIGNES && j < NB_COLONNES && laGrille[i][j] == lePion)
    {
        cpt++;
        i++;
        j++;
    }
    if (cpt >= 4)
    {
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Est
    while (j < NB_COLONNES && i >= 0 && laGrille[i][j] == lePion)
    {
        cpt++;
        i--;
        j++;
    }
    i = lig + 1;
    j = col - 1;
    // on regarde au Sud Ouest
    while (i < NB_LIGNES && j >= 0 && laGrille[i][j] == lePion)
    {
        cpt++;
        i++;
        j--;
    }
    if (cpt >= 4)
    {
        return true;
    }
    return false;
}

void finDePartie(char vainqueur)
{
    if (vainqueur != INCONNU)
    {
        printf("Joueur %c vainqueur\n", vainqueur);
    }
    else
    {
        printf("MATCH NUL");
    }
}

void choisir_colonne(Grille tab, char pion, int *ligne, int *colonne)
{
    int lig;
    int col;

    char pion_adverse;

    if (pion == PION_A)
    {
        pion_adverse = PION_B;
    }
    else
    {
        pion_adverse = PION_A;
    }

    if (bloquer_joueur(tab, pion_adverse, &lig, &col))
    {

        *ligne = lig;
        *colonne = col;
    }
    else if (trouver_pion(tab, 3, pion, &lig, &col))
    {
        *ligne = lig;
        *colonne = col;
    }

    else
    {
        *colonne = jouer_centre(tab);
        *ligne = chercherLigne(tab, *colonne);
    }
}

bool bloquer_joueur(Grille tab, char pion, int *lig, int *col)
{

    for (int i = 0; i < NB_LIGNES; i++)
    {
        for (int j = 0; j < NB_COLONNES; j++)
        {
            if (tab[i][j] == pion && regarder(tab, 3, pion, &i, &j))
            {

                *lig = i;
                *col = j;

                return true;
            }
        }
    }

    return false;
}

bool trouver_pion(Grille tab, int x, char pion, int *lig, int *col)
{

    for (int i = 0; i < NB_LIGNES; i++)

    {
        for (int j = 0; j < NB_COLONNES; j++)
        {
            if (tab[i][j] == pion && regarder(tab, x, pion, &i, &j))
            {

                *lig = i;
                *col = j;
                return true;
            }
        }
    }

    if (x > 0)
    {
        return trouver_pion(tab, x - 1, pion, &(*lig), &(*col));
    }

    return false;
}

bool regarder(Grille laGrille, int nb, char lePion, int *lig, int *col)
{

    int cpt, i, j;
    int compteur = 0;
    // Pour l'horizontale on contre quand il y a 2 pions allignés
    int tmp = nb;
    if (nb == 3)
    {
        tmp--;
    }

    // regarder la verticale, en comptant le nombre de pions au Sud
    i = *lig;
    cpt = 0;
    while (i < NB_LIGNES && laGrille[i][*col] == lePion)
    {
        cpt++;

        if (cpt >= nb && *lig != 0 && laGrille[*lig - 1][*col] == VIDE)
        {
            *lig = *lig - 1;
            return true;
        }

        i++;
    }

    // regarder l'horizontale, en comptant le nombre de pions de l'Est vers l'Ouest
    j = *col;
    cpt = 0;
    // on regarde Ã  l'est

    while (j >= start && (laGrille[*lig][j] == lePion || laGrille[*lig][j] == VIDE))
    {
        if (laGrille[*lig][j] == lePion)
        {
            cpt++;
        }
        else if (laGrille[*lig][j] == VIDE)
        {

            compteur++;
        }
        // remets le compteur à zéro si il y a plus de 2 cases vides
        if (compteur == max_vide)
        {
            cpt = 0;
        }

        if (cpt >= tmp)
        {

            if (*col - 2 >= start && (tmp == 2 || tmp == 3) && laGrille[*lig][*col - 2] == VIDE && (laGrille[*lig + 1][*col - 2] != VIDE || *lig == 5))
            {

                *lig = *lig;
                *col = *col - 2;
                return true;
            }
            else if (*col - 1 >= start && laGrille[*lig][*col - 1] == VIDE && (laGrille[*lig + 1][*col - 1] != VIDE || *lig == 5))
            {

                *lig = *lig;
                *col = *col - 1;
                return true;
            }
            else if (*col + 1 < NB_COLONNES && laGrille[*lig][*col + 1] == VIDE && (laGrille[*lig + 1][*col + 1] != VIDE || *lig == 5))
            {
                *lig = *lig;
                *col = *col + 1;
                return true;
            }
            else if (*col - 3 >= start && tmp == 3 && laGrille[*lig][*col - 3] == VIDE && (laGrille[*lig + 1][*col - 3] != VIDE || *lig == 5))
            {
                *lig = *lig;
                *col = *col - 3;
                return true;
            }
            else
            {
                cpt = 0;
            }
        }
        j--;
    }

    i = *lig;
    j = *col;
    cpt = 0;
    compteur = 0;
    // on regarde au Nord Ouest jusqu'au Sud Est
    while (i < NB_LIGNES && j < NB_COLONNES && (laGrille[i][j] == lePion || laGrille[i][j] == VIDE))
    {
        if (laGrille[i][j] == lePion)
        {
            cpt++;
        }
        else if (laGrille[i][j] == VIDE)
        {

            compteur++;
        }
        if (compteur == max_vide)
        {
            cpt = 0;
        }

        if (cpt >= nb)
        {
            if ((*lig + 1 < NB_LIGNES) && (*col + 1 < NB_COLONNES) && laGrille[*lig + 1][*col + 1] == VIDE)
            {
                if (*lig + 1 == NB_LIGNES - 1)
                {
                    *lig = *lig + 1;
                    *col = *col + 1;
                    return true;
                }
                if (laGrille[*lig + 2][*col + 1] != VIDE)
                {
                    *lig = *lig + 1;
                    *col = *col + 1;
                    return true;
                }
            }
            else if ((nb == 2 || nb == 3) && (*lig + 2 < NB_LIGNES) && (*col + 2 < NB_COLONNES) && laGrille[*lig + 2][*col + 2] == VIDE)
            {
                if (*lig + 2 == NB_LIGNES - 1)
                {
                    *lig = *lig + 2;
                    *col = *col + 2;
                    return true;
                }
                if (laGrille[*lig + 3][*col + 2] != VIDE)
                {
                    *lig = *lig + 2;
                    *col = *col + 2;
                    return true;
                }
            }
            else if ((*lig - 1 >= start) && (*col - 1 >= start) && laGrille[*lig - 1][*col - 1] == VIDE)
            {

                if (laGrille[*lig][*col - 1] != VIDE)
                {
                    *lig = *lig - 1;
                    *col = *col - 1;
                    return true;
                }
            }

            else if (nb == 3 && (*lig + 3 < NB_LIGNES) && (*col + 3 < NB_COLONNES) && laGrille[*lig + 3][*col + 3] == VIDE)
            {
                if (*lig + 3 == NB_LIGNES - 1)
                {
                    *lig = *lig + 3;
                    *col = *col + 3;
                    return true;
                }
                if (laGrille[*lig + 4][*col + 3] != VIDE)
                {
                    *lig = *lig + 3;
                    *col = *col + 3;
                    return true;
                }
            }
            else
            {
                cpt = 0;
            }
        }
        j++;
        i++;
    }
    i = *lig;
    j = *col;
    cpt = 0;
    compteur = 0;
    // on regarde au Sud Ouest jusqu'au Nord Est
    while (j < NB_COLONNES && i >= 0 && (laGrille[i][j] == lePion || laGrille[i][j] == VIDE))
    {
        if (laGrille[i][j] == lePion)
        {
            cpt++;
        }
        else if (laGrille[i][j] == VIDE)
        {

            compteur++;
        }
        if (compteur == max_vide)
        {
            cpt = 0;
        }

        if (cpt >= nb)
        {
            if ((*lig - 1 >= start) && (*col + 1 < NB_COLONNES) && laGrille[*lig - 1][*col + 1] == VIDE && (laGrille[*lig][*col + 1] != VIDE || *lig - 1 == 0))
            {

                if (laGrille[*lig][*col + 1] != VIDE)
                {
                    *lig = *lig - 1;
                    *col = *col + 1;
                    return true;
                }
            }
            else if ((nb == 2 || nb == 3) && (*lig - 2 >= start) && (*col + 2 < NB_COLONNES) && laGrille[*lig - 2][*col + 2] == VIDE && (laGrille[*lig - 1][*col + 2] != VIDE || *lig - 2 == 0))
            {

                if (laGrille[*lig - 1][*col + 2] != VIDE)
                {
                    *lig = *lig - 2;
                    *col = *col + 2;
                    return true;
                }
            }
            else if ((*lig + 1 < NB_LIGNES) && (*col - 1 >= start) && laGrille[*lig + 1][*col - 1] == VIDE && (laGrille[*lig + 2][*col - 1] != VIDE || *lig + 1 == 5))
            {
                if (*lig + 1 == NB_LIGNES - 1)
                {
                    *lig = *lig + 1;
                    *col = *col - 1;
                    return true;
                }
                if (laGrille[*lig + 2][*col - 1] != VIDE)
                {
                    *lig = *lig + 1;
                    *col = *col - 1;
                    return true;
                }
            }

            else if (nb == 3 && (*lig - 3 >= start) && (*col + 3 < NB_COLONNES) && laGrille[*lig - 3][*col + 3] == VIDE && (laGrille[*lig - 2][*col + 3] != VIDE || *lig - 3 == 0))
            {

                if (laGrille[*lig - 2][*col + 3] != VIDE)
                {
                    *lig = *lig - 3;
                    *col = *col + 3;
                    return true;
                }
            }
            else
            {
                cpt = 0;
            }
        }
        j++;
        i--;
    }

    return false;
}

int jouer_centre(Grille tab)
{
    int colonne, i, j;
    bool trouver = false;
    colonne = NB_COLONNES / 2;
    i = colonne - 1;
    j = colonne + 1;

    if (tab[0][colonne] == VIDE)
    {
        colonne = colonne;
    }
    else
    {
        while (!trouver && i > -1)
        {
            if (tab[0][j] == VIDE)
            {
                colonne = j;
                trouver = true;
            }
            else if (tab[0][i] == VIDE)
            {
                colonne = i;
                trouver = true;
            }

            i--;
            j++;
        }
    }

    return colonne;
}
