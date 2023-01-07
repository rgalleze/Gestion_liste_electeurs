//
// Created by pllsj on 28/03/2022.
//

#include "tp3.h"
#include <stdio.h>

int main() {

    T_Electeur liste = NULL;
    T_Electeur gauche = NULL;
    T_Electeur droite = NULL;
    T_Electeur blanc = NULL;
    T_Electeur fusion = NULL;


    long cin;                                                                                                 // ici sont définies les variables utiles lors de la navigation du menu (ex : selection = choix de l'utilisateur)
    int position_electeur,selection;
    char sous_selection,fname[MAX_LENGTH];
    float pourcentage_gauche;
    do{                                                                                                       // tant que selection !=8, on reste dans le menu
        printf("\n(0. Ajouter des electeurs a partir d'un fichier texte)");
        printf("\n1. Ajouter des electeurs");
        printf("\n2. Supprimer un electeur par CIN");
        printf("\n3. Rechercher un electeur");
        printf("\n4. Afficher la liste des electeurs");
        printf("\n5. Calculer le nombre des electeurs");
        printf("\n6. Decouper la liste en trois sous-listes selon les choix: droite, gauche et blanc");
        printf("\n   a. Trier les sous-listes");
        printf("\n   b. Afficher les sous-listes");
        printf("\n   c. Fusionner les deux sous-listes : gauche et droite");
        printf("\n   d. Calculer les pourcentages de gauche et de droite pour le 2eme tour");
        printf("\n   d. Quitter");
        printf("\n7. Liberer les listes");
        printf("\n8. Quitter");
        printf("\nVeuillez saisir votre choix (tapez le numero pour acceder a la sous-liste): ");
        scanf("%d",&selection);
        fflush(stdin);
        switch(selection)
        {

            case 0 :

                printf("\n Nom du fichier : "); // saisir "../liste.txt" pour utiliser le fichier texte du projet
                scanf("%s", &fname);
                fflush(stdin);
                lecture_fichier(&liste,fname);
                break;

            case 1 :
                ajout(&liste);
                reinitialisation(&fusion);                                      // On s'apprête à mettre à jour fusion
                break;



            case 2 :
                printf("\nSaisir le numero de CIN de l'electeur : ");
                scanf("%ld",&cin);
                supprimelecteur(&liste,cin);
                reinitialisation(&fusion);                                      // On s'apprête à mettre à jour fusion
                break;

            case 3:
                printf("\nSaisir le numero de CIN de l'electeur : ");
                scanf("%ld",&cin);
                position_electeur =  trouvelecteur(liste,cin);                          //on récupère la position de l'électeur et vérifie s'il existe bien
                if (position_electeur==-1) printf("[Electeur introuvable]\n");
                else printf("\nCelui-ci ce trouve a la %dieme position dans la liste.\n",position_electeur);
                break;

            case 4 :
                afficheliste(liste);
                break;

            case 5 :
                printf("Il y a %d electeurs dans la liste.\n", comptelecteur(liste));
                break;

            case 6 :
                reinitialisation(&gauche); // On s'apprete à mettre à jour gauche donc on le réinitialise et libère la mémoire
                reinitialisation(&droite); // On s'apprete à mettre à jour droite
                reinitialisation(&blanc);  // On s'apprete à mettre à jour blanc
                decoupeliste(liste, &gauche, &droite, &blanc);
                do {                                                                            // on ne sort pas du sous-menu tant qu'on ne saisit pas 'e'
                    printf("\nSouhaitez-vous : ");
                    printf("\n   a. Trier les sous-listes");
                    printf("\n   b. Afficher les sous-listes");
                    printf("\n   c. Fusionner les deux sous-listes : gauche et droite");
                    printf("\n   d. Calculer les pourcentages de gauche et de droite pour le 2eme tour");
                    printf("\n   e. Quitter");
                    printf("\nReponse : ");
                    sous_selection = getchar();
                    fflush(stdin);
                    switch (sous_selection) {

                        case 'a':
                            triliste(gauche);
                            triliste(droite);
                            triliste(blanc);
                            break;

                        case 'b':
                            printf("                           LISTE GAUCHE");
                            afficheliste(gauche);
                            printf("\n                            LISTE DROITE");
                            afficheliste(droite);
                            printf("\n                            LISTE BLANC");
                            afficheliste(blanc);
                            break;

                        case 'c':
                            reinitialisation(&fusion);                                      // On s'apprête à mettre à jour fusion
                            fusion = fusionlistes(gauche, droite);
                            printf("\n                            LISTE FUSION");
                            afficheliste(fusion);
                            break;

                        case 'd':
                            if (fusion==NULL)
                            {
                                printf("\nVeuillez effectuer la fusion au prealable (avec une liste non vide). (6.c)\n");
                            }
                            else
                            {
                                pourcentage_gauche =  ((float) 100* (float)compteGD(fusion))/ ((float) comptelecteur(fusion)) ;
                                printf("\nPourcentage gauche : [%3f% ] | Pourcentage droite : [%3f% ] \n", pourcentage_gauche, (100-pourcentage_gauche)); // le % ne s'affiche pas
                            }
                            break;

                        default :
                            break;
                    }
                }while(sous_selection!='e');
                break;

            case 7:
                reinitialisation(&gauche); // On s'apprete à mettre à jour gauche donc on libère la mémoire
                reinitialisation(&droite); // On s'apprete à mettre à jour droite
                reinitialisation(&blanc);  // On s'apprete à mettre à jour blanc
                reinitialisation(&fusion); // On s'apprête à mettre à jour fusion
                reinitialisation(&liste);  // On s'apprête à mettre à jour liste
                break;

            default: break;
        }

    }while(selection != 8);
    printf("\n--->Au revoir.");
    return 0;
}
