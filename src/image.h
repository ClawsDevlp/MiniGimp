#ifndef IMAGE_H__
#define IMAGE_H__

typedef struct Image {
	char code[2];
	int hauteur;
	int largeur;
	unsigned char pixels[];
} Image;

void initializeImage(FILE *i, Image image);
	
#endif