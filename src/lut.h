#ifndef LUT_H__
#define LUT_H__
#include "image.h"

/*typedef enum {
    ADDLUM,
    DIMLUM,
    ADDCON,
    DIMCON,
    INVERT,
    SEPIA
} lut;*/

//LUT contains 3 colors : R,G & B
typedef struct Lut {
    int red[256];
    int green[256];
    int blue[256];
} Lut;


void applyLut(Image *image, Lut *lut);
unsigned char convertToUnsignedChar(int num);
int truncate(int num);
void initializeLut(Lut *lut);
void addLum(Lut *lut, int parameter);
void dimLum(Lut *lut, int parameter);
void invert(Lut *lut);
void sepia(Image *image);
void mirror(Image *image);
void seuil(Lut *lut);
void addCon(Lut *lut, int parameter);
void dimCon(Lut *lut, int parameter);
void blackWhite(Image *image);


#endif