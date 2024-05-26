#include <SDL2/SDL.h>
#include "rendering.h"

void Set_color(SDL_Renderer *renderer, color c){
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
}

void Draw_fill_circle(SDL_Renderer *renderer, int x, int y , int r, color c){
	Set_color(renderer, c);
	for(int w = 0; w<=2*r ; ++w){
		for(int h = 0 ; h<=2*r; ++h){
			int dx = r - w;
			int dy = r - h;
			if((SQUARE(dx) + SQUARE(dy)) <= SQUARE(r))
				SDL_RenderDrawPoint(renderer, x + dx , y + dy);
		}
	}
}

void Draw_circle(SDL_Renderer *renderer, int x, int y, 	int r, int t, color c){
	Draw_fill_circle(renderer, x, y, r+t, c);
	Draw_fill_circle(renderer, x, y, r, BACKGROUND_COLOR);
}

void Draw_line(SDL_Renderer *renderer, int x, int y, Thread t, Pframe p, color c){
    Set_color(renderer, c);
    SDL_RenderDrawLine(renderer, p.p[t.x].x + x, p.p[t.x].y + y, p.p[t.y].x + x, p.p[t.y].y + y);
}

void Draw_circle_pins(SDL_Renderer *renderer, int x, int y, Pframe pins, color c){
	Draw_fill_circle(renderer, pins.p[0].x + x, pins.p[0].y + y , 3, c);
	for(uint i=1; i<pins.n; ++i)
		Draw_fill_circle(renderer, pins.p[i].x + x, pins.p[i].y + y , 3, c);
}

void Draw_line_pins(SDL_Renderer *renderer, int x, int y, Pframe pins, color c){
	uint r = pins.p[0].x / cos(0);
	Pframe ptmp = Find_pins(r+8, pins.n);

	Set_color(renderer, c);
	for(uint i=0; i<pins.n; ++i)
		SDL_RenderDrawLine(renderer, pins.p[i].x + x, pins.p[i].y + y, ptmp.p[i].x + x, ptmp.p[i].y + y);
}

void Draw_frame(SDL_Renderer *renderer, void (*fpins)(SDL_Renderer *, int, int, Pframe, color), 
	 			int x, int y, uint r, Pframe p, color c1, color c2){
    Draw_circle(renderer, x, y, r, 2, c1); 
    fpins(renderer, x, y, p, c2);
}

void Draw_canvas();