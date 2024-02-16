#ifndef CHIP_8_WINDOW_H
#define CHIP_8_WINDOW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

SDL_Window *init_window();
SDL_Renderer *init_render(SDL_Window *window);
SDL_Surface *init_surface();
SDL_Texture *init_texture(SDL_Renderer *render, SDL_Surface* surface);
void destroy_window(
    SDL_Window *window, SDL_Renderer *render, SDL_Texture *texture
);
void update_window(SDL_Texture *texture, uint32_t *pixels, int pitch);

#endif
