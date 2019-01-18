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

//LUT contient 3 couleurs R,G & B
typedef struct Lut {
    int rouge[256];
    int vert[256];
    int bleu[256];
} Lut;

void appliqueLut(Image *image, Lut *lut);
unsigned char convertToUnsignedChar(int num);
void initializeLut(Lut *lut);
void addLum(Lut *lut, int parametre);
void dimLum(Lut *lut, int parametre);
void invert(Lut *lut);
void sepia(Image *image);
void seuil(Lut *lut);
void addCon(Lut *lut, int parametre);
void dimCon(Lut *lut, int parametre);
void noirEtBlanc(Image *image);

#endif