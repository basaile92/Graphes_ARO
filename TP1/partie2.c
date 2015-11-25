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

int i, nbMax;
tNomSommet nom;
printf("Liste des sommets n'ayant pas de voisins:\n");
for(i = 0; i < grapheNbSommets(graphe); i++)
{
	if(grapheNbVoisinsSommet(graphe, i)== 0)
	{
		grapheRecupNomSommet( graphe, i, nom);
    printf("%s\n", nom);
	}
}

nbMax=0;
printf("Liste des sommets ayant le plus de voisins:\n");
for(i = 0; i < grapheNbSommets(graphe); i++)
{
    if(grapheNbVoisinsSommet(graphe, i) > nbMax)
        nbMax= grapheNbVoisinsSommet(graphe, i);
}

for(i = 0; i < grapheNbSommets(graphe); i++)
{
    if(grapheNbVoisinsSommet(graphe, i) == nbMax)
    {
      grapheRecupNomSommet(graphe, i, nom);
      printf("%s\n", nom);

    }
}


//On libere la mémoire occupee par le graphe
  grapheLibere(graphe);
  exit(EXIT_SUCCESS);
}
