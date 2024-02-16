#include <machine.h>
#include <window.h>
#include <cpu.h>
#include <time.h>

typedef void (*opcode_table)(Machine *machine, uint16_t opcode);

static void operation_0(Machine *machine, uint16_t opcode);
static void operation_1(Machine *machine, uint16_t opcode);
static void operation_2(Machine *machine, uint16_t opcode);
static void operation_3(Machine *machine, uint16_t opcode);
static void operation_4(Machine *machine, uint16_t opcode);
static void operation_5(Machine *machine, uint16_t opcode);
static void operation_6(Machine *machine, uint16_t opcode);
static void operation_7(Machine *machine, uint16_t opcode);
static void operation_8(Machine *machine, uint16_t opcode);
static void operation_9(Machine *machine, uint16_t opcode);
static void operation_A(Machine *machine, uint16_t opcode);
static void operation_B(Machine *machine, uint16_t opcode);
static void operation_C(Machine *machine, uint16_t opcode);
static void operation_D(Machine *machine, uint16_t opcode);
static void operation_E(Machine *machine, uint16_t opcode);
static void operation_F(Machine *machine, uint16_t opcode);

static opcode_table operation[16] = {
  &operation_0,
  &operation_1,
  &operation_2,
  &operation_3,
  &operation_4,
  &operation_5,
  &operation_6,
  &operation_7,
  &operation_8,
  &operation_9,
  &operation_A,
  &operation_B,
  &operation_C,
  &operation_D,
  &operation_E,
  &operation_F,
};

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
      uint16_t opcode = (machine->memory[machine->pc] << 8) |
                        machine->memory[machine->pc + 1];
      INCREMENT_PC(machine);
      uint8_t op = OPCODE(opcode);
      operation[op](machine, opcode);

      cycles = SDL_GetTicks();
    }

    if (SDL_GetTicks() - lastTicks > (1000 / 60)) {
      if (machine->delayTimer) {
        machine->delayTimer--;
      }

      if (machine->soundTimer) {
        machine->soundTimer--;
      }

      SDL_LockTexture(texture, NULL, &surface->pixels, &surface->pitch);
      expansion(machine->screen, (uint32_t *) surface->pixels);
      SDL_UnlockTexture(texture);

      // SDL_RenderClear(render);
      SDL_RenderCopy(render, texture, NULL, NULL);
      SDL_RenderPresent(render);

      lastTicks = SDL_GetTicks();
    }
  }

  destroy_window(window, render, texture);
}

/**
 *  00E0 - CLS - Clear the display
 *  00EE - RET - Return from a subroutine, set the program counter to the
 * address
 * */
void operation_0(Machine *machine, uint16_t opcode) {
  if (opcode == 0x00E0) {
    memset(machine->screen, 0x0, SCREEN_SIZE);
    printf("CLS\n");
  } else if (opcode == 0x00EE) {
    if (machine->sp > 0) {
      machine->pc = machine->stack[--machine->sp];
    }

    printf("RET\n");
  }
}

void operation_1(Machine *machine, uint16_t opcode) {
  uint16_t nnn = OPCODE_NNN(opcode);

  machine->pc = nnn;
  printf("JP addr: %d\n", nnn);
}

/**
 * 2nnn - CALL addr - Call subroutine at nnn
 * */
void operation_2(Machine *machine, uint16_t opcode) {
  uint16_t nnn = OPCODE_NNN(opcode);

  if (machine->sp < 16) {
    machine->stack[machine->sp++] = machine->pc;
  }

  machine->pc = nnn;

  printf("CALL addr: %d\n", nnn);
}

/**
 * 3xkk - SE Vx, byte
 * SE Vx, kk - Skip next instruction if Vx = kk
 * */
void operation_3(Machine *machine, uint16_t opcode) {
  uint8_t kk = OPCODE_KK(opcode);
  uint8_t x = OPCODE_X(opcode);

  if (machine->v[x] == kk) {
    INCREMENT_PC(machine);
  }

  printf("SE Vx, byte: %d, %d\n", x, kk);
}

/**
 * 4xkk - SNE Vx, byte
 * SNE Vx, kk - Skip next instruction if Vx != kk
 * */
void operation_4(Machine *machine, uint16_t opcode) {
  uint8_t kk = OPCODE_KK(opcode);
  uint8_t x = OPCODE_X(opcode);

  if (machine->v[x] != kk) {
    INCREMENT_PC(machine);
  }

  printf("SNE Vx, byte: %d, %d\n", x, kk);
}

/**
 * 5xy0 - SE Vx, Vy
 * SE Vx, Vy - Skip next instruction if Vx = Vy
 * */
void operation_5(Machine *machine, uint16_t opcode) {
  uint8_t x = OPCODE_X(opcode);
  uint8_t y = OPCODE_Y(opcode);

  if (machine->v[x] == machine->v[y]) {
    INCREMENT_PC(machine);
  }

  printf("SE Vx, Vy: %d, %d\n", x, y);
}

/**
 * 6xkk - LD Vx, byte
 * LD Vx, kk - Set Vx = kk
 *
 * Puts the value kk into register Vx. Constant value or register value.
 * */
void operation_6(Machine *machine, uint16_t opcode) {
  uint8_t kk = OPCODE_KK(opcode);
  uint8_t x = OPCODE_X(opcode);

  machine->v[x] = kk;
  printf("LD Vx, byte: %d, %d\n", x, kk);
}

/**
 * 7xkk - ADD Vx, byte
 * ADD Vx, kk - Add Vx = (Vx + kk) & 0xFF (8 bits)
 * */
void operation_7(Machine *machine, uint16_t opcode) {
  uint8_t kk = OPCODE_KK(opcode);
  uint8_t x = OPCODE_X(opcode);

  machine->v[x] = (machine->v[x] + kk) & 0xFF;
  printf("ADD Vx, byte: %d, %d\n", x, kk);
}

/**
 * 8xy0 - LD Vx, Vy - Set Vx = Vy
 * 8xy1 - OR Vx, Vy - Set Vx = Vx OR Vy
 * 8xy2 - AND Vx, Vy - Set Vx = Vx AND Vy
 * 8xy3 - XOR Vx, Vy - Set Vx = Vx XOR Vy
 * 8xy4 - ADD Vx, Vy - Set Vx = Vx + Vy, set VF if Vx + Vy > 255
 * 8xy5 - SUB Vx, Vy - Set Vx = Vx - Vy, set VF if Vx > Vy
 * 8xy6 - SHR Vx {, Vy} - Set Vx = Vx SHR 1 (divide by 2), set VF if Vx is odd
 * 8xy7 - SUBN Vx, Vy - Set Vx = Vy - Vx, set VF if Vy > Vx
 * 8xyE - SHL Vx {, Vy} - Set Vx = Vx SHL 1, set VF if Vx > 127
 * */
void operation_8(Machine *machine, uint16_t opcode) {
  uint8_t x = OPCODE_X(opcode);
  uint8_t y = OPCODE_Y(opcode);
  uint8_t n = OPCODE_N(opcode);

  switch (n) {
  case 0x0:
    machine->v[x] = machine->v[y];
    printf("LD Vx, Vy: %d, %d\n", x, y);
    break;
  case 0x1:
    machine->v[x] |= machine->v[y];
    printf("OR Vx, Vy: %d, %d\n", x, y);
    break;
  case 0x2:
    machine->v[x] &= machine->v[y];
    printf("AND Vx, Vy: %d, %d\n", x, y);
    break;
  case 0x3:
    machine->v[x] ^= machine->v[y];
    printf("XOR Vx, Vy: %d, %d\n", x, y);
    break;
  case 0x4:
    machine->v[0xF] = machine->v[x] > (machine->v[x] + machine->v[y]);
    machine->v[x] += machine->v[y];
    printf("ADD Vx, Vy: %d, %d\n", x, y);
    break;
  case 0x5:
    machine->v[0xF] = machine->v[x] > machine->v[y];
    machine->v[x] -= machine->v[y];
    printf("SUB Vx, Vy: %d, %d\n", x, y);
    break;
  case 0x6:
    machine->v[0xF] = (machine->v[x] & 1);
    machine->v[x] >>= 1;
    printf("SHR Vx: %d\n", x);
    break;
  case 0x7:
    machine->v[0xF] = machine->v[y] > machine->v[x];
    machine->v[x] = machine->v[y] - machine->v[x];
    printf("SUBN Vx, Vy: %d, %d\n", x, y);
    break;
  case 0xE:
    machine->v[0xF] = machine->v[x] >> 0x7;
    machine->v[x] <<= 1;
    printf("SHL Vx: %d\n", x);
    break;
  }
}

/**
 * 9xy0 - SNE Vx, Vy - Skip next instruction if Vx != Vy
 * */
void operation_9(Machine *machine, uint16_t opcode) {
  uint8_t x = OPCODE_X(opcode);
  uint8_t y = OPCODE_Y(opcode);

  if (machine->v[x] != machine->v[y]) {
    INCREMENT_PC(machine);
  }
  printf("SNE Vx, Vy: %d, %d\n", x, y);
}

/**
 * Annn - LD I, addr - Set I = nnn
 * */
void operation_A(Machine *machine, uint16_t opcode) {
  uint16_t nnn = OPCODE_NNN(opcode);

  machine->i = nnn;
  printf("LD I, addr: %d\n", nnn);
}

/**
 * Bnnn - JP V0, addr - Jump to location nnn + V0
 * */
void operation_B(Machine *machine, uint16_t opcode) {
  uint16_t nnn = OPCODE_NNN(opcode);

  machine->pc = MASK_FFF(nnn + machine->v[0]);
  printf("JP V0, addr: %d\n", nnn);
}

/**
 * Cxkk - RND Vx, byte - Set Vx = random byte AND kk
 * */
void operation_C(Machine *machine, uint16_t opcode) {
  uint8_t kk = OPCODE_KK(opcode);
  uint8_t x = OPCODE_X(opcode);

  machine->v[x] = rand() & kk;

  printf("RND Vx, byte: %d, %d\n", x, kk);
}

/**
 * Dxyn - DRW Vx, Vy, nibble - Display n-byte sprite starting at memory location
 *  I at (Vx, Vy), set VF = collision
 *
 * */
void operation_D(Machine *machine, uint16_t opcode) {
  uint8_t x = OPCODE_X(opcode);
  uint8_t y = OPCODE_Y(opcode);
  uint8_t n = OPCODE_N(opcode);

  machine->v[0xF] = 0;
  for (int j = 0; j < n; j++) {
    uint8_t sprite = machine->memory[machine->i + j];
    for (int i = 0; i < 8; i++) {
      int px = (machine->v[x] + i) & (SCREEN_WIDTH - 1);
      int py = (machine->v[y] + j) & (SCREEN_HEIGHT - 1);
      int position = (SCREEN_WIDTH * py) + px;
      int pixel = (sprite & (1 << (7 - i))) != 0;

      machine->v[0xF] |= (machine->screen[position] & pixel);
      machine->screen[position] ^= pixel;
    }
  }

  printf("DRW Vx, Vy, nibble: %d, %d, %d\n", x, y, n);
}

void operation_E(Machine *machine, uint16_t opcode) {
  uint8_t x = OPCODE_X(opcode);
  uint8_t kk = OPCODE_KK(opcode);

  if (kk == 0x9E) {
    // TODO: SKP Vx: Skip next instruction if key with the value of Vx is
    // pressed
    printf("SKP Vx: %d\n", x);
  } else if (kk == 0xA1) {
    // TODO: SKNP Vx: Skip next instruction if key with the value of Vx is
    // not pressed
    printf("SKNP Vx: %d\n", x);
  }
}

/**
 * Fx07 - LD Vx, DT - Set Vx = delay timer value
 * Fx0A - LD Vx, K - Wait for a key press, store the value of the key in Vx
 * Fx15 - LD DT, Vx - Set delay timer = Vx
 * Fx18 - LD ST, Vx - Set sound timer = Vx
 * Fx1E - ADD I, Vx - Set I = I + Vx
 * Fx29 - LD F, Vx - Set I = location of sprite for digit Vx
 * Fx33 - LD B, Vx - Store BCD representation of Vx in memory locations I,
 * Fx55 - LD [I], Vx: Store registers V0 through Vx in memory starting at
 *  location I I is set to I + X + 1 after operation
 * Fx65 - LD Vx, [I]: Read registers V0 through Vx from memory starting
 *  at location I
 * */
void operation_F(Machine *machine, uint16_t opcode) {
  uint8_t kk = OPCODE_KK(opcode);
  uint8_t x = OPCODE_X(opcode);

  switch (kk) {
  case 0x07:
    machine->v[x] = machine->delayTimer;
    printf("LD Vx, DT: %d\n", x);
    break;
  case 0x0A:
    // TODO: LD Vx, K: Wait for a key press, store the value of the key in
    // Vx
    printf("LD Vx, K: %d\n", x);
    break;
  case 0x15:
    machine->delayTimer = machine->v[x];
    printf("LD DT, Vx: %d\n", x);
    break;
  case 0x18:
    machine->soundTimer = machine->v[x];
    printf("LD ST, Vx: %d\n", x);
    break;
  case 0x1E:
    machine->i += machine->v[x];
    printf("ADD I, Vx: %d\n", x);
    break;
  case 0x29:
    machine->i = 0x50 + (machine->v[x] & 0xF) * 5;
    printf("LD F, Vx: %d\n", x);
    break;
  case 0x33:
    machine->memory[machine->i + 2] = machine->v[x] % 10;
    machine->memory[machine->i + 1] = (machine->v[x] / 10) % 10;
    machine->memory[machine->i] = machine->v[x] / 100;

    printf("LD B, Vx: %d\n", x);
    break;
  case 0x55:
    for (int reg = 0; reg <= x; reg++) {
      machine->memory[machine->i + reg] = machine->v[reg];
    }

    printf("LD [I], Vx: %d\n", x);
    break;
  case 0x65:
    for (int reg = 0; reg <= x; reg++) {
      machine->v[reg] = machine->memory[machine->i + reg];
    }

    printf("LD Vx, [I]: %d\n", x);
    break;
  }
}
