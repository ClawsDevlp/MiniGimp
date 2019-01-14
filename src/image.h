#ifndef IMAGE_H__
#define IMAGE_H__

typedef struct Image {
	char code[2];
	int hauteur;
	int largeur;
	int profondeur;
	unsigned char pixels[];
} Image;

Image * initializeImage(FILE *i);
int newFileImage(char nom[], Image *image);
int allocationImage(Image *image, int hauteur, int largeur);
void freeImage(Image *image);

#endif