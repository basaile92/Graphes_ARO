#include <stdio.h>
#include <stdlib.h>
#include "sys/wait.h"
#include <string.h>
#include "graphe.h"

int ChercheChemin(tGraphe arbre, tNomSommet nomEntree, tNomSommet nomSortie, tPileSommets chemin) {
	tNumeroSommet entree, noeud, voisin;
	tPileSommets pile;

  pile = pileSommetsAlloue();
	noeud = entree = grapheChercheSommetParNom(arbre, nomEntree);
	pileSommetsEmpile(pile, noeud);
	pileSommetsEmpile(chemin, grapheChercheSommetParNom(arbre, nomSortie));

	while(!pileSommetsEstVide(pile)) {
		for(int i=0; i<grapheNbVoisinsSommet(arbre, noeud); i++) {
			voisin = grapheVoisinSommetNumero(arbre, noeud, i);
			pileSommetsEmpile(pile, voisin);
			if(pileSommetsTete(chemin) == voisin) {
				pileSommetsEmpile(chemin, voisin);
			}
		}
    noeud = pileSommetsDepile(pile);
	}

	return pileSommetsTete(chemin) == entree;
}

tPileSommets ReversePile(tPileSommets pile) {



	return pile;
}

int main(int argc, char *argv[]) {
	tGraphe graphe;
	tPileSommets chemin;

	if (argc < 2)
		halt("Usage : %s FichierGraphe\n", argv[0]);

  chemin = pileSommetsAlloue();
	graphe = grapheAlloue();
	grapheChargeFichier(graphe,  argv[1]);

	if(!ChercheChemin(graphe, "entree", "sortie", chemin))
		printf("Il n'y a pas de chemin dans le labyrinthe.");
	chemin = ReversePile(chemin);

	grapheLibere(graphe);
	exit(EXIT_SUCCESS);
}
