#ifndef CHIP_8_MACHINE_H
#define CHIP_8_MACHINE_H

#include <stdint.h>
#include <stdio.h>

#define MEM_SIZE 4096

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
  uint8_t mem[MEM_SIZE];          // 4k memory
  uint16_t pc;                    // Program counter
  uint8_t sp;                     // Stack pointer
  uint16_t stack[16];             // Stack
  uint8_t v[16];                  // Vx registers
  uint16_t i;                     // I register
  uint8_t delayTimer, sountTimer; // Delay timer
} Machine;

#endif
