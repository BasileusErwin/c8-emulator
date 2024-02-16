#include <cpu.h>
#include <machine.h>
#include <rom.h>

int main(int argc, char *argv[]) {
  Machine machine;
  init_machine(&machine);

  load_rom(&machine, "roms/UFO");
  execute(&machine);

  return 0;
}
