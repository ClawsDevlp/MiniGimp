#ifndef LUT_H__
#define LUT_H__
#include "image.h"


//struct LUT contains 3 colors table : R, G & B
typedef struct Lut {
    int red[256];
    int green[256];
    int blue[256];
} Lut;


// Apply LUT on the struct image
void applyLut(Image *image, Lut *lut);

// Initialize basic LUT
void initializeLut(Lut *lut);

// int num -> unsigned char num
unsigned char convertToUnsignedChar(int num);

// Truncate num between 0 and 255
int truncate(int num);

// Add and diminish luminosity of LUT
// // (+ or - parameter on each RGB color value)
void addLum(Lut *lut, int parameter);
void dimLum(Lut *lut, int parameter);

// Invert colors of LUT
void invert(Lut *lut);

// Apply sepia effect on Image
void sepia(Image *image);

// Apply mirror effect on Image
void mirror(Image *image);

// Apply seuil effect on LUT
void seuil(Lut *lut);

// Add and diminish contrast of LUT
// // with parameter between 0 & 255
void addCon(Lut *lut, int parameter);
void dimCon(Lut *lut, int parameter);

// Apply black and white effect on Image
void blackWhite(Image *image);


#endif