#ifndef CHIP_8_WINDOW_H
#define CHIP_8_WINDOW_H
#include <SDL2/SDL.h>

SDL_Window *init_window();
SDL_Renderer *init_render(SDL_Window *window);
SDL_Surface *init_surface();
SDL_Texture *init_texture(SDL_Renderer *render, SDL_Surface *surface);
void destroy_window(
    SDL_Window *window, SDL_Renderer *render, SDL_Texture *texture
);
void update_texture(
    SDL_Texture *texture, char *screen, uint32_t *pixels, int *pitch
);

SDL_AudioSpec *init_audio_spec();
void destroy_audio_spec(SDL_AudioSpec *audio_spec);

#endif
