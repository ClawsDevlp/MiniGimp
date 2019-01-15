#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

// Initialisation de l'image
Image * initializeImage(FILE *i){
	Image *image;

	char code[2];
	int hauteur;
	int largeur;

	fscanf(i,"%s\n",code);
	fscanf(i,"%d",&hauteur);
	fscanf(i,"%d\n",&largeur);

	//alloue assez de place à l'image
	image = malloc(sizeof(Image) + 3*hauteur*largeur*sizeof(unsigned char));
	if (image==NULL) {
		fprintf(stderr,"Not enough memory!\n");
		exit(1);
	}

	strcpy(image->code, code);
	fscanf(i,"%d\n",&image->profondeur);
	image->hauteur = hauteur;
	image->largeur = largeur;
	
	fread(image->pixels, sizeof (unsigned char), largeur*hauteur*3, i);

	return image;
}

// Ecriture de la nouvelle image
int newFileImage(char nom[], Image *image){
	FILE* fichier = NULL;
	char new[40] = "images/";
	strcat(new,nom);
	fichier = fopen(new, "w");

	if (fichier != NULL){
		fprintf(fichier,"%s\n",image->code);
		fprintf(fichier,"%d %d\n",image->hauteur, image->largeur);
		fprintf(fichier,"%d\n",image->profondeur);
		//fprintf(fichier,"%s","#Made by Andrea & Clara");
		fwrite(image->pixels,sizeof(unsigned char),image->largeur*image->hauteur*3,fichier);
		fclose(fichier);
	}
	return EXIT_SUCCESS;
}

// Libere l'espace de l'image
void freeImage(Image *image) {
  if(image != NULL) {
    image->largeur  = 0;
    image->hauteur = 0;
	
	free(image);
	}
}
