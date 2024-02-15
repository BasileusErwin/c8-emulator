#include <machine.h>
#include <memory.h>

/**
 * Initialize the machine
 *
 * pc     - Initialize the program counter to 0x200 for the start of the program
 * memory - Set all memory to 0
 * stack  - Set all stack values to 0
 * v      - Set all register values to 0
 *
 * @param machine The machine to initialize
 * */
void init_machine(Machine *machine) {
  memset(machine, 0x00, sizeof(Machine));
  memset(machine->memory, 0x00, sizeof(machine->memory));
  memset(machine->stack, 0x00, sizeof(machine->stack));
  memset(machine->v, 0x00, sizeof(machine->stack));

  machine->pc = 0x200;
  machine->sp = 0;
  machine->i = 0;
  machine->delayTimer = 0;
  machine->soundTimer = 0;
}
