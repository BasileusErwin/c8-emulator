#include <cpu.h>
#include <machine.h>
#include <rom.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  Machine machine;
  init_machine(&machine);

  if (argc == 1) {
    printf("Usage: c8 <ROMFILE>\n");
    exit(1);
  }

  load_rom(&machine, argv[1]);
  execute(&machine);

  return 0;
}
