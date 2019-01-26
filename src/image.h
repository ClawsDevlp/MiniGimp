#ifndef IMAGE_H__
#define IMAGE_H__

// Struct Image contains all its parameters
typedef struct Image {
	char format[2];
	int height;
	int width;
	int maxValue;
	unsigned char pixelData[];
} Image;


// Initialize the image struct
// // with FILE i
Image * initializeImage(FILE *i);

// Writing a new image file
// // with image struct
// // and with imageName, the new image file's name
int newFileImage(char imageName[], Image *image);

// Free image space
void freeImage(Image *image);


#endif