#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "lut.h"

void createHistogram(Image *image, char histoName[]);


int main(int argc, char *argv[]){
	// If no argument, can't charge file
	if (argc < 1) {
		printf("Une image est nécessaire pour continuer \n");
		return EXIT_FAILURE;
	}

	// Openning the file
	FILE *i = fopen(argv[1], "r");
	if (i == NULL) {
		printf("L'image %s n'a pas pu être ouverte \n", argv[1]);
		return EXIT_FAILURE;
	};


	// Creating variables
	Image *image = initializeImage(i);
	fclose(i);
	Lut lut;
	char imageName[200] = "images/output.ppm";
	initializeLut(&lut);


	// Managing options
	for (int i=2; i < argc; i++) {
		if (strcmp(argv[i], "-histo") == 0) {
			createHistogram(image, "images/histo_DEBUT");
		}
		if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-help") == 0){
			printf("\n- ADDLUM (+ paramètre) : augmente la luminosité de l'image.\n");
			printf("- DIMLUM (+ paramètre) : diminue la luminosité de l'image.\n");
			printf("- ADDCON (+ paramètre) : augmente le contraste de l'image (paramètre entre 0 et 255).\n");
			printf("- DIMCON (+ paramètre) : diminue le contraste de l'image (paramètre entre 0 et 255).\n");
			printf("- INVERT : inverse les couleurs de l'image.\n");
			printf("- SEPIA : applique un effet sépia.\n");
			printf("- MIROIR : applique un effet miroir.\n");
			printf("- NOIRBLANC : applique un effet noir et blanc.\n");
			printf("- SEUIL : applique un effet de seuil.\n\n");
		}
	}
	
	for (int i=2; i < argc; i++) {
		if (strcmp(argv[i], "ADDLUM") == 0) { addLum(&lut, atoi(argv[i+1])); }
		if (strcmp(argv[i], "DIMLUM") == 0) { dimLum(&lut, atoi(argv[i+1])); }
		if (strcmp(argv[i], "ADDCON") == 0) { 
			if (atoi(argv[i+1]) > 255) {
				printf("Attention, vous avez mis un paramêtre supérieur à 255. Le contraste obtenu n'est pas garanti.\n");
			}
			addCon(&lut, atoi(argv[i+1])); 
		}
		if (strcmp(argv[i], "DIMCON") == 0) { 
			if (atoi(argv[i+1]) > 255) {
				printf("Attention, vous avez mis un paramêtre supérieur à 255. Le contraste obtenu n'est pas garanti.\n");
			}
			dimCon(&lut, atoi(argv[i+1])); 
		}
		if (strcmp(argv[i], "INVERT") == 0) { invert(&lut); }
		if (strcmp(argv[i], "SEPIA") == 0) { sepia(image); }
		if (strcmp(argv[i], "MIROIR") == 0) { mirror(image); }
		if (strcmp(argv[i], "SEUIL") == 0) { blackWhite(image); seuil(&lut); }
		if (strcmp(argv[i], "NOIRBLANC") == 0) { blackWhite(image); }
		if (strcmp(argv[i], "-o") == 0) { 
			imageName[0] = '\0';
			strcpy(imageName, argv[i+1]);
		}
	}
	// END managing options


	// Image modification
	applyLut(image, &lut);
	newFileImage(imageName, image);
	for (int i=2; i < argc; i++) {
		if (strcmp(argv[i], "-histo") == 0) {
			createHistogram(image, "images/histo_FIN");
		}
	}
	freeImage(image);

	return EXIT_SUCCESS;
}



// Creating histogram
void createHistogram(Image *image, char histoName[]){
	int grayValuesAverage[256];
	int maxValue = 0;

	// Creating and filling of the gray values average table
	for (int j=0; j < 256; j++) {
		grayValuesAverage[j] = 0;
	}

    for (int i=0; i < image->height; i++) {
		for (int j=0; j < image->width; j++) {
			grayValuesAverage[image->pixelData[image->width*3*i+3*j+0]]++;
			grayValuesAverage[image->pixelData[image->width*3*i+3*j+1]]++;
			grayValuesAverage[image->pixelData[image->width*3*i+3*j+2]]++;
		}
	}

	// Looking for the maximum of the gray values
	for (int h=0; h < 256; h++) {
		if (maxValue < grayValuesAverage[h]) {
			maxValue = grayValuesAverage[h];
		}
	}

	// Creating the histogram image
	Image *histo;
	histo = malloc(sizeof(Image) + 3*1920*1080*sizeof(unsigned char));
	strcpy(histo->format, "P6");
	histo->width = 1920;
	histo->height = 1080;
	histo->maxValue = 255;

	float coeffH = 1080.0/maxValue;
	float coeffL = 256/1920.0;

	// Drawing the histogram
	for (int i=0; i < histo->height; i++) {
		for (int j=0; j < histo->width; j++) {
			int indiceTab = (int)j*coeffL;

			if (i < histo->height - grayValuesAverage[indiceTab]*coeffH) {
				histo->pixelData[histo->width*3*i+3*j+0] = 255;
				histo->pixelData[histo->width*3*i+3*j+1] = 255;
				histo->pixelData[histo->width*3*i+3*j+2] = 255;
			} else {
				histo->pixelData[histo->width*3*i+3*j+0] = 0;
				histo->pixelData[histo->width*3*i+3*j+1] = 0;
				histo->pixelData[histo->width*3*i+3*j+2] = 0;
			}
		}
	}

	newFileImage(histoName, histo);
	freeImage(histo);
}