#ifndef CHIP_8_MACHINE_H
#define CHIP_8_MACHINE_H

#include <stdint.h>
#include <stdio.h>

#define MEM_SIZE 4096 // 4K memory in bytes

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define SCREEN_SIZE SCREEN_WIDTH *SCREEN_HEIGHT

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
 * screen     - 64x32 screen
 *              - Each pixel is a byte
 *              - 0x00 is off
 *              - 0x01 is on
 * waitKey   - Wait for a key press
 * */
typedef struct machine_t {
  uint8_t memory[MEM_SIZE];       // 4k memory
  uint16_t pc;                    // Program counter
  uint8_t sp;                     // Stack pointer
  uint16_t stack[16];             // Stack
  uint8_t v[16];                  // Vx registers
  uint16_t i;                     // I register
  uint8_t delayTimer, soundTimer; // Delay timer
  char screen[SCREEN_SIZE];       // 64x32 screen
  char waitKey;                   // Wait for a key press
} Machine;

void init_machine(Machine *machine);
void expansion(char *from, uint32_t *to);

#endif
