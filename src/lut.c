#include <stdio.h>
#include <stdlib.h>
#include "lut.h"

// Apply LUT on the image
void applyLut(Image *image, Lut *lut) {
    int coordinateR, coordinateG, coordinateB;

    for (int i=0; i < image->height; i++) {
		for (int j=0; j < image->width; j++) {
            coordinateR = image->width*3*i+3*j+0;
            coordinateG = image->width*3*i+3*j+1;
            coordinateB = image->width*3*i+3*j+2;

			image->pixelData[coordinateR] = convertToUnsignedChar(lut->red[image->pixelData[coordinateR]]);
			image->pixelData[coordinateG] = convertToUnsignedChar(lut->green[image->pixelData[coordinateG]]);
			image->pixelData[coordinateB] = convertToUnsignedChar(lut->blue[image->pixelData[coordinateB]]);
		}
	}
}

// int num -> unsigned char num
unsigned char convertToUnsignedChar(int num) {
    return (unsigned char) truncate(num);
}

// Truncate num between 0 and 255
int truncate(int num) {
    if (num < 0) {
        num = 0;
    } else if (num > 255) {
        num = 255;
    }
    return num;
}

// Initialize basic LUT
void initializeLut(Lut *lut) {
    for (int i=0; i <= 255; i++) {
        lut->red[i] = i;
        lut->green[i] = i;
        lut->blue[i] = i;
    }
}

// Add luminosity to LUT
void addLum(Lut *lut, int parameter) {
    for (int i=0; i <= 255; i++) {
        lut->red[i] += parameter;
        lut->green[i] += parameter;
        lut->blue[i] += parameter;
    }
}

// Diminish luminosity of LUT
void dimLum(Lut *lut, int parameter) {
    for(int i=0; i <= 255; i++) {
        lut->red[i] -= parameter;
        lut->green[i] -= parameter;
        lut->blue[i] -= parameter;
    }
}

// Invert colors of LUT
void invert(Lut *lut) {
    for(int i=0; i <= 255; i++) {
        lut->red[i] = 255-lut->red[i];
        lut->green[i] = 255-lut->green[i];
        lut->blue[i] = 255-lut->blue[i];
    }
}

// Apply sepia effect on Image
void sepia(Image *image) {
    int coordinateR, coordinateG, coordinateB;
    int red, green, blue;

    for (int i=0; i < image->height; i++) {
		for (int j=0; j < image->width; j++) {
            coordinateR = image->width*3*i+3*j+0;
            coordinateG = image->width*3*i+3*j+1;
            coordinateB = image->width*3*i+3*j+2;
            
            red = image->pixelData[coordinateR];
            green = image->pixelData[coordinateG];
            blue = image->pixelData[coordinateB];
            
            // Turning RGB to sepia
            image->pixelData[coordinateR] = convertToUnsignedChar(red*0.593 + green*0.669 + blue*0.089);
            image->pixelData[coordinateG] = convertToUnsignedChar(red*0.349 + green*0.686 + blue*0.168);
            image->pixelData[coordinateB] = convertToUnsignedChar(red*0.272 + green*0.534 + blue*0.131);
		}
	}
}

// Apply mirror effect on Image
void mirror(Image *image) {
    int coordinateR, coordinateG, coordinateB;
    int oppCoordinateR, oppCoordinateG, oppCoordinateB;
    int tmpR, tmpV, tmpB;

    // Swapping values between RGB coordinate and their opposite
    for (int i=0; i < image->height; i++) {
		for (int j=0; j < image->width/2; j++) {
            coordinateR = image->width*3*i+3*j+0;
            coordinateG = image->width*3*i+3*j+1;
            coordinateB = image->width*3*i+3*j+2;

            oppCoordinateR = image->width*3*i+(image->width-j)*3+0;
            oppCoordinateG = image->width*3*i+(image->width-j)*3+1;
            oppCoordinateB = image->width*3*i+(image->width-j)*3+2;

            tmpR = image->pixelData[coordinateR];
            tmpV = image->pixelData[coordinateG];
            tmpB = image->pixelData[coordinateB];

            image->pixelData[coordinateR] = image->pixelData[oppCoordinateR];
            image->pixelData[coordinateG] = image->pixelData[oppCoordinateG];
            image->pixelData[coordinateB] = image->pixelData[oppCoordinateB];
            
            image->pixelData[oppCoordinateR] = tmpR;
            image->pixelData[oppCoordinateG] = tmpV;
            image->pixelData[oppCoordinateB] = tmpB;
		}
	}
}

// Apply seuil effect on LUT
void seuil(Lut *lut) {
    for (int i=0; i <= 128; i++) {
        lut->red[i] = 0;
        lut->green[i] = 0;
        lut->blue[i] = 0;
    }
    for (int i=129; i <= 255; i++) {
        lut->red[i] = 255;
        lut->green[i] = 255;
        lut->blue[i] = 255;
    }
}

// Add contrast to LUT
void addCon(Lut *lut, int parameter) {
    float factor = (259.*(parameter+255))/(255*(259-parameter));

    for (int i=0; i <= 255; i++) {
        lut->red[i] = truncate(factor*(lut->red[i] -128) +128);
        lut->green[i] = truncate(factor*(lut->green[i] -128) +128);
        lut->blue[i] = truncate(factor*(lut->blue[i] -128) + 128);
    }
}

// Diminish contrast of LUT
void dimCon(Lut *lut, int parameter) {
    float factor = (259.*(-parameter+255)) / (255*(259+parameter));

    for (int i=0; i <= 255; i++) {
        lut->red[i] = truncate(factor*(lut->red[i] -128) +128);
        lut->green[i] = truncate(factor*(lut->green[i] -128) +128);
        lut->blue[i] = truncate(factor*(lut->blue[i] -128) +128);
    }
}

// Apply black and white effect on Image
void blackWhite(Image *image) {
    int grey;
    int coordinateR, coordinateG, coordinateB;

    for (int i=0; i < image->height; i++) {
		for (int j=0; j < image->width; j++) {
            coordinateR = image->width*3*i+3*j+0;
            coordinateG = image->width*3*i+3*j+1;
            coordinateB = image->width*3*i+3*j+2;

            // Turning RGB to grey
            grey = image->pixelData[coordinateR]*0.299 + image->pixelData[coordinateG]*0.587 + image->pixelData[coordinateB]*0.114;
            
            image->pixelData[coordinateR] = grey;
            image->pixelData[coordinateG] = grey;
            image->pixelData[coordinateB] = grey;
		}
	}
}