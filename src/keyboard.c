#include <SDL2/SDL_keyboard.h>
#include <keyboard.h>
#include <stdint.h>

/**
 * Chip 8 has a hex based keypad (0x0 - 0xF)
 *
 * +---------+
 * | 1 2 3 C |
 * | 4 5 6 D |
 * | 7 8 9 E |
 * | A 0 B F |
 * +---------+
 *
 * */
char keys[] = {
  SDL_SCANCODE_X, // 0
  SDL_SCANCODE_1, // 1
  SDL_SCANCODE_2, // 2
  SDL_SCANCODE_3, // 3
  SDL_SCANCODE_Q, // 4
  SDL_SCANCODE_W, // 5
  SDL_SCANCODE_E, // 6
  SDL_SCANCODE_A, // 7
  SDL_SCANCODE_S, // 8
  SDL_SCANCODE_D, // 9
  SDL_SCANCODE_Z, // A
  SDL_SCANCODE_C, // B
  SDL_SCANCODE_4, // C
  SDL_SCANCODE_R, // D
  SDL_SCANCODE_F, // E
  SDL_SCANCODE_V  // F
};

/**
 * Check if a key is pressed.
 * This function acceps only a Chip-8 key in rage (0x0 - 0xF)
 *
 * @param key The key to check
 *
 * @return 1 if the key is pressed, 0 otherwise
 * */
int is_key_pressed(char key) {
  if (key < 0 || key > 0xF) {
    return 0;
  }

  const uint8_t *sld_keys = SDL_GetKeyboardState(NULL);
  uint8_t real_key = keys[(int) key];

  return sld_keys[real_key];
}
