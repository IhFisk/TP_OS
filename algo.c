/*********************************
 *                               *
 *  Algorithmes de remplacement  *
 *  de page                      *
 *                               *
 *  Auteur : Hugo MOHAMED        *
 *                               *
 ********************************/

#include <stdio.h>
#include <stdlib.h>

#include "liste.h"

void usage(char* s);

// First In First Out
int fifo(int nbAcces,int *valide, int *acces, int caseRAM);

// Less Rencently Use
int lru();

// Algorithme de l'Horloge
int horloge();

// Optimal
int optimal();

int main(int argc, char* argv[])
{
    if(argc < 5)
      usage(argv[0]);

    int algo = atoi(argv[1]);
    int caseRAM = atoi(argv[2]);

	if(caseRAM < 1)
	{
		fprintf(stderr,"Erreur, nombre de case invalide\n");
		exit(EXIT_FAILURE);
	}

    FILE* acces_mem = NULL;
	acces_mem = fopen(argv[4],"r");
    if(acces_mem == NULL)
    {
		fprintf(stderr,"Erreur lors de l'ouverture de <<%s>>\n",argv[4]);
		exit(EXIT_FAILURE);
    }

    int nbPage;
	int nbAcces;
	int nbDefPage = 0;
    int *acces;
    int *valide;
    int *b_acces;
    liste pageRAM = liste_vide();
    int i = 0;
    int page;
    char ligne[10];

    fgets(ligne,10,acces_mem);
	nbAcces = atoi(ligne);
	fgets(ligne,10,acces_mem);
    nbPage = atoi(ligne);

	acces = (int*)malloc(nbAcces * sizeof(int));
	valide = (int*)malloc(nbPage * sizeof(int));
	if(acces == NULL || valide == NULL)
	{
		fprintf(stderr,"Erreur lors de l'allocation mémoire.\n");
		exit(EXIT_FAILURE);
	}

	// On remplit le tableau des acces mémoire
	while(fgets(ligne,10,acces_mem) != NULL)
	{
		acces[i] = atoi(ligne);
		printf("%d ",acces[i]);
		i++;
	}
	printf("\n");
	// On initialise valide a 0
	for(i=0;i<caseRAM;i++)
		valide[i] = 0;

    // FIFO
    if(algo == 1)
    {
		nbDefPage = fifo(nbAcces, valide, acces, caseRAM);
    }

    // LRU
    else if(algo == 2)
    {

    }

    // Horloge
    else if(algo == 3)
    {

    }

    // optimal
    else if(algo == 4)
    {

    }

	printf("\n");
    for(i=0;i<nbAcces;i++)
    {
		if(valide[i])
			fprintf(stdout,"%d ", acces[i]);
    }
	printf("\nDefauts de page : %d\n", nbDefPage);

	fclose(acces_mem);

    exit(EXIT_SUCCESS);
}


void usage(char* s)
{
    fprintf(stderr,"Usage : %s <numéro algo> <nb case RAM> <mode affichage> <fichier acces>\n",s);
    fprintf(stderr,"Algo :\n    1) FIFO\n    2) LRU\n    3) Horloge\n    4) Optimal\n");
    fprintf(stderr,"Mode affichage :\n    d: debug\n    c: classique\n");

    exit(EXIT_FAILURE);
}


int fifo(int nbAcces,int *valide, int *acces, int caseRAM)
{
	int i, j=0, nbDefPage=0;
	int page;
	liste pageRAM = liste_vide();

	// on parcours les acces mémoire
	for(i=0;i<nbAcces;i++)
	{
		page = acces[i];

		// On test si la page n'est pas déjà en RAM
		if(valide[page] == 0)
		{
			valide[page] = 1;

			// Si on a encore de la place en RAM
			if(j < caseRAM)
			{
				pageRAM = inserer_element_liste(pageRAM,page);
				j++;
			}

			// Si on a plus de place -> defaut de page
			else
			{
				nbDefPage++;

				// Remplacement FIFO
				valide[renvoie_premier_liste(pageRAM)] = 0;
				pageRAM = supprimer_element_liste(pageRAM);
				pageRAM = inserer_element_liste(pageRAM,page);
			}
		}

	}
	free(pageRAM);
	return nbDefPage;
}
