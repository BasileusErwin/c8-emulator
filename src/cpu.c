#include <cpu.h>

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
  &operation_0, &operation_1, &operation_2, &operation_3,
  &operation_4, &operation_5, &operation_6, &operation_7,
  &operation_8, &operation_9, &operation_A, &operation_B,
  &operation_C, &operation_D, &operation_E, &operation_F,
};

void execute(Machine *machine) {
  int mustExit = 0;

  while (!mustExit) {
    uint16_t opcode =
        machine->memory[machine->pc] << 8 | machine->memory[machine->pc + 1];

    if ((machine->pc += 2) == MEM_SIZE) {
      mustExit = 1;
      machine->pc = 0;
    }

    uint8_t op = OPCODE(opcode);

    operation[op](machine, opcode);
  }
}

void operation_0(Machine *machine, uint16_t opcode) {
  if (opcode == 0x00E0) {
    // TODO: CLS: Clear the screen
    printf("CLS\n");
  } else if (opcode == 0x00EE) {
    // TODO: RET: Return from a subroutine
    printf("RET\n");
  }
}

void operation_1(Machine *machine, uint16_t opcode) {
  uint16_t nnn = OPCODE_NNN(opcode);

  // TODO: JP addr: Jump to location nnn
  printf("JP addr: %d\n", nnn);
}

void operation_2(Machine *machine, uint16_t opcode) {
  uint16_t nnn = OPCODE_NNN(opcode);
  // TODO: CALL addr: Call subroutine at nnn
  printf("CALL addr: %d\n", nnn);
}

void operation_3(Machine *machine, uint16_t opcode) {
  uint8_t kk = OPCODE_KK(opcode);
  uint8_t x = OPCODE_X(opcode);
  // TODO: SE Vx, byte: Skip next instruction if Vx = kk
  printf("SE Vx, byte: %d, %d\n", x, kk);
}

void operation_4(Machine *machine, uint16_t opcode) {
  uint8_t kk = OPCODE_KK(opcode);
  uint8_t x = OPCODE_X(opcode);

  // TODO: SNE Vx, byte: Skip next instruction if Vx != kk
  printf("SNE Vx, byte: %d, %d\n", x, kk);
}

void operation_5(Machine *machine, uint16_t opcode) {
  uint8_t x = OPCODE_X(opcode);
  uint8_t y = OPCODE_Y(opcode);

  // TODO: SE Vx, Vy: Skip next instruction if Vx = Vy
  printf("SE Vx, Vy: %d, %d\n", x, y);
}

void operation_6(Machine *machine, uint16_t opcode) {
  uint8_t kk = OPCODE_KK(opcode);
  uint8_t x = OPCODE_X(opcode);

  // TODO: LD Vx, byte: Set Vx = kk
  printf("LD Vx, byte: %d, %d\n", x, kk);
}

void operation_7(Machine *machine, uint16_t opcode) {
  uint8_t kk = OPCODE_KK(opcode);
  uint8_t x = OPCODE_X(opcode);
  // TODO: ADD Vx, byte: Set Vx = Vx + kk
  printf("ADD Vx, byte: %d, %d\n", x, kk);
}

void operation_8(Machine *machine, uint16_t opcode) {
  uint8_t x = OPCODE_X(opcode);
  uint8_t y = OPCODE_Y(opcode);
  uint8_t n = OPCODE_N(opcode);

  switch (n) {
  case 0x0:
    break;
  case 0x1:
    // TODO: OR Vx, Vy: Set Vx = Vx OR Vy
    printf("OR Vx, Vy: %d, %d\n", x, y);
    break;
  case 0x2:
    // TODO: AND Vx, Vy: Set Vx = Vx AND Vy
    printf("AND Vx, Vy: %d, %d\n", x, y);
    break;
  case 0x3:
    // TODO: XOR Vx, Vy: Set Vx = Vx XOR Vy
    printf("XOR Vx, Vy: %d, %d\n", x, y);
    break;
  case 0x4:
    // TODO: ADD Vx, Vy: Set Vx = Vx + Vy, set VF = carry
    printf("ADD Vx, Vy: %d, %d\n", x, y);
    break;
  case 0x5:
    // TODO: SUB Vx, Vy: Set Vx = Vx - Vy, set VF = NOT borrow
    printf("SUB Vx, Vy: %d, %d\n", x, y);
    break;
  case 0x6:
    // TODO: SHR Vx {, Vy}: Set Vx = Vx SHR 1
    printf("SHR Vx: %d\n", x);
    break;
  case 0x7:
    // TODO: SUBN Vx, Vy: Set Vx = Vy - Vx, set VF = NOT borrow
    printf("SUBN Vx, Vy: %d, %d\n", x, y);
    break;
  case 0xE:
    // TODO: SHL Vx {, Vy}: Set Vx = Vx SHL 1
    printf("SHL Vx: %d\n", x);
    break;
  }
}

void operation_9(Machine *machine, uint16_t opcode) {
  uint8_t x = OPCODE_X(opcode);
  uint8_t y = OPCODE_Y(opcode);
  // TODO: SNE Vx, Vy: Skip next instruction if Vx != Vy
  printf("SNE Vx, Vy: %d, %d\n", x, y);
}

void operation_A(Machine *machine, uint16_t opcode) {
  uint16_t nnn = OPCODE_NNN(opcode);
  // TODO: LD I, addr: Set I = nnn
  printf("LD I, addr: %d\n", nnn);
}

void operation_B(Machine *machine, uint16_t opcode) {
  uint16_t nnn = OPCODE_NNN(opcode);
  // TODO: JP V0, addr: Jump to location nnn + V0
  printf("JP V0, addr: %d\n", nnn);
}

void operation_C(Machine *machine, uint16_t opcode) {
  uint8_t kk = OPCODE_KK(opcode);
  uint8_t x = OPCODE_X(opcode);
  // TODO: RND Vx, byte: Set Vx = random byte AND kk
  printf("RND Vx, byte: %d, %d\n", x, kk);
}

void operation_D(Machine *machine, uint16_t opcode) {
  uint8_t x = OPCODE_X(opcode);
  uint8_t y = OPCODE_Y(opcode);
  uint8_t n = OPCODE_N(opcode);

  // TODO: DRW Vx, Vy, nibble: Display n-byte sprite starting at memory
  // location I at (Vx, Vy), set VF = collision
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

void operation_F(Machine *machine, uint16_t opcode) {
  uint8_t kk = OPCODE_KK(opcode);
  uint8_t x = OPCODE_X(opcode);

  switch (kk) {
  case 0x07:
    // TODO: LD Vx, DT: Set Vx = delay timer value
    printf("LD Vx, DT: %d\n", x);
    break;
  case 0x0A:
    // TODO: LD Vx, K: Wait for a key press, store the value of the key in
    // Vx
    printf("LD Vx, K: %d\n", x);
    break;
  case 0x15:
    // TODO: LD DT, Vx: Set delay timer = Vx
    printf("LD DT, Vx: %d\n", x);
    break;
  case 0x18:
    // TODO: LD ST, Vx: Set sound timer = Vx
    printf("LD ST, Vx: %d\n", x);
    break;
  case 0x1E:
    // TODO: ADD I, Vx: Set I = I + Vx
    printf("ADD I, Vx: %d\n", x);
    break;
  case 0x29:
    // TODO: LD F, Vx: Set I = location of sprite for digit Vx
    printf("LD F, Vx: %d\n", x);
    break;
  case 0x33:
    // TODO: LD B, Vx: Store BCD representation of Vx in memory locations I,
    // I+1, and I+2
    printf("LD B, Vx: %d\n", x);
    break;
  case 0x55:
    // TODO: LD [I], Vx: Store registers V0 through Vx in memory starting at
    // location I I is set to I + X + 1 after operation
    printf("LD [I], Vx: %d\n", x);
    break;
  case 0x65:
    // TODO: LD Vx, [I]: Read registers V0 through Vx from memory starting
    // at location I
    printf("LD Vx, [I]: %d\n", x);
    break;
  }
}
