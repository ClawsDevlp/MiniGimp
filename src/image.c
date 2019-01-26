#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

// Initialize the image
Image * initializeImage(FILE *i){
	Image *image;

	char format[2];
	int height;
	int width;

	fscanf(i,"%s\n", format);
	fscanf(i,"%d", &width);
	fscanf(i,"%d\n", &height);

	//allocate enough space for the image
	image = malloc(sizeof(Image) + 3*height*width*sizeof(unsigned char));
	if (image == NULL) {
		fprintf(stderr, "Not enough memory!\n");
		exit(1);
	}

	strcpy(image->format, format);
	fscanf(i, "%d\n", &image->maxValue);
	image->height = height;
	image->width = width;
	
	fread(image->pixelData, sizeof(unsigned char), width*height*3, i);

	return image;
}

// Writing of the new file image
int newFileImage(char imageName[], Image *image){
	FILE* fichier = NULL;
	fichier = fopen(imageName, "w");

	if (fichier != NULL){
		fprintf(fichier, "%s\n", image->format);
		fprintf(fichier, "%s", "#Made by Andrea & Clara with love\n");
		fprintf(fichier, "%d %d\n", image->width, image->height);
		fprintf(fichier, "%d\n", image->maxValue);
		fwrite(image->pixelData, sizeof(unsigned char), image->width*image->height*3, fichier);
		fclose(fichier);
	}
	return EXIT_SUCCESS;
}

// Free image space
void freeImage(Image *image) {
  if(image != NULL) {
    image->width  = 0;
    image->height = 0;
	
	free(image);
	}
}
