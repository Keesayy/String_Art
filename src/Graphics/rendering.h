#ifndef _RENDERING_H_
#define _RENDERING_H_

#include "../Threads/thread.h"

#define BACKGROUND_COLOR WHITE
#define WHITE (color){.r = 255, .g = 255, .b = 255}
#define BLACK (color){.r = 0  , .g = 0  , .b = 0}
#define GREY  (color){.r = 128, .g = 128, .b = 128} 
#define GOLD  (color){.r = 218, .g = 165, .b = 32}
#define RED   (color){.r = 255, .g = 0  , .b = 0}

/** **/
void Set_color(SDL_Renderer *renderer, color c);
void Draw_fill_circle(SDL_Renderer *renderer, int x, int y, int r, color c);
void Draw_circle(SDL_Renderer *renderer, int x, int y, int r, int thickness, color c);
void Draw_line(SDL_Renderer *renderer, int x, int y, Thread t, Pframe p, color c);

/** **/
void Draw_circle_pins(SDL_Renderer *renderer, int x, int y, Pframe pins, color c);
void Draw_line_pins(SDL_Renderer *renderer, int x, int y, Pframe pins, color c);
void Draw_frame(SDL_Renderer *renderer, void (*fpins)(SDL_Renderer *, int, int, Pframe, color), 
				int x, int y, uint r, Pframe p, color c1, color c2);

/** **/
void Draw_canvas(SDL_Renderer *renderer);

#endif