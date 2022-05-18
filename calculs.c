#include "structures.h"

//la fonction calculerChemin renvoie le nombre de tuiles du chemin
//je me déplace d'abord sur la ligne puis sur la colonne
int calculerChemin(t_coords tab_chemin[10], t_coords positionInitiale, t_coords positionFinale, int pm)
{
    int nbreTuilesSurLigne = 1;
    int nbreTuilesSurColonne = 0;
    int nbreTuilesSurChemin = 1;
    tab_chemin[0].numeroLigne = positionInitiale.numeroLigne;
    tab_chemin[0].numeroColonne = positionInitiale.numeroColonne;

    int deplacementHorizontal = positionFinale.numeroColonne - positionInitiale.numeroColonne; //nbre de déplacements (d'une case) hrizontaux

    int deplacementVertical = positionFinale.numeroLigne - positionInitiale.numeroLigne; //nbre de déplacements (d'une case) verticaux

    //si la position finale est égale à la position initiale, pas de déplacement
    if (deplacementHorizontal == 0 && deplacementVertical == 0)
    {
        return 0;
    }

    calculerPremiereTuileDuChemin(tab_chemin, positionInitiale, positionFinale);

    printf("\ndeplacement horizontal = %d", deplacementHorizontal);

    if(deplacementHorizontal == 0)
    {
        nbreTuilesSurChemin = calculerCheminUniquementVertical(tab_chemin, positionInitiale, deplacementVertical, pm);
    }

    else
    {
        nbreTuilesSurChemin = calculerCheminHorizontal(tab_chemin, positionInitiale, deplacementHorizontal, 0, pm);
        if (nbreTuilesSurChemin > 0) //si nbreTuilesSurChemin vaut -1, on ne continue pas
        {
            t_coords positionApresDeplacementHorizontal;
            positionApresDeplacementHorizontal.numeroLigne = tab_chemin[0].numeroLigne;
            positionApresDeplacementHorizontal.numeroColonne = tab_chemin[abs(deplacementHorizontal) - 1].numeroColonne;

            nbreTuilesSurChemin = nbreTuilesSurChemin +
                                  calculerCheminVertical(tab_chemin, positionApresDeplacementHorizontal, deplacementVertical, nbreTuilesSurChemin, pm);
        }


    }


    printf("\nnbre Tuiles  Sur Chemin: %d", nbreTuilesSurChemin) ;


    return nbreTuilesSurChemin;

}

//enregistre dans le tableau tab_chemin (à partir de l'indice indiceTabChemin) un chemin vertical à partir de la position initiale
//et en se déplaçant d'un certain nombre de tuiles. Ce nombre est la valeur du paramètre deplacementVertical, qui peut être positif
//(ddéplacement vers le bas) ou négatif (déplacement vers le haut)
//renvoie le nombre de tuiles du chemin ou -1 si le déplacement nécessite plus de tuiles que la valeur pm
int calculerCheminVertical(t_coords tab_chemin[10], t_coords positionDepart, int deplacementVertical, int indiceTabChemin, int pm)
{
    printf("\ndeplacement vertical = %d", deplacementVertical);

    if (deplacementVertical == 0)
    {
        return 0;
    }

    int nbreTuilesSurColonne = 0;

    if (indiceTabChemin != 0)
    {

        for (int j=indiceTabChemin ; j < indiceTabChemin + abs(deplacementVertical); j++)
        {
            printf("\nl'indice dans tab_chemin pour deplac. vertical est %d", j);
            //je me déplace sur la colonne, c'est le numéro de ligne qui change
            tab_chemin[j].numeroLigne = tab_chemin[j - 1].numeroLigne + deplacementVertical/abs(deplacementVertical);
            tab_chemin[j].numeroColonne = positionDepart.numeroColonne;
            nbreTuilesSurColonne ++;
            if (nbreTuilesSurColonne > pm)
            {
                printf("\ndeplacement impossible, vous avez depasse la pm %d", pm);
                return -1;
            }
        }

    }

    printf("\nnbre Tuiles du chemin en vertical : %d", nbreTuilesSurColonne);

    return nbreTuilesSurColonne;
}


int calculerCheminUniquementVertical(t_coords tab_chemin[10], t_coords positionDepart, int deplacementVertical, int pm)
{
       if (deplacementVertical == 0)
    {
        return 0;
    }

    int nbreTuilesSurColonne = 1; //la premiere tuile est déjà calculée




    for (int j=1 ; j < abs(deplacementVertical); j++) //il faut démarrer à 1 car sinon tab_chemin[j - 1] n'est pas défini
    {

        //je me déplace sur la colonne, c'est le numéro de ligne qui change
        tab_chemin[j].numeroLigne = tab_chemin[j - 1].numeroLigne + deplacementVertical/abs(deplacementVertical);
        tab_chemin[j].numeroColonne = positionDepart.numeroColonne;
        nbreTuilesSurColonne ++;
        if (nbreTuilesSurColonne > pm)
        {
            printf("\ndeplacement impossible, vous avez depasse la pm %d", pm);
            return -1;
        }

    }

    printf("\nnbre Tuiles du chemin en vertical : %d", nbreTuilesSurColonne);

    return nbreTuilesSurColonne;
}


//enregistre dans le tableau tab_chemin (à partir de l'indice indiceTabChemin) un chemin horizontal à partir de la position initiale
//et en se déplaçant d'un certain nombre de tuiles. Ce nombre est la valeur du paramètre deplacementHorizontal, qui peut être positif
//(ddéplacement vers la droite) ou négatif (déplacement vers la gauche)
//renvoie le nombre de tuiles du chemin ou -1 si le déplacement nécessite plus de tuiles que la valeur pm
int calculerCheminHorizontal(t_coords tab_chemin[10], t_coords positionDepart, int deplacementHorizontal, int indiceTabChemin, int pm)
{
    if (deplacementHorizontal == 0)
    {
        return 0;
    }

    int nbreTuilesEnDeplacementHorizontal = 1;
    for (int i=indiceTabChemin +1; i < indiceTabChemin + abs(deplacementHorizontal); i++)
    {
        //      je me déplace sur la ligne, c'est le numéro de colonne qui change
        tab_chemin[i].numeroLigne = positionDepart.numeroLigne;


        tab_chemin[i].numeroColonne = tab_chemin[i - 1].numeroColonne  + deplacementHorizontal/abs(deplacementHorizontal);  //deplacementHorizontal/abs(deplacementHorizontal) vaut 1 ou -1 suiant que deplacementHorizontal est positif ou négatif


        nbreTuilesEnDeplacementHorizontal ++;
        if (nbreTuilesEnDeplacementHorizontal > pm)
        {
            printf("\ndeplacement impossible, vous avez depasse la pm %d", pm);
            return -1;
        }
    }

    printf("\nnbre Tuiles du chemin en horizontal : %d", nbreTuilesEnDeplacementHorizontal);

    return nbreTuilesEnDeplacementHorizontal;
}

calculerPremiereTuileDuChemin(t_coords tab_chemin[10], t_coords positionInitiale, t_coords positionFinale)
{

    int deplacementHorizontal = positionFinale.numeroColonne - positionInitiale.numeroColonne; //nbre de déplacements (d'une case) hrizontaux

    int deplacementVertical = positionFinale.numeroLigne - positionInitiale.numeroLigne; //nbre de déplacements (d'une case) verticaux

    if (deplacementHorizontal != 0){
        tab_chemin[0].numeroLigne = positionInitiale.numeroLigne;
        tab_chemin[0].numeroColonne = positionInitiale.numeroColonne + deplacementHorizontal/abs(deplacementHorizontal);
    }


    else //il faut commencer à se déplacer en vertical
    {

        tab_chemin[0].numeroColonne = positionInitiale.numeroColonne;

        tab_chemin[0].numeroLigne = positionInitiale.numeroLigne + deplacementVertical/abs(deplacementVertical);

    }

    printf("\n la premiere tuile est ligne %d, colonne %d", tab_chemin[0].numeroLigne, tab_chemin[0].numeroColonne);

}

//la fonction calculerChemin renvoie le nombre de tuiles du chemin
//je me déplace d'abord sur la ligne puis sur la colonne; mais s'il y a un obstacle
int calculerCheminAvecObstacle(t_coords tab_chemin[10], t_tuile terrain[NYMAP][NXMAP], t_coords positionInitiale, t_coords positionFinale)
{
}
