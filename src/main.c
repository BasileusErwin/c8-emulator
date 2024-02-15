/**
 * Chip-8 Emulator
 * */
#include <cpu.h>
#include <machine.h>
#include <rom.h>

int main(int argc, char *argv[]) {
  Machine machine;
  init_machine(&machine);

  load_rom(&machine, "roms/PONG.bin");
  execute(&machine);

  return 0;
}
