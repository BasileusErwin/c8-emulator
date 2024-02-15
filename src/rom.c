#include <rom.h>

/**
 * Load ROM into memory
 *
 * @param machine - Machine
 * */
void load_rom(Machine *machine, const char *path) {
  FILE *rom = fopen(path, "r");

  if (rom == NULL) {
    printf("Error: Could not open ROM file\n");
    exit(1);
  }

  fseek(rom, 0, SEEK_END);
  int lenght = ftell(rom);
  fseek(rom, 0, SEEK_SET);

  if (lenght > MEM_SIZE - 0x200) {
    printf("Error: ROM file too large\n");
    exit(1);
  }

  fread(machine->memory + 0x200, lenght, 1, rom);

  fclose(rom);
}
