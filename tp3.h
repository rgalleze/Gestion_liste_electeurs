//
// Created by pllsj on 28/03/2022.
//

#ifndef TP3_TP3_H
#define TP3_TP3_H
#define MAX_LENGTH 30                                                                  // Définition (une constante) de la taille maximale de la variable nom
typedef struct electeur
{
    char nom[MAX_LENGTH];
    long cin_num;
    int choix;
    struct electeur *suivant;
}electeur;

typedef struct electeur*T_Electeur;

//---------------FONCTION AJOUTEES--------------------
void ajout(T_Electeur *tElecteur);                      // ajoute n électeurs (saisis par l'utilisateur) à la liste
void reinitialisation(T_Electeur *tElecteur);           // permet de réinitialiser la liste lorsqu'il faut faire une mise à jour
void permuter(electeur *a,electeur *b);                 // permet d'échanger les données de 2 électeurs, utilisée dans triliste()
void lecture_fichier(T_Electeur *tElecteur, char nom_fichier[MAX_LENGTH]);      // insertion d'électeurs à l'aide d'un fichier .txt
//----------------------------------------------------

T_Electeur creationelecteur(void);
void afficheliste(T_Electeur tElecteur);
void ajoutelecteur(T_Electeur *tElecteur, char nom[MAX_LENGTH], long cin_num, int choix );
int comptelecteur(T_Electeur tElecteur);
int trouvelecteur(T_Electeur tElecteur, long cin_num);
void supprimelecteur(T_Electeur *tElecteur,long cin_num);
void decoupeliste(T_Electeur tElecteur,T_Electeur *gauche,T_Electeur *droite,T_Electeur *blanc);
void triliste(T_Electeur tElecteur);                                    // tri à bulles
T_Electeur fusionlistes(T_Electeur tElecteur, T_Electeur tElecteur1);
int compteGD(T_Electeur tElecteur);
void libereliste(T_Electeur tElecteur);

#endif //TP3_TP3_H



