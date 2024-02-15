#ifndef CHIP_8_MACHINE_H
#define CHIP_8_MACHINE_H

#include <stdint.h>
#include <stdio.h>

#define MEM_SIZE 4096 // 4K memory in bytes

/**
 * En el chip-8 hay 35 opcodes, cada uno de 2 bytes
 *
 * 0x0NNN - SYS addr
 * 0x00E0 - CLS
 * 0x00EE - RET
 * 0x1NNN - JP addr
 * 0x2NNN - CALL addr
 * ...
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
#define OPCODE_X(opcode) ((opcode & OPCODE_X_MASK) >> 8)
#define OPCODE_Y(opcode) ((opcode & OPCODE_Y_MASK) >> 4)
#define OPCODE_N(opcode) (opcode & OPCODE_N_MASK)
#define OPCODE(opcode) (opcode >> 12)

/**
 * Chip-8 Machine
 *
 * mem        - 4k memory
 * v          - 16 8-bit registers
 *              - If need access a register use v[0] to v[15]
 *              - Example: v[8] = V8; v[15] = VF
 * i          - 16-bit register
 * pc         - 16-bit program counter
 * sp         - 8-bit stack pointer
 * stack      - 16 16-bit values
 *              - Stack pointer is used to point to the top of the stack
 * delayTimer - 8-bit delay timer
 * soundTimer - 8-bit sound timer
 * */
typedef struct machine_t {
  uint8_t memory[MEM_SIZE];       // 4k memory
  uint16_t pc;                    // Program counter
  uint8_t sp;                     // Stack pointer
  uint16_t stack[16];             // Stack
  uint8_t v[16];                  // Vx registers
  uint16_t i;                     // I register
  uint8_t delayTimer, soundTimer; // Delay timer
} Machine;

void init_machine(Machine *machine);

#endif
