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

SDL_Texture *init_texture(SDL_Renderer *render, uint32_t *pixels, int pitch) {
  SDL_Texture *texture = SDL_CreateTexture(
      render,
      SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_STREAMING,
      64,
      32
  );
  SDL_LockTexture(texture, NULL, (void **) &pixels, &pitch);
  memset(pixels, 0xFF, 32 * pitch);
  SDL_UnlockTexture(texture);
  return texture;
}

void destroy_window(
    SDL_Window *window, SDL_Renderer *render, SDL_Texture *texture
) {
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
