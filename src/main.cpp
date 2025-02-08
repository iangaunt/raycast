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
    s->set_camera(0, 0, 0);

    sphere* red = new sphere(3.7, -1, -0.5, 0xFF0000, 6);
    s->add_sphere(red);

    sphere* blue = new sphere(4.4, 1, 1.25, 0x0000FF, 9);
    s->add_sphere(blue);

    s->add_plane(new plane(-4, 2, 6, 5, 0xFF00FF));
    s->add_plane(new plane(0, 0, 1, 1, 0xFFFFFF));

    double t = 0.0;

    double cx = 0;
    double cy = 0;
    double cz = 0;

    bool w_down = false;
    bool s_down = false;
    bool a_down = false;
    bool d_down = false;
    bool q_down = false;
    bool e_down = false;

    while (!quit) {
        // s->set_camera(cx, cy, cz);
        s->generate();
        
        SDL_UpdateTexture(texture, nullptr, s->pixels, WIDTH * sizeof(unsigned int));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);

        t += 0.1;
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

                        case SDLK_w: { w_down = true; break; }
                        case SDLK_s: { s_down = true; break; }
                        case SDLK_a: { a_down = true; break; }
                        case SDLK_d: { d_down = true; break; }
                        case SDLK_q: { q_down = true; break; }
                        case SDLK_e: { e_down = true; break; }
                        
                        default: { break; }
                    }

                    break;
			    } 

                case SDL_KEYUP: {
                    switch (event.key.keysym.sym) {
                        case SDLK_w: { w_down = false; break; }
                        case SDLK_s: { s_down = false; break; }
                        case SDLK_a: { a_down = false; break; }
                        case SDLK_d: { d_down = false; break; }
                        case SDLK_q: { q_down = false; break; }
                        case SDLK_e: { e_down = false; break; }
                        
                        default: { break; }
                    }
                    
                    break;
                }
            }
        }

        if (w_down) cx += 0.1;
        if (s_down) cx -= 0.1;
        if (a_down) cy += 0.1;
        if (d_down) cy -= 0.1;
        if (q_down) cz += 0.1;
        if (e_down) cz -= 0.1;
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}