#include <stdio.h>
#include <stdlib.h>
#include "sys/wait.h"
#include <string.h>
#include "graphe.h"
typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];

int estVoisin(tGraphe graphe,tNumeroSommet a, tNumeroSommet b)
{
  int i;
  for(i = 0; i < grapheNbVoisinsSommet(graphe, a); i++)
  {
    if(b == grapheVoisinSommetNumero(graphe, a, i))
    {
      return 0 == 0;
    }
  }
  return 0 == 1;
}


int solutionLab(tGraphe graphe, tNomSommet entree, tNomSommet sortie, tTabCouleurs tabCouleurs)
{

  int i, pasVoisinBleu;
  tNumeroSommet numE, numS, x, y, varChemin;
  tNomSommet nomVarChemin, nom1,nom2;
  tPileSommets pile, pileChemin;

  pile = pileSommetsAlloue();
  pileChemin = pileSommetsAlloue();
  pasVoisinBleu = 1 == 1;
  for(i = 0; i < grapheNbSommets(graphe); i++)
  {

    tabCouleurs[i] = BLEU;
  }
  numE = grapheChercheSommetParNom(graphe, entree);
  numS = grapheChercheSommetParNom(graphe, sortie);
  tabCouleurs[numE] = VERT;
  pileSommetsEmpile(pile, numE);
  while(!pileSommetsEstVide(pile)&& pileSommetsTete(pile) != numS)
  {

    x = pileSommetsTete(pile);
    pasVoisinBleu = 1 == 1;
    for(i = 0; i < grapheNbVoisinsSommet(graphe, x);i++)
    {
      y = grapheVoisinSommetNumero(graphe, x, i);
      if(tabCouleurs[y] == BLEU)
      {

        tabCouleurs[y] = VERT;
        pileSommetsEmpile(pile, y);
        pasVoisinBleu = pasVoisinBleu && 0 == 1;
      }
    }
    if(pasVoisinBleu)
    {

      x = pileSommetsDepile(pile);
      tabCouleurs[x] = ROUGE;
    }
  }
  if(!pileSommetsEstVide(pile)&& pileSommetsTete(pile) == numS)
  {

    while(!pileSommetsEstVide(pile))
    {

      varChemin = pileSommetsDepile(pile);
      pileSommetsEmpile(pileChemin, varChemin);

      if(!pileSommetsEstVide(pile))
      {
        while(!estVoisin(graphe, pileSommetsTete(pile), varChemin))
        {

          pileSommetsDepile(pile);
        }
      }
    }

    while(!pileSommetsEstVide(pileChemin))
    {
      grapheRecupNomSommet(graphe, pileSommetsDepile(pileChemin), nomVarChemin);
      printf("%s\n", nomVarChemin );
    }
    return 0 == 0;
  }
  return 0 == 1;
}




int main(int argc, char *argv[]) {

  tGraphe graphe;
  tTabCouleurs tabCouleurs;
  if (argc < 4) {
    halt("Usage : %s FichierGraphe SommetEntree SommetSortie\n", argv[0]);
  }

  graphe = grapheAlloue();

  grapheChargeFichier(graphe,  argv[1]);

  if(!solutionLab(graphe, argv[2], argv[3],tabCouleurs))
  {
    printf("Il n'y a pas de chemin dans le labyrinthe.\n");
  }

  grapheLibere(graphe);
  exit(EXIT_SUCCESS);

}
