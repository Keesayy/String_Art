#include "image.h"

void ShowIMG(img_t img){
	const size_t length = img.height * img.width;
	printf("%ld %ld %d\n", img.height, img.width, img.max);

	for (size_t i =0; i<length; ++i){
		printf(" (%d, %d);", img.pixels[i].c, img.pixels[i].g);
		if(i+1 % img.height == 0) printf("\n");
	}
}

img_t ReadIMG(const char *src){
	img_t img;
	FILE *f;
	f = fopen(src, "r");
	if (f == NULL) {
 	   fprintf(stderr, "Error opening file: %s\n", src);
    	exit(EXIT_FAILURE);
	}
	
	fscanf(f, "P2 %ld %ld %d", &img.width, &img.height, &img.max);

	const size_t length = img.width * img.height;
	img.pixels = (pixel_t*)malloc(length*sizeof(pixel_t));
	for(size_t i = 0; i<length; ++i){
		fscanf(f, "%d", &img.pixels[i].g);
		img.pixels[i].c = 0;
	}

	fclose(f);
	return img;
}

void WriteIMG(const char *name, img_t img){
	FILE * f;
	f = fopen(name, "w");
	if (f == NULL) {
 	   fprintf(stderr, "Error opening f: %s\n", name);
    	exit(EXIT_FAILURE);
	}
	fprintf(f, "P2\n%ld %ld\n%d\n", img.width, img.height, img.max);	

	for(size_t i=0; i<img.height; ++i){
		for(size_t j=0; j<img.width; ++j){
			// if(P(img, i, j).c)
			// 	fprintf(f, "%hd ", P(img, i, j).g);
			// else
			// 	fprintf(f, "%hd ", img.max);
			fprintf(f, "%hd ", P(img, i, j).g);
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

void InvertGrayIMG(img_t img){
	for(size_t i=0; i<img.height*img.width; ++i){
		int tmp = (int)img.pixels[i].g - img.max;
		img.pixels[i].g = ABS(tmp);
	}

}

int Circle_cropIMG(img_t img){
	int r = (MIN(img.height, img.width) / 2) ;
	int y = img.width / 2;
	int x = img.height / 2;

	for(int w = 0; w<=2*r ; ++w){
		for(int h = 0 ; h<=2*r; ++h){
			int dx = r - w;
			int dy = r - h;
			if((SQUARE(dx) + SQUARE(dy)) < SQUARE(r))
				P(img, x + dx , y + dy).c = 1;
		}
	}
	return r;
}