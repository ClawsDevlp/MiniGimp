#include <stdio.h>
#include <stdlib.h>
#include "lut.h"
#include "image.h"


void appliqueLut(Image *image, Lut *lut){
    for (int i=0; i< image->hauteur; i++){
		for (int j=0; j< image->largeur; j++){
			image->pixels[image->largeur*3*i+3*j+0] = convertToUnsignedChar(lut->rouge[image->pixels[image->largeur*3*i+3*j+0]]);
			image->pixels[image->largeur*3*i+3*j+1] = convertToUnsignedChar(lut->vert[image->pixels[image->largeur*3*i+3*j+1]]);
			image->pixels[image->largeur*3*i+3*j+2] = convertToUnsignedChar(lut->bleu[image->pixels[image->largeur*3*i+3*j+2]]);
		}
	}
}

unsigned char convertToUnsignedChar(int num){
    if (num < 0) {
        num = 0;
    } else if (num > 255) {
        num = 255;
    }
    return (unsigned char) num;
}


void initializeLut(Lut *lut){
    for (int i=0; i<=255; i++){
        lut->rouge[i] = i;
        lut->vert[i] = i;
        lut->bleu[i] = i;
    }
}

void addLum(Lut *lut, int parametre){
    for (int i=0; i<=255; i++){
        lut->rouge[i] += parametre;
        lut->vert[i] += parametre;
        lut->bleu[i] += parametre;
    }
}

void dimLum(Lut *lut, int parametre){
    for(int i=0; i<=255; i++){
        lut->rouge[i] -= parametre;
        lut->vert[i] -= parametre;
        lut->bleu[i] -= parametre;
    }
}

void invert(Lut *lut){
    for(int i=0; i<=255; i++){
        lut->rouge[i] = 255-lut->rouge[i];
        lut->vert[i] = 255-lut->vert[i];
        lut->bleu[i] = 255-lut->bleu[i];
    }
}

void sepia(Image *image){
    int rouge; int vert; int bleu;
    for(int i=0; i< image->hauteur; i++){
		for (int j=0; j< image->largeur; j++){
            rouge = image->pixels[image->largeur*3*i+3*j+0];
            vert = image->pixels[image->largeur*3*i+3*j+1];
            bleu = image->pixels[image->largeur*3*i+3*j+2];
            image->pixels[image->largeur*3*i+3*j+0] = convertToUnsignedChar(rouge*0.493 + vert*0.769 + bleu*0.089);
            image->pixels[image->largeur*3*i+3*j+1] = convertToUnsignedChar(rouge*0.349 + vert*0.686 + bleu*0.168);
            image->pixels[image->largeur*3*i+3*j+2] = convertToUnsignedChar(rouge*0.272 + vert*0.534 + bleu*0.131);
		}
	}
}

void seuil(Lut *lut){
    for(int i=0; i<=128; i++){
        if (i<128) {
            lut->rouge[i] = 0;
            lut->vert[i] = 0;
            lut->bleu[i] = 0;
        } else {
            lut->rouge[i] = 255;
            lut->vert[i] = 255;
            lut->bleu[i] = 255;
        }
    }
}

void addCon(Lut *lut, int parametre){
    for(int i=0; i<=255; i++){
        if (i<128) {
            lut->rouge[i] -= parametre;
            lut->vert[i] -= parametre;
            lut->bleu[i] -= parametre;
        } else {
            lut->rouge[i] += parametre;
            lut->vert[i] += parametre;
            lut->bleu[i] += parametre;
        }
    }
}

/*
void dimCon(Lut *lut, int parametre){
    for(int i=0; i<=255; i++){
        if (i<128) {
            lut->rouge[i] = i+parametre;
            lut->vert[i] = i+parametre;
            lut->bleu[i] = i+parametre;
        } else {
            lut->rouge[i] = i-parametre;
            lut->vert[i] = i-parametre;
            lut->bleu[i] = i-parametre;
        }
    }
}*/

void dimCon(Lut *lut, int parametre){
    int ajout;
    for(int i=0; i<=255; i++){
        if (i<128) {
            ajout = i+parametre;
            if(ajout > 128){
                ajout = 128;
            }
        } else {
            ajout = i-parametre;
            if(ajout < 128){
                ajout = 128;
            }
        }
        lut->rouge[i] = ajout;
        lut->vert[i] = ajout;
        lut->bleu[i] = ajout;
    }
}

void noirEtBlanc(Image *image){
    int gris;
    for(int i=0; i< image->hauteur; i++){
		for (int j=0; j< image->largeur; j++){
            gris = image->pixels[image->largeur*3*i+3*j+0]*0.299 + image->pixels[image->largeur*3*i+3*j+1]*0.587 + image->pixels[image->largeur*3*i+3*j+2]*0.114;
            image->pixels[image->largeur*3*i+3*j+0] = gris;
            image->pixels[image->largeur*3*i+3*j+1] = gris;
            image->pixels[image->largeur*3*i+3*j+2] = gris;
		}
	}
}