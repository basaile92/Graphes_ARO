#include <stdio.h>
#include <stdlib.h>
#include "sys/wait.h"
#include <string.h>
#include "graphe.h"
typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];

void plusCourteChaine(tGraphe graphe, tNomSommet nom, tNumeroSommet pred[MAX_SOMMETS])
{
  int d[MAX_SOMMETS];
  tFileSommets file;
  int i;
  tTabCouleurs tabCouleurs;
  tNumeroSommet s, x, y;

    s = grapheChercheSommetParNom(graphe, nom);
    file = fileSommetsAlloue();
    for(i = 0; i <= grapheNbSommets(graphe) - 1; i++)
    {

      if(i != s)
        tabCouleurs[i] = BLEU;
    }
    d[s]=0;
    tabCouleurs[s] = VERT;
    fileSommetsEnfile(file, s);
    while(!fileSommetsEstVide(file))
    {

      x = fileSommetsDefile(file);
      for(i = 0; i <= grapheNbVoisinsSommet(graphe, x) - 1; i++)
      {

        y = grapheVoisinSommetNumero(graphe, x, i);
        if(tabCouleurs[y] == BLEU)
        {

          tabCouleurs[y] = VERT;
          fileSommetsEnfile(file, y);
          d[y] = d[x] + 1;
          pred[y] = x;
        }

      }
      tabCouleurs[x] = ROUGE;
    }

}


void graphe2visuPlusCourtsChemins(tGraphe graphe, char *outfile, tNumeroSommet depart, tNumeroSommet pred[MAX_SOMMETS]) {
  FILE *fic;
  char commande[80];
  char dotfile[80]; /* le fichier dot pour cr´eer le ps */
  int ret, i, j, k, l;
  tNomSommet actuel, prochain;
  char* couleur, *couleurarete;
  /* on va cr´eer un fichier pour graphviz, dans le fichier "outfile".dot */
  strcpy(dotfile, outfile);
  strcat(dotfile, ".dot");
  fic = fopen(dotfile, "w");
  if (fic==NULL)
    halt ("Ouverture du fichier %s en ´ecriture impossible\n", dotfile);

  fprintf(fic, "graph {\n");

  for(i = 0; i <= grapheNbSommets(graphe) - 1; i++)
  {
    couleur = "black";
    if(i == depart)
    {
      couleur = "blue";
    }
    grapheRecupNomSommet(graphe, i, actuel);
    fprintf(fic, "%s [color=%s];\n", actuel, couleur);
  }
  for(j = 0; j < grapheNbArcs(graphe) ; j++)
  {
        k=grapheRecupArcNumero(graphe, j).orig;
        l=grapheRecupArcNumero(graphe, j).dest;
        couleurarete = "black";
        if((k == depart && pred[l] == depart )|| (pred[k] == l && l == depart))
        {

          couleurarete = "blue";
        }
        grapheRecupNomSommet(graphe, k, actuel);
        grapheRecupNomSommet(graphe, l, prochain);
        fprintf(fic, " %s -- %s [color=%s];\n", actuel, prochain, couleurarete);
  }
  fprintf(fic, "}\n");

  fclose(fic);
  sprintf(commande, "dot -Tps %s -o %s", dotfile, outfile);
  ret = system(commande);
  if (WEXITSTATUS(ret))
    halt("La commande suivante a ´echou´e\n%s\n", commande);
}


int main(int argc, char *argv[]) {

  tGraphe graphe;
  tNumeroSommet pred[MAX_SOMMETS];
  if (argc < 3) {
    halt("Usage : %s FichierGraphe NomSommetDeBase\n", argv[0]);
  }

  graphe = grapheAlloue();
  grapheChargeFichier(graphe,  argv[1]);


  plusCourteChaine(graphe, argv[2], pred);
  graphe2visuPlusCourtsChemins(graphe, "img/visu.ps", grapheChercheSommetParNom(graphe, argv[2]), pred);


  grapheLibere(graphe);
  exit(EXIT_SUCCESS);

}
