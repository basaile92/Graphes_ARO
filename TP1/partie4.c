#include <stdio.h>
#include <stdlib.h>
#include "sys/wait.h"
#include <string.h>
#include "graphe.h"


void graphe2visu(tGraphe graphe, char *outfile) {
  FILE *fic;
  char commande[80];
  char dotfile[80]; /* le fichier dot pour cr´eer le ps */
  int ret, i, j;
  char isdigraph, *isdigraph2;
  tNomSommet actuel, prochain;
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

  for(i = 0; i <= grapheNbSommets(graphe) - 1; i++)
  {
    for(j = 0; j <= grapheNbSuccesseursSommet(graphe, i)-1; j++)
    {
      grapheRecupNomSommet(graphe, i, actuel);
      grapheRecupNomSommet(graphe, grapheSuccesseurSommetNumero(graphe, i, j), prochain);
      fprintf(fic, " %s -%c %s\n", actuel, isdigraph, prochain);
    }
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

  if (argc < 2) {
    halt("Usage : %s FichierGraphe\n", argv[0]);
  }

  graphe = grapheAlloue();

  grapheChargeFichier(graphe,  argv[1]);

  graphe2visu(graphe, "visu.ps");

  grapheLibere(graphe);
  exit(EXIT_SUCCESS);

}
