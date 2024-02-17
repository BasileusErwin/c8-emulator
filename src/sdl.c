#include <machine.h>
#include <math.h>
#include <sdl.h>

void expansion(char *from, uint32_t *to) {
  for (int i = 0; i < SCREEN_SIZE; i++) {
    to[i] = (from[i]) ? -1 : 0;
  }
}

SDL_Window *init_window() {
  SDL_Init(SDL_INIT_EVERYTHING);

  return SDL_CreateWindow(
      "CHIP-8 Emulator",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      640,
      320,
      0
  );
}

SDL_Renderer *init_render(SDL_Window *window) {
  return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

void update_texture(
    SDL_Texture *texture, char *screen, uint32_t *pixels, int *pitch
) {
  SDL_LockTexture(texture, NULL, (void **) pixels, pitch);
  expansion(screen, pixels);

  SDL_UnlockTexture(texture);
}

void destroy_window(
    SDL_Window *window, SDL_Renderer *render, SDL_Texture *texture
) {
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

// Audio

typedef struct audio_t {
  float tone_pos;
  float tone_inc;
} Audio;

static void feed(void *udata, uint8_t *stream, int len) {
  Audio *audio = (Audio *) udata;
  for (int i = 0; i < len; i++) {
    stream[i] = sinf(audio->tone_pos) + 127;
    audio->tone_pos += audio->tone_inc;
  }
}

SDL_AudioSpec *init_audio_spec() {
  Audio *audio = (Audio *) malloc(sizeof(Audio));
  audio->tone_pos = 0;
  audio->tone_inc = 2 * M_PI * 440 / 44100;

  SDL_AudioSpec *spec = (SDL_AudioSpec *) malloc(sizeof(SDL_AudioSpec));
  spec->freq = 44100;
  spec->format = AUDIO_U8;
  spec->channels = 1;
  spec->samples = 4096;
  spec->callback = feed;
  spec->userdata = audio;

  return spec;
}

void destroy_audio_spec(SDL_AudioSpec *audio_spec) {
  free(audio_spec->userdata);
  free(audio_spec);
}
