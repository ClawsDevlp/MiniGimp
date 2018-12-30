#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "lut.h"

int main(int argc, char *argv[]){
	if(argc < 1){
		printf("Une image est nécessaire \n");
		return EXIT_FAILURE;
	}

	FILE *i = fopen(argv[1],"r");
	if (i==NULL){
		printf( "L'image n'a pas pu être ouverte %s\n", argv[1] );
		return EXIT_FAILURE;
	};

    Image image;
	initializeImage(i,image);

	fclose(i);

	return EXIT_SUCCESS;
}