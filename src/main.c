#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "lut.h"

int main(int argc, char *argv[]){
	if(argc < 1){
		printf("Une image est nécessaire au programme \n");
		return EXIT_FAILURE;
	}

	// Ouverture du fichier
	FILE *i = fopen(argv[1],"r");
	if (i==NULL){
		printf( "L'image n'a pas pu être ouverte %s\n", argv[1] );
		return EXIT_FAILURE;
	};


	// Creation des variables
	Image *image = initializeImage(i);
	Lut lut;
	char nomImage[200] = "output.ppm";
	addLum(&lut,0); //initialiser le LUT pour pas que l'image bug ??


	// Gestion des options de commande
	for(int i=2; i<argc; i++){
		if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-histo") == 0){
			//fonction histogramme
		}
		if(strcmp(argv[i],"ADDLUM") == 0) { addLum(&lut, atoi(argv[i+1])); }
		if(strcmp(argv[i],"DIMLUM") == 0) { dimLum(&lut, atoi(argv[i+1])); }
		if(strcmp(argv[i],"ADDCON") == 0) { addCon(&lut, atoi(argv[i+1])); }
		if(strcmp(argv[i],"DIMCON") == 0) { dimCon(&lut, atoi(argv[i+1])); }
		if(strcmp(argv[i],"INVERT") == 0) { invert(&lut); }
		if(strcmp(argv[i],"SEPIA") == 0) { sepia(&lut); }
		if(strcmp(argv[i],"-o") == 0) { 
			nomImage[0] = '\0';
			strcpy(nomImage, argv[i+1]);
		}
	}


	// Modification de l'image
	appliqueLut(image, &lut);
	newFileImage(nomImage, image);
	freeImage(image);

	fclose(i);

	return EXIT_SUCCESS;
}