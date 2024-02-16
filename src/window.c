#include <window.h>

SDL_Window *init_window() {
  SDL_Init(SDL_INIT_EVERYTHING);

  return SDL_CreateWindow(
      "CHIP-8 Emulator",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      640,
      320,
      SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
  );
}

SDL_Renderer *init_render(SDL_Window *window) {
  return SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );
}

SDL_Texture *init_texture(SDL_Renderer *render, SDL_Surface *surface) {
  SDL_Texture *texture = SDL_CreateTexture(
      render,
      SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_STREAMING,
      64,
      32
  );

  SDL_LockTexture(texture, NULL, &surface->pixels, &surface->pitch);

  memset(surface->pixels, 0xFF, 32 * surface->pitch);

  SDL_UnlockTexture(texture);

  return texture;
}

SDL_Surface *init_surface() {
  return SDL_CreateRGBSurface(
      0,
      64,
      32,
      32,
      0x00FF0000,
      0x0000FF00,
      0x000000FF,
      0xFF000000
  );
}

void destroy_window(
    SDL_Window *window, SDL_Renderer *render, SDL_Texture *texture
) {
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
