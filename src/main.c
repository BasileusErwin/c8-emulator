#include <cpu.h>
#include <keyboard.h>
#include <machine.h>
#include <rom.h>
#include <sdl.h>
#include <stdio.h>
#include <time.h>

void execute(Machine *machine) {
  srand(time(NULL));
  int mustExit = 0;
  int lastTicks = 0;
  int cycles = 0;

  SDL_Window *window = init_window();

  if (window == NULL) {
    printf("Error: Could not create window\n");
    exit(1);
  }

  SDL_Renderer *render = init_render(window);

  if (render == NULL) {
    printf("Error: Could not create renderer\n");
    exit(1);
  }

  SDL_Surface *surface = init_surface();

  SDL_Texture *texture = init_texture(render, surface);

  SDL_AudioSpec *audioSpec = init_audio_spec();
  SDL_AudioDeviceID audioDevice =
      SDL_OpenAudioDevice(NULL, 0, audioSpec, NULL, 0);

  if (audioDevice == 0) {
    printf("Error: Could not open audio device\n");
    exit(1);
  }

  if (audioSpec == NULL) {
    printf("Error: Could not create audio spec\n");
    exit(1);
  }

  if (texture == NULL) {
    printf("Error: Could not create texture\n");
    exit(1);
  }

  SDL_Event event;
  while (!mustExit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        mustExit = 1;
      }
    }

    if (SDL_GetTicks() - cycles > 1) {
      if ((int) machine->waitKey != -1) {
        for (int key = 0; key <= 0xF; key++) {
          if (is_key_pressed(key)) {
            machine->v[(int) machine->waitKey] = key;
            machine->waitKey = -1;
            break;
          }
        }
      }

      execute_instruction(machine);

      cycles = SDL_GetTicks();
    }

    if (SDL_GetTicks() - lastTicks > (1000 / 60)) {
      if (machine->delayTimer) {
        machine->delayTimer--;
      }

      if (machine->soundTimer) {
        if (--machine->soundTimer == 0) {
          SDL_PauseAudioDevice(audioDevice, 1);
        } else {
          SDL_PauseAudioDevice(audioDevice, 0);
        }
      }

      update_texture(
          texture,
          machine->screen,
          surface->pixels,
          &surface->pitch
      );

      SDL_RenderCopy(render, texture, NULL, NULL);
      SDL_RenderPresent(render);

      lastTicks = SDL_GetTicks();
    }
  }

  SDL_CloseAudioDevice(audioDevice);
  destroy_audio_spec(audioSpec);
  destroy_window(window, render, texture);
}

int main(int argc, char *argv[]) {
  Machine machine;
  init_machine(&machine);

  if (argc == 1) {
    printf("Usage: c8 <ROMFILE>\n");
    exit(1);
  }

  load_rom(&machine, argv[1]);
  execute(&machine);

  return 0;
}
