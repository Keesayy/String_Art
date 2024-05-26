#ifndef _THREAD_H_
#define _THREAD_H_

#include "../Images/image.h"

#define PI 3.14159
#define ABS(A) ( ((A) > 0) ? (A) : (-(A)) )
#define SWAP(TYPE, A, B) do {TYPE tmp = (A); (A) = (B); (B) = tmp;} while(0)
#define PFRAME_FREE(p) (free((p).p))

/** Point type **/
typedef struct{
	uint x;
	uint y;
}Point;

Point Point_translate(Point a, img_t img);

/** Pins around the frame **/
typedef struct{
	uint n;	  // number of pins
	Point *p; 
}Pframe;

void Pframe_print(Pframe pins);
Pframe Find_pins(int r, int n); 

/** Find best Thread **/
img_t Canvas_create(img_t img);  // Blank circle
bool Point_in_bounds(img_t canvas, int x, int y);

/** Couple of points, point is a pin number **/
typedef Point Thread; 

double Thread_darkness(double dark, double thick);
uint Add(uint x, double y);
uint Remove(uint x, double y);

void Canvas_thread(img_t canvas, Pframe pf, Thread t, uint f(uint, double));
uint Errorf(img_t img, img_t canvas);

Thread Find_thread(img_t img, img_t canvas, Pframe pf, Thread t);

typedef struct Thlist{
	Thread s;
	struct Thlist *next;
}Thlist;

Thlist *String_Art(const char* src, int npins);

//List functions 
void Thlist_print(Thlist *t, FILE *f);
void Thlist_add(Thlist **t, Thread v);
void Thlist_free(Thlist *t);

#endif