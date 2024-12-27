#include <cstdlib>
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>

#include "headers/scene.h"
#include "headers/sphere.h"

int WIDTH = 300;
int HEIGHT = 300;

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow(
        "SDL", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        WIDTH, HEIGHT, 
        SDL_WINDOW_ALLOW_HIGHDPI
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
    
    SDL_Texture* texture = 	texture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_ARGB8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        WIDTH, HEIGHT
    );

    if (window == NULL) return 1;

    SDL_Event event;
    bool quit = false;

    scene* s = new scene(WIDTH, HEIGHT, 0, 20);

    sphere* red = new sphere(3.7, -1, -0.5, 0xFFFFFF, 6);
    s->add(red);

    sphere* blue = new sphere(4.4, 1, 1.25, 0xBBBBBB, 9);
    s->add(blue);

    double t = 0.0;

    while (!quit) {
        s->generate();

        SDL_UpdateTexture(texture, nullptr, s->pixels, WIDTH * sizeof(unsigned int));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);

        t += 0.05;
        red->r = abs(sin(t)) * 6;
        blue->z = sin(t) * 2 + 1;

        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    quit = true;
                    break;
                }  
            
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE: { 
                            quit = true; 
                            break;
                        }
                        
                        default: { break; }
                    }

                    break;
			    } 
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}