#ifndef IMAGE_H__
#define IMAGE_H__

typedef struct Image {
	char format[2];
	int height;
	int width;
	int maxValue;
	unsigned char pixelData[];
} Image;


Image * initializeImage(FILE *i);
int newFileImage(char imageName[], Image *image);
void freeImage(Image *image);


#endif