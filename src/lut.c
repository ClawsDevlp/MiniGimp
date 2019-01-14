#include <stdio.h>
#include <stdlib.h>
#include "lut.h"
#include "image.h"

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)


void appliqueLut(Image *image, Lut *lut){
    for(int i=0; i< image->hauteur; i++){
		for (int j=0; j< image->largeur; j++){
			image->pixels[image->largeur*3*i+3*j+0] = convertToUnsignedChar(lut->rouge[image->pixels[image->largeur*3*i+3*j+0]]);
			image->pixels[image->largeur*3*i+3*j+1] = convertToUnsignedChar(lut->vert[image->pixels[image->largeur*3*i+3*j+1]]);
			image->pixels[image->largeur*3*i+3*j+2] = convertToUnsignedChar(lut->bleu[image->pixels[image->largeur*3*i+3*j+2]]);
		}
	}
}

unsigned char convertToUnsignedChar(int num){
    if(num<0) {
        num = 0;
    } else if (num>255) {
        num = 255;
    }
    return (unsigned char) num;
}

void addLum(Lut *lut, int parametre){
    for(int i=0; i<=255; i++){
        lut->rouge[i] = i+parametre;
        lut->vert[i] = i+parametre;
        lut->bleu[i] = i+parametre;
    }
}

void dimLum(Lut *lut, int parametre){
    for(int i=0; i<=255; i++){
        lut->rouge[i] = i-parametre;
        lut->vert[i] = i-parametre;
        lut->bleu[i] = i-parametre;
    }
}

void invert(Lut *lut){
    for(int i=0; i<=255; i++){
        lut->rouge[i] = 255-i;
        lut->vert[i] = 255-i;
        lut->bleu[i] = 255-i;
    }
}

void sepia(Lut *lut){
    for(int i=0; i<=255; i++){
        lut->rouge[i] = i*0.398 + i*0.769 + i*0.189;
        lut->vert[i] = i*0.349 + i*0.686 + i*0.168;
        lut->bleu[i] = i*0.272 + i*0.534 + i*0.131;
    }
}

void addCon(Lut *lut, int parametre){
    for(int i=0; i<=128; i++){
        lut->rouge[i] = i-parametre;
        lut->vert[i] = i-parametre;
        lut->bleu[i] = i-parametre;
    }
    for(int i=128; i<=255; i++){
        lut->rouge[i] = i+parametre;
        lut->vert[i] = i+parametre;
        lut->bleu[i] = i+parametre;
    }
}

void dimCon(Lut *lut, int parametre){
    for(int i=0; i<=128; i++){
        lut->rouge[i] = i+parametre;
        lut->vert[i] = i+parametre;
        lut->bleu[i] = i+parametre;
    }
    for(int i=128; i<=255; i++){
        lut->rouge[i] = i-parametre;
        lut->vert[i] = i-parametre;
        lut->bleu[i] = i-parametre;
    }
}

/*tr = 0.393R + 0.769G + 0.189B
tg = 0.349R + 0.686G + 0.168B
tb = 0.272R + 0.534G + 0.131B
*/






//créer une fonction qui transforme l’image RGB en niveau de gris en utilisant 
//cette formule sur les trois composants (RGB) du pixel : 
//Gris = 0.299 Rouge + 0.587 Vert + 0.114 Bleu.
/*void imageValeurGris(Image *image){
    unsigned char niveauGris[image->largeur*image->hauteur*3];
    int rouge; int vert; int bleu;

    for(int i=0; i < image->largeur*image->hauteur; i++){
        for(int j=0; j<3; j++){
            sscanf("%d",&rouge);
            sscanf("%d",&vert);
            sscanf("%d",&bleu);
            printf("%d",&rouge);
        }
    }
}*/