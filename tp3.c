//
// Created by pllsj on 28/03/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"
#include <string.h>


void ajout(T_Electeur *tElecteur)                              // permet d'ajouter nombre_electeurs electeurs à la liste
{

    int choix;
    int stop = 0;
    int choixUser;
    long cin_num;
    char nom[MAX_LENGTH];
    while (stop== 0) {                                                 // tant que stop est différent de 1 on itère
        printf("\n------------------Electeur---------------------");
        printf("\n Nom : ");
        scanf("%s", &nom);
        fflush(stdin);
        printf("Numero de CIN : ");
        scanf("%ld", &cin_num);
        fflush(stdin);
        printf("Choix : ");
        scanf("%d", &choix);
        fflush(stdin);
        printf("-----------------------------------------------");
        ajoutelecteur(tElecteur, nom, cin_num, choix);                  // on ajoute l'électeur à la liste une fois toutes les infos récupérées
        printf("\nVoulez-vous ajouter un autre electeur (O/N) ?");
        choixUser = getchar();
        if(choixUser == 'n' || choixUser == 'N') stop =1;
    }
    printf("\nFin de l'ajout des electeurs\n");
}

void reinitialisation(T_Electeur *tElecteur)                                    // permet de réinitialiser la liste lorsqu'il faut faire une mise à jour
{
    libereliste(*tElecteur);
    *tElecteur = NULL;
}

T_Electeur creationelecteur(void)                                               //créer un nouvel électeur
{
    electeur *nouveau = malloc(sizeof(*nouveau));                          // on alloue de l'espace mémoire pour le nouvel électeur
    if (nouveau!=NULL)                                                          // vérification qu'il n'y a pas d'erreur lors de l'allocation mémoire
    {
        nouveau->suivant = NULL;                                                // on initialise l'électeur suivant à NULL
        return nouveau;                                                         // on retourne l'électeur
    }
    printf("[Erreur lors de la creation de l'electeur.]");
    return NULL;
}

void afficheliste(T_Electeur tElecteur)                                         //affiche les informations relatives aux électeurs de la liste
{

    printf("\n               NOM                 |      CIN        | CHOIX ");
    printf("\n-------------------------------------------------------------");
    if(tElecteur==NULL)                                                         // si la liste est vide, on l'indique
    {
        printf("\n[Liste vide]\n");
        return;
    }
    while(tElecteur!= NULL)                                                     // tant que l'électeur pointé n'est pas nul, on l'affiche
    {
        printf("\n%30s     | %15ld |   %1d ", tElecteur->nom, tElecteur->cin_num,tElecteur->choix);
        tElecteur = tElecteur->suivant;
    }
    printf("\n");

}
void ajoutelecteur(T_Electeur *tElecteur, char nom[MAX_LENGTH], long cin_num, int choix ) //ajoute un électeur dans la liste
{
    if (trouvelecteur(*tElecteur,cin_num)!=-1)                                               // On vérifie si l'électeur est déjà dans la liste
    {
        printf("\n[L'electeur est deja dans la liste]\n");                                      // si oui, on ne l'ajoute pas
        return;
    }
    electeur *nouveau = creationelecteur();                                                 // création d'un électeur et initialisation de ses attributs
    if (nouveau !=NULL)                                                                     // vérification qu'il n'y a pas d'erreur lors de la creation de l'electeur
    {
        strcpy(nouveau->nom,nom);                                                   // on copie le nom dans l'attribut nom de nouveau avec strcpy()
        nouveau->cin_num = cin_num;
        nouveau->choix = choix;

        if (*tElecteur == NULL)                                                                    // si liste vide, liste = nouveau
        {
            *tElecteur = nouveau;
            return;
        }
        electeur *temp = *tElecteur;                                                            // création d'une variable temporaire pour itérer sur *tElecteur
        if (strcmp(temp->nom, nom) >0)                                               // si l'électeur est à placer au début de la liste, nouveau devient tête de liste
        {
            nouveau->suivant = temp;
            *tElecteur = nouveau;
        } else {
            while (temp->suivant != NULL && strcmp(temp->suivant->nom, nom) <0)                     // tant que le nom est placé après le nom de la variable temporaire, on itère
            {
                temp = temp->suivant;
            }
            nouveau->suivant = temp->suivant;                                                   // On place nouveau devant la variable temporaire
            temp->suivant = nouveau;
        }
    }
    else printf("[Impossible d'ajouter l'electeur.]");

}
int comptelecteur(T_Electeur tElecteur)                                                     //compte le nombre d'électeurs
{
    int compteur = 0;
    while(tElecteur!=NULL)                                                                  // tant que l'électeur pointé n'est pas nul, on incrémente le compteur
    {
        compteur++;
        tElecteur =  tElecteur->suivant;
    }
    return compteur;
}

int trouvelecteur(T_Electeur tElecteur, long cin_num)                                        //recherche un électeur en fonction de son numéro de CIN
{
    int position = 1;
    while(tElecteur !=NULL)
    {
        if(tElecteur->cin_num==cin_num)
        {
            printf("\n----------Informations de l'electeur----------");
            printf("\nNom : %s",tElecteur->nom);
            printf("\nNumero de CIN : %ld",tElecteur->cin_num);
            printf("\nChoix : %d",tElecteur->choix);
            printf("\n----------------------------------------------");
            return position;
        }
        else
        {
            position++;
            tElecteur = tElecteur->suivant;
        }
    }
    return -1;                                                                                       // on retourne -1 s'il est introuvable
}

void supprimelecteur(T_Electeur *tElecteur,long cin_num)                                             // supprime un électeur de la liste en fonction du numéro de CIN
{
    if ((*tElecteur)->cin_num == cin_num)                                                      // si l'électeur est en début de liste
    {
        printf("\n----------Informations de l'electeur----------");
        printf("\nNom : %s",(*tElecteur)->nom);
        printf("\nNumero de CIN : %ld",(*tElecteur)->cin_num);
        printf("\nChoix : %d",(*tElecteur)->choix);
        printf("\n----------------------------------------------");
        *tElecteur = (*tElecteur)->suivant;                                                         // la tête de liste est le 2ème électeur
        printf("\n[Electeur supprime]");
    }
    else if(trouvelecteur(*tElecteur,cin_num)==-1) printf("\n[Electeur introuvable]");     // on indique que l'électeur n'existe pas si introuvable
    else
    {
        int supprime = 0;
        electeur *suivant = (*tElecteur)->suivant;                                                  // représente l'électeur suivant celui que l'on cherche à supprimer
        electeur *precedent = *tElecteur;                                                           // représente l'électeur précédent celui que l'on cherche à supprimer
        while (!supprime)
        {

            if (suivant->cin_num == cin_num)                                                        // si l'électeur est trouvé, le précédent pointe vers le suivant
            {
                precedent->suivant = suivant->suivant;
                supprime = 1;
            }
            else                                                                                    // sinon on continue d'itérer,précédent et suivant "avancent"
            {
                suivant = suivant->suivant;
                precedent = precedent->suivant;
            }


        }
        printf("\n[Electeur supprime]");
    }
}

void decoupeliste(T_Electeur tElecteur,T_Electeur *gauche,T_Electeur *droite,T_Electeur *blanc)                         // divise la liste en 3 sous-listes
{
    while (tElecteur!=NULL)                                                                                             // on continue d'itérer dans que l'électeur pointé n'est pas nul (arrivé à la fin)
    {
        if (tElecteur->choix==1 || tElecteur->choix==3)                                                                 // si le choix de l'électeur correspond à un critère d'une liste, on l'ajoute
        {
            ajoutelecteur(gauche,tElecteur->nom,tElecteur->cin_num,tElecteur->choix);
        }
        else if (tElecteur->choix==2 || tElecteur->choix==4)
        {
            ajoutelecteur(droite,tElecteur->nom,tElecteur->cin_num,tElecteur->choix);
        }
        else
        {
            ajoutelecteur(blanc,tElecteur->nom,tElecteur->cin_num,tElecteur->choix);
        }
        tElecteur = tElecteur->suivant;
    }
}

void permuter(electeur *a,electeur *b)                                       //permet d'échanger les données de 2 électeurs, utilisée dans triliste()
{
    electeur *temp = creationelecteur();                                     // création d'une variable temporaire pour effectuer l'échange
    if(temp!=NULL) {                                                         // si pas d'erreur lors de l'allocation mémoire
        temp->cin_num = a->cin_num;                                          // on affecte à temp les valeurs de a
        temp->choix = a->choix;
        strcpy(temp->nom, a->nom);

        a->cin_num = b->cin_num;                                             // a prend les valeurs de b
        strcpy(a->nom, b->nom);
        a->choix = b->choix;

        b->cin_num = temp->cin_num;                                          // b prend les valeurs de temp, c-à-d celles de a
        strcpy(b->nom, temp->nom);
        b->choix = temp->choix;
        free(temp);
    }                                                                        // cette variable temporaire n'est plus utile, on la libère
    else printf("\n[Erreur pendant la permutation]");
}
void triliste(T_Electeur tElecteur)                                         // tri à bulles
{
    if(tElecteur!=NULL && comptelecteur(tElecteur)>1)                       // si la liste n'est pas vide et plus grande que 1, on effectue le tri selon le numéro de CIN
    {
        int permut;
        electeur *ptr;
        do {
            permut = 0;
            ptr = tElecteur;
            while (ptr->suivant != NULL) {
                if (ptr->cin_num > ptr->suivant->cin_num)                    // si cin_num est plus grand que cin_num de l'électeur suivant, on permute avec permuter()
                {
                    permuter(ptr, ptr->suivant);
                    permut = 1;
                }
                ptr = ptr->suivant;                                         // on passe à l'électeur suivant
            }
        } while (permut);                                                   // si on a permuté au moins 1 fois (permut=1), on revérifie si la liste est bien triée
    }
}

T_Electeur fusionlistes(T_Electeur tElecteur, T_Electeur tElecteur1)        // permet de fusionner deux listes en une
{
    T_Electeur fusion = NULL;
    while(tElecteur!=NULL)                                                  // on ajoute tous les électeurs de tElecteur à fusion
    {
        ajoutelecteur(&fusion,tElecteur->nom,tElecteur->cin_num,tElecteur->choix);
        tElecteur= tElecteur->suivant;
    }
    while(tElecteur1!=NULL)                                                 // on ajoute tous les électeurs de tElecteur1 à fusion
    {
        ajoutelecteur(&fusion,tElecteur1->nom,tElecteur1->cin_num,tElecteur1->choix);
        tElecteur1= tElecteur1->suivant;
    }
    triliste(fusion);                                                       // on trie la fusion des 2 listes
    return fusion;
}
int compteGD(T_Electeur tElecteur)                                          //compte le nombre d'électeurs de gauche d'une liste
{
    int compteur = 0;
    while(tElecteur!=NULL)
    {
        if(tElecteur->choix==1 || tElecteur->choix==3)
        {
            compteur++;                                                    // si l'électeur est de gauche, on incrémente le compteur

        }
        tElecteur =  tElecteur->suivant;                                   // puis on passe à l'électeur suivant
    }
    return compteur;
}
void libereliste(T_Electeur tElecteur)                                      // on libère l'espace mémoire que prennent les n électeurs
{
    T_Electeur temp;                                                        // on crée une variable temporaire qui permet de pointer sur chaque électeur
    while(tElecteur !=NULL)
    {
        temp = tElecteur;                                                   // temp prend l'adresse de l'électeur pointée par tElecteur
        tElecteur = tElecteur->suivant;                                     //  tElecteur pointe vers l'électeur suivant
        free(temp);                                                         // on peut maintenant libérer l'emplacement mémoire pointé par temp
    }
}

void lecture_fichier(T_Electeur *tElecteur, char nom_fichier[MAX_LENGTH])   // permet de lire les informations des électeurs sur un fichier .txt
{
    FILE *f;                                                                // création d'un pointeur vers le fichier
    int choix;
    long cin_num;
    char nom[MAX_LENGTH];

    f = fopen(nom_fichier, "r");                                            // ouverture du fichier

    if(f==NULL){                                                            // si fichier inexistant ou erreur d'ouverture, on arrête
        printf("Erreur lors de l'ouverture d'un fichier.\n");
        return;
    }

    while(fscanf(f, "Nom : %s Num CIN : %ld Choix : %d\n", &nom, &cin_num,&choix) != EOF)                // tant que fscanf ne retourne pas EOS ou -1 (fin de fichier ou erreur), on lit les lignes
    {                                                                                                    // ici fscanf lit un fichier formaté
        ajoutelecteur(tElecteur, nom, cin_num, choix);                                                   // on ajoute chaque électeur à la liste
    }
    fclose(f);                                                                                           // on ferme le fichier
}
