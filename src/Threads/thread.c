#include <math.h>
#include <assert.h>
#include "thread.h"

Point Point_translate(Point a, img_t img){
	return (Point){.x = a.x + (uint)img.height/2, .y = a.y + (uint)img.width/2};
}

void Pframe_print(Pframe pins){
	for(uint i=0; i<pins.n; ++i)
		printf("(%d, %d); ", pins.p[i].x, pins.p[i].y);
	printf("\n");
}

Pframe Find_pins(int r, int n){
	Pframe pins;
	pins.n = n;
	pins.p = (Point*)malloc(n*sizeof(Point));
	assert(pins.p != NULL);

	double dp = (2*PI) / n;
	double theta = 0;
	uint i = 0;
	while(theta < (2*PI)){
		pins.p[i].x = (uint)(r * cos(theta)); 
		pins.p[i].y = (uint)(r * sin(theta));
		theta += dp;
		i++;
	}
	return pins;
}

img_t Canvas_create(img_t img){
	img_t canvas;
	canvas.height = 1*img.height;
	canvas.width = 1*img.width;
	canvas.max = img.max;
	
	const size_t length = canvas.height*canvas.width;
	canvas.pixels = (pixel_t*)malloc(length*sizeof(pixel_t));
	if(canvas.pixels == NULL) exit(EXIT_FAILURE);

	for(size_t i=0; i<length; ++i){
		//canvas.pixels[i].c = img.pixels[i].c;
		canvas.pixels[i].g = canvas.max; 
	}
	Circle_cropIMG(canvas);
	return canvas;
}

bool Point_in_bounds(img_t canvas, int x, int y){
	return (0 <= x) && (x < (int)canvas.width) && (0 <= y) && (y < (int)canvas.height);
}

double Thread_darkness(double dark, double thick){
	double d = 0;
	double t = ABS(thick);

	if(t >= 0 && t <= 0.5) 
		d = dark;

	if(t > 0.5 && t <= 3.0)
		d = (-(dark * t) + ((5.0 / 2.0 )* dark) ) / 2.0;	

	return d;
}

uint Add(uint x, double y){ return x + (uint)y; }
uint Remove(uint x, double y){ return x - (uint)y; }

void Canvas_thread(img_t canvas, Pframe pf, Thread t,
				   uint f(uint, double)){
	Point a = Point_translate(pf.p[t.x], canvas);
	Point b = Point_translate(pf.p[t.y], canvas);
	int x1 = (int)a.x; int y1 = (int)a.y; 
	int x2 = (int)b.x; int y2 = (int)b.y;
	
	double dx = x2 - x1;
	double dy = y2 - y1;
	double dark = canvas.max / 5;

	if(ABS(dx) > ABS(dy)){
		if(x1 > x2){
			SWAP(int, x1, x2);
			SWAP(int, y1, y2);
		}

		for(int x=x1; x<=x2; ++x){
			double yf = dy*(x - x1)/dx + y1;
			int y = (int)dy*(x - x1)/(int)dx + y1;
			double df = ABS(yf - (double)y);
			//if(Point_in_bounds(canvas, x, y)){
				P(canvas, x, y).g 	= f(P(canvas, x, y).g  , Thread_darkness(dark, 0 + df));
				P(canvas, x, y+1).g = f(P(canvas, x, y+1).g, Thread_darkness(dark, 1 + df));
				P(canvas, x, y+2).g = f(P(canvas, x, y+2).g, Thread_darkness(dark, 2 + df));
				P(canvas, x, y-1).g = f(P(canvas, x, y-1).g, Thread_darkness(dark, 1 + df));
				P(canvas, x, y-2).g = f(P(canvas, x, y-2).g, Thread_darkness(dark, 2 + df));
			//}
			//printf("%lf\n", yf - (double)y);
		}
	}else{
		if(y1 > y2){
			SWAP(int, x1, x2);
			SWAP(int, y1, y2);
		}

		for(int y=y1; y<=y2; ++y){
			double xf = dx*(y - y1)/dy + x1;
			int x = dx*(y - y1)/dy + x1;
			double df = ABS(xf - (double)x);
			if(Point_in_bounds(canvas, x-2, y)){
				P(canvas, x, y).g   = f(P(canvas, x, y).g  , Thread_darkness(dark, 0 + df));
				P(canvas, x+1, y).g = f(P(canvas, x+1, y).g, Thread_darkness(dark, 1 + df));
				P(canvas, x+2, y).g = f(P(canvas, x+2, y).g, Thread_darkness(dark, 2 + df));
				P(canvas, x-1, y).g = f(P(canvas, x-1, y).g, Thread_darkness(dark, 1 + df));
				P(canvas, x-2, y).g = f(P(canvas, x-2, y).g, Thread_darkness(dark, 2 + df));
			}
			//printf("%lf\n", xf - (double)x);
		}
	}
}

uint Errorf(img_t img, img_t canvas){
	uint sum = 0;
	for(size_t i=0; i<img.height; ++i){
		for(size_t j=0; j<img.width; ++j){
			if(P(img, i, j).c)
				sum += SQUARE((P(img, i, j).g - P(canvas, i, j).g));
		}
	}
	return sum;
}

Thread Find_thread(img_t img, img_t canvas, Pframe pf, Thread t){
	Thread best = {.x = t.y, .y = (t.y + 1) % pf.n};
	Canvas_thread(canvas, pf, best, Add);
	uint min = Errorf(img, canvas);
	Canvas_thread(canvas, pf, best, Remove);

	for(uint i=2; i<pf.n; ++i){
		Thread candidate = {.x = t.y, .y = (t.y + i) % pf.n};
		Canvas_thread(canvas, pf, candidate, Add);

		uint tmp = Errorf(img, canvas);
		if(tmp < min && candidate.y != t.x){
			best.y = candidate.y;
			min = tmp;
		}
		Canvas_thread(canvas, pf, candidate, Remove);
	}
	Canvas_thread(canvas, pf, best, Add);
	return best;
}

Thlist *String_Art(const char* src, int npins){
    img_t img    = ReadIMG(src);
    int r        = Circle_cropIMG(img);
    Pframe p     = Find_pins(r, npins);
    img_t canvas = Canvas_create(img);

    Thlist *l = NULL;
    InvertGrayIMG(canvas);


    Thread t = {.x = 0, .y = 0};
    for(int i=0; i<500; ++i){
    	t = Find_thread(img, canvas, p, t);
    	Thlist_add(&l, t);
    	printf("%d %d\n", t.x, t.y);
    }
  
    InvertGrayIMG(canvas);
    WriteIMG("out2.pgm", canvas);

    IMGFREE(canvas);
    IMGFREE(img);
    PFRAME_FREE(p);
    return l;
}

void Thlist_print(Thlist *t, FILE *f){
	uint i = 1;
	while(t != NULL){
		fprintf(f, "(%d, %d) ", t->s.x, t->s.y);
		t = t->next;
		if(i % 4 == 0) fprintf(f, "\n");
		++i;
	}
}
void Thlist_add(Thlist **t, Thread v){
	Thlist *tail = (Thlist*)malloc(sizeof(Thlist));
	if (tail == NULL) exit(EXIT_FAILURE);
	tail->s = v;
	tail->next = NULL;

	if(*t == NULL){
		*t = tail;
	}else{
		Thlist *copie = *t;
		while(copie->next != NULL) copie = copie->next;
		copie->next = tail;
	}
}

void Thlist_free(Thlist *t){
	Thlist *copie = NULL;
	while(t != NULL){
		copie = t;
		t = t->next;
		free(copie);
	}
}