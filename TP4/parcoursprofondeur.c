#include <stdio.h>
#include <stdlib.h>
#include "sys/wait.h"
#include <string.h>
#include "graphe.h"
typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];

void graphe2visuCouleurs(tGraphe graphe, char *outfile, tTabCouleurs tabCouleurs) {
  FILE *fic;
  char commande[80];
  char dotfile[80]; /* le fichier dot pour cr´eer le ps */
  int ret, i, j;
  char isdigraph, *isdigraph2, *color;
  tNomSommet actuel, prochain, sommet;
  /* on va cr´eer un fichier pour graphviz, dans le fichier "outfile".dot */
  strcpy(dotfile, outfile);
  strcat(dotfile, ".dot");
  fic = fopen(dotfile, "w");
  if (fic==NULL)
    halt ("Ouverture du fichier %s en ´ecriture impossible\n", dotfile);

  isdigraph = '-';
  isdigraph2 = "graph {";

  if(grapheEstOriente(graphe))
  {
    isdigraph = '>';
    isdigraph2 = "digraph {";
  }

  fprintf(fic, "%s\n", isdigraph2 );

  for(i = 0; i<=grapheNbSommets(graphe) - 1; i++)
  {

    grapheRecupNomSommet(graphe, i, sommet);
    if(tabCouleurs[i] == ROUGE)
    {
      color = "red";
    }else if(tabCouleurs[i] == BLEU)
    {
      color = "blue";
    }else if(tabCouleurs[i] == VERT)
    {
      color = "green";
    }
    fprintf(fic, "%s [color=%s]\n", sommet, color);
  }

  for(i = 0; i <= grapheNbArcs(graphe) - 1; i++)
  {
        grapheRecupNomSommet(graphe, grapheRecupArcNumero(graphe, i).orig, actuel);
        grapheRecupNomSommet(graphe, grapheRecupArcNumero(graphe, i).dest, prochain);
        fprintf(fic, " %s -%c %s\n", actuel, isdigraph, prochain);
  }
fprintf(fic, "}\n");

  fclose(fic);
  sprintf(commande, "dot -Tps %s -o %s", dotfile, outfile);
  ret = system(commande);
  if (WEXITSTATUS(ret))
    halt("La commande suivante a ´echou´e\n%s\n", commande);
}



void en_profondeur(tGraphe graphe, tNomSommet nom, tTabCouleurs tabCouleurs)
{

  int i, pasVoisinBleu, cpt;
  tNumeroSommet num, x, y;
  tPileSommets pile;
  char * fichier;

  pile = pileSommetsAlloue();
  cpt=0;
  fichier=malloc(sizeof(char[20]));
  pasVoisinBleu = 1 == 1;
  for(i = 0; i < grapheNbSommets(graphe); i++)
  {

    tabCouleurs[i] = BLEU;
  }
  num = grapheChercheSommetParNom(graphe, nom);
  tabCouleurs[num] = VERT;
  graphe2visuCouleurs(graphe, "img/visu0.ps", tabCouleurs);
  pileSommetsEmpile(pile, num);
  while(!pileSommetsEstVide(pile))
  {

    x = pileSommetsTete(pile);
    pasVoisinBleu = 1 == 1;
    for(i = 0; i < grapheNbVoisinsSommet(graphe, x);i++)
    {
      y = grapheVoisinSommetNumero(graphe, x, i);
      if(tabCouleurs[y] == BLEU)
      {

        tabCouleurs[y] = VERT;
        pasVoisinBleu = pasVoisinBleu && 0 == 1;
        pileSommetsEmpile(pile, y);
      }
    }
    if(pasVoisinBleu)
    {

      x = pileSommetsDepile(pile);
      tabCouleurs[x] = ROUGE;
    }
    cpt++;

    sprintf(fichier, "img/visu%d.ps",cpt );

    graphe2visuCouleurs(graphe, fichier, tabCouleurs);

  }
}




int main(int argc, char *argv[]) {

  tGraphe graphe;
  tTabCouleurs tabCouleurs;
  if (argc < 3) {
    halt("Usage : %s FichierGraphe NomSommetDeBase\n", argv[0]);
  }

  graphe = grapheAlloue();

  grapheChargeFichier(graphe,  argv[1]);

  en_profondeur(graphe, argv[2], tabCouleurs);

  grapheLibere(graphe);
  exit(EXIT_SUCCESS);

}
