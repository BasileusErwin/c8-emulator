#ifndef CHIP_8_CPU_H
#define CHIP_8_CPU_H

#include <machine.h>
#include <stdlib.h>

/**
 * En el chip-8 hay 35 opcodes, cada uno de 2 bytes
 *
 * 0x00E0 - CLS
 * 0x00EE - RET
 * 0x1NNN - JP addr
 * 0x2NNN - CALL addr
 * 0x3XKK - SE Vx, byte
 * 0x4XKK - SNE Vx, byte
 * 0x5XY0 - SE Vx, Vy
 * 0x6XKK - LD Vx, byte
 * 0x7XKK - ADD Vx, byte
 * 0x8XY0 - LD Vx, Vy
 * 0x8XY1 - OR Vx, Vy
 * 0x8XY2 - AND Vx, Vy
 * 0x8XY3 - XOR Vx, Vy
 * 0x8XY4 - ADD Vx, Vy
 * 0x8XY5 - SUB Vx, Vy
 * 0x8XY6 - SHR Vx {, Vy}
 * 0x8XY7 - SUBN Vx, Vy
 * 0x8XYE - SHL Vx {, Vy}
 * 0x9XY0 - SNE Vx, Vy
 * 0xANNN - LD I, addr
 * 0xBNNN - JP V0, addr
 * 0xCXKK - RND Vx, byte
 * 0xDXYN - DRW Vx, Vy, nibble
 * 0xEX9E - SKP Vx
 * 0xEXA1 - SKNP Vx
 * 0xFX07 - LD Vx, DT
 * 0xFX0A - LD Vx, K
 * 0xFX15 - LD DT, Vx
 * 0xFX18 - LD ST, Vx
 * 0xFX1E - ADD I, Vx
 * 0xFX29 - LD F, Vx
 * 0xFX33 - LD B, Vx
 * 0xFX55 - LD [I], Vx
 * 0xFX65 - LD Vx, [I]
 *
 * Para sacar los valores de las operaciones es necesario aplicar una mascarda
 * de bits, para obtener los valores de NNN, X, Y y N.
 *
 * Para las operaciones:
 *   - NNN: NNN es el valor de 12 bits menos significativos
 *   - KK: KK es el valor de 8 bits menos significativos
 *   - X: X es el valor de 4 bits más significativos
 *   - Y: Y es el valor de 4 bits menos significativos
 * */
#define OPCODE_NNN_MASK 0x0FFF
#define OPCODE_KK_MASK 0xFF
#define OPCODE_X_MASK 0xF
#define OPCODE_Y_MASK 0xF
#define OPCODE_N_MASK 0xF

#define OPCODE_NNN(opcode) (opcode & OPCODE_NNN_MASK)
#define OPCODE_KK(opcode) (opcode & OPCODE_KK_MASK)
#define OPCODE_X(opcode) ((opcode >> 8) & OPCODE_X_MASK)
#define OPCODE_Y(opcode) ((opcode >> 4) & OPCODE_Y_MASK)
#define OPCODE_N(opcode) (opcode & OPCODE_N_MASK)
#define OPCODE(opcode) (opcode >> 12)

#define MASK_FFF(n) (n) & 0xFFF

/**
 * Incrementa el contador de programa en 2
 * */
#define INCREMENT_PC(machine) machine->pc = MASK_FFF(machine->pc + 2)

void execute(Machine *machine);

#endif
