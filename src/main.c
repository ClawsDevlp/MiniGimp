#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "lut.h"

void createHistogram(Image *histogramme, char nom[]);

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
	fclose(i);
	Lut lut;
	char nomImage[200] = "output.ppm";
	initializeLut(&lut);


	// Gestion des options de commande
	for(int i=2; i<argc; i++){
		if(strcmp(argv[i], "-histo") == 0){
			createHistogram(image,"histogramme_DEBUT");
		}
		if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-help") == 0){
			printf("\n- ADDLUM (+ paramètre) : permet d'augmenter la luminosité de l'image.\n- DIMLUM (+ paramètre) : permet de diminuer la luminosité de l'image.\n- ADDCON (+ paramètre) : permet d'augmenter le contraste de l'image.\n- DIMCON (+ paramètre) : permet de diminuer le contraste de l'image.\n- INVERT : permet d'inverser les couleurs de l'image.\n- SEPIA : permet de créer un effet sépia.\n- NOIRBLANC : permet de créer un effet noir et blanc.\n- SEUIL : permet de créer un effet de seuil.\n");
		}
	}
	for(int i=2; i<argc; i++){
		if(strcmp(argv[i],"ADDLUM") == 0) { addLum(&lut, atoi(argv[i+1])); }
		if(strcmp(argv[i],"DIMLUM") == 0) { dimLum(&lut, atoi(argv[i+1])); }
		if(strcmp(argv[i],"ADDCON") == 0) { 
			if(atoi(argv[i+1]) > 255){
				printf("Attention, vous avez mis un paramêtre supérieur à 255. Le contraste obtenu n'est pas garanti.\n");
			}
			addCon(&lut, atoi(argv[i+1])); 
		}
		if(strcmp(argv[i],"DIMCON") == 0) { 
			if(atoi(argv[i+1]) > 255){
				printf("Attention, vous avez mis un paramêtre supérieur à 255. Le contraste obtenu n'est pas garanti.\n");
			}
			dimCon(&lut, atoi(argv[i+1])); 
		}
		if(strcmp(argv[i],"INVERT") == 0) { invert(&lut); }
		if(strcmp(argv[i],"SEPIA") == 0) { sepia(image); }
		if(strcmp(argv[i],"MIROIR") == 0) { miroir(image); }
		if(strcmp(argv[i],"SEUIL") == 0) { noirEtBlanc(image); seuil(&lut); }
		if(strcmp(argv[i],"NOIRBLANC") == 0) { noirEtBlanc(image); }
		if(strcmp(argv[i],"-o") == 0) { 
			nomImage[0] = '\0';
			strcpy(nomImage, argv[i+1]);
		}
	}


	// Modification de l'image
	appliqueLut(image, &lut);
	newFileImage(nomImage, image);
	createHistogram(image, "histogramme_FIN");
	freeImage(image);

	return EXIT_SUCCESS;
}




// Creation de l'histogramme
void createHistogram(Image *image, char nomHisto[]){
	int moyenneValeurGris[256];
	for(int j=0; j<256; j++){
		moyenneValeurGris[j] = 0;
	}

    for(int i=0; i<image->hauteur; i++){
		for (int j=0; j<image->largeur; j++){
			moyenneValeurGris[image->pixels[image->largeur*3*i+3*j+0]]++;
			moyenneValeurGris[image->pixels[image->largeur*3*i+3*j+1]]++;
			moyenneValeurGris[image->pixels[image->largeur*3*i+3*j+2]]++;
		}
	}

	int max = 0;

	for(int h=0; h<256; h++){
		if(max < moyenneValeurGris[h]){
			max = moyenneValeurGris[h];
		}
	}

	Image *histo;
	histo = malloc(sizeof(Image) + 3*1920*1080*sizeof(unsigned char));
	strcpy(histo->code,"P6");
	histo->largeur = 1920;
	histo->hauteur = 1080;
	histo->profondeur = 255;

	float coeffH = 1080.0/max;
	float coeffL = 256/1920.0;

	for(int i=0; i<histo->hauteur; i++){
		for (int j=0; j<histo->largeur; j++){
			int indiceTab = (int)j*coeffL;
			if (i < histo->hauteur - moyenneValeurGris[indiceTab]*coeffH) {
				histo->pixels[histo->largeur*3*i+3*j+0] = 255;
				histo->pixels[histo->largeur*3*i+3*j+1] = 255;
				histo->pixels[histo->largeur*3*i+3*j+2] = 255;
			} else {
				histo->pixels[histo->largeur*3*i+3*j+0] = 0;
				histo->pixels[histo->largeur*3*i+3*j+1] = 0;
				histo->pixels[histo->largeur*3*i+3*j+2] = 0;
			}
		}
	}

	newFileImage(nomHisto, histo);
	freeImage(histo);
}