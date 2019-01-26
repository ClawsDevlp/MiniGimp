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

	// Read image file parameters
	fscanf(i,"%s\n", format);
	fscanf(i,"%d", &width);
	fscanf(i,"%d\n", &height);

	// Allocate enough space for the image
	image = malloc(sizeof(Image) + 3*height*width*sizeof(unsigned char));
	if (image == NULL) {
		fprintf(stderr, "Not enough memory!\n");
		exit(1);
	}

	// Read image file parameters
	strcpy(image->format, format);
	fscanf(i, "%d\n", &image->maxValue);
	image->height = height;
	image->width = width;
	fread(image->pixelData, sizeof(unsigned char), width*height*3, i);

	return image;
}

// Writing a new image file
int newFileImage(char imageName[], Image *image){
	FILE* newFile = NULL;
	newFile = fopen(imageName, "w");

	// Print on new image all parameters and new data pixels
	if (newFile != NULL){
		fprintf(newFile, "%s\n", image->format);
		/* fprintf(newFile, "%s", "#Made by Andrea & Clara with love\n"); */
		fprintf(newFile, "%d %d\n", image->width, image->height);
		fprintf(newFile, "%d\n", image->maxValue);
		fwrite(image->pixelData, sizeof(unsigned char), image->width*image->height*3, newFile);
		fclose(newFile);
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
