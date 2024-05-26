#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define ABS(A) ( ((A) > 0) ? (A) : (-(A)) )
#define MIN(A, B) ( ((A) < (B)) ? (A) : (B) )
#define SQUARE(A) ((A) * (A))

#define IMGFREE(IMG) free((IMG).pixels)
#define P(A, I, J) (A).pixels[(I)*(A).width + (J)]

/* convert jpeg/png to ppm/pgm with ImageMagick
   convert INPUT.JPG -compress none OUTPUT.PPM */

// Rgb
typedef struct{
	uint8_t r;
	uint8_t g;
	uint8_t b;
}color;

typedef struct{
	uint g; //gray color
	bool c; //In circle ?
}pixel_t;

/** Store Image PPM or PGM format **/
typedef struct{
	size_t height;
	size_t width;
	uint max;        // >= 255
	pixel_t *pixels;
}img_t;

void ShowIMG(img_t img);
img_t ReadIMG(const char *src);
void WriteIMG(const char *name, img_t img);

//We take the biggest circle possible from center
void InvertGrayIMG(img_t img);
int Circle_cropIMG(img_t img);

#endif