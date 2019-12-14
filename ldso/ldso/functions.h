#ifndef FUNCTION_H
#define FUNCTION_H

#include <link.h>
#include <elf.h>
#include "elf_manipulation.h"

char **build_dependency_table(char *executable_name);
void load_program(elf_phdr *program, elf_ehdr *elf, struct link_map *map, elf_addr interp);
elf_addr load_elf_binary(struct link_map *map, elf_addr interp);
struct link_map *build_link_map(char **table, elf_addr interp);

#endif /* !FUNCTION_H */
