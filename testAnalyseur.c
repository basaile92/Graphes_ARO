/**********************************************************************
 *testAnalyseur.c
 *
 *  (François lemaire)  <Francois.Lemaire@lifl.fr> 
 * Time-stamp: <2010-10-06 15:06:29 lemaire>
 ***********************************************************************/

/* Ce program prend un nom de graphe en entrée, le charge,
   et l'affiche de façon détaillée.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphe.h"

int main(int argc, char *argv[]) {

  tGraphe graphe;

  if (argc<2) {
    halt("Usage : %s FichierGraphe\n", argv[0]);
  }

//On initialise la graphe  
  graphe = grapheAlloue();
  
//On prend le premier argument de la fonction et on le met dans graphe. On charge le fichier graphe.
  grapheChargeFichier(graphe,  argv[1]);
//On affiche de maniere detaillee le graphe.
  grapheAffiche(graphe);

//On libere la mémoire occupee par le graphe
  grapheLibere(graphe);

  exit(EXIT_SUCCESS);
}
