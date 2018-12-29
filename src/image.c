#include <stdio.h>
#include <stdlib.h>
#include "image.h"

// fonction d'initialisation d'image
void initializeImage(FILE *i, Image image){
	char hauteur[3];
	char largeur[3];

	fscanf(i,"%s",image.code);
	fscanf(i,"%s",hauteur);
	fscanf(i,"%s",largeur);
	image.hauteur = atoi(hauteur);
	image.largeur = atoi(largeur);

//alloue assez de place à l'image
	*image.pixels = malloc(3*image.hauteur*image.largeur*sizeof(unsigned char));
	if (image.pixels==NULL) {
		fprintf(stderr,"Not enough memory!\n");
		exit(1);
	}
}