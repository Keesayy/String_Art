#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Graphics/rendering.h"	

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800
#define RADIUS 250

int main(void){
    // if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    //     fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
    //     return EXIT_FAILURE;
    // }

    // SDL_Window *window = SDL_CreateWindow("StringArt",
    //                                       100, 100,
    //                                       SCREEN_WIDTH, SCREEN_HEIGHT,
    //                                       SDL_WINDOW_SHOWN);

    // if (window == NULL) {
    //     fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    //     return EXIT_FAILURE;
    // }

    // SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
    //                                             SDL_RENDERER_ACCELERATED |
    //                                             SDL_RENDERER_PRESENTVSYNC);
    // if (renderer == NULL) {
    //     SDL_DestroyWindow(window);
    //     fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    //     return EXIT_FAILURE;
    // }  

    // SDL_Event e;
    // int quit = 0;
    // Pframe p = Find_pins(RADIUS, 100);

    // // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
    // Set_color(renderer, BACKGROUND_COLOR);
    // SDL_RenderClear(renderer);  

    // Draw_frame(renderer, &Draw_line_pins, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, RADIUS, p, BLACK, GREY);
    // Draw_line(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, (Thread){.x = 0, .y = 66}, p, GREY);
    // SDL_RenderPresent(renderer);

    // while (quit != 1) {
    //     while (SDL_PollEvent(&e)) {
    //         switch (e.type) {
    //         case SDL_QUIT:
    //            	printf("quitting\n");
    //            	quit = 1;
    //             break;

	// 		case SDL_KEYDOWN :
    //         {
	// 			switch(e.key.keysym.sym){
    //             case SDLK_q:
    //                 printf("quitting\n");
    //                 quit = 1;
    //                 break;

    //             case SDLK_SPACE:

    //                 break;
    //             }
    //         }
    //         case SDL_MOUSEBUTTONDOWN:

    //             break;

    //         default: {}
    //         }
    //     }  
    // }

    // SDL_DestroyWindow(window);
    // SDL_DestroyRenderer(renderer);
    // SDL_Quit();

    // Pframe_print(p);
    // PFRAME_FREE(p);

    // img_t img    = ReadIMG("bonobo.pgm");
    // int r        = Circle_cropIMG(img);
    // Pframe p     = Find_pins(r, 300);
    // img_t canvas = Canvas_create(img);

    // InvertGrayIMG(canvas);
    // Thread t = {.x = 0, .y = 0};
    // for(int i=0; i<100; ++i){
    //     t = Find_thread(img, canvas, p, t);
    //     printf("%d %d\n", t.x, t.y); 
    // }
    // InvertGrayIMG(canvas);
    Thlist *t = String_Art("A.pgm", 300);
    FILE *f = fopen("o.txt", "w");
    Thlist_print(t, f);

    return EXIT_SUCCESS;
}