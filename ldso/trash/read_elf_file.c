#include <linux/mman.h>
#include <linux/stat.h>
#include <asm-generic/fcntl.h>
#include "unistd.h"
#include "readelf/header_info.h"
//#include "types.h"
//#include "string.h"

#define MAP_FAILED ((void *)-1)
#define SEEK_END 2
#define AT_FDCWD -100
int get_file_size(char *filename)
{
    struct statx st;
    statx(AT_FDCWD, filename, 0, STATX_SIZE, &st);
    return st.stx_size;
}

void *read_elf_file(char *filename, int *file_size, ElfW(Addr) addr)
{
    int filedes = open(filename, O_RDONLY);
    if (filedes == -1)
        return MAP_FAILED;
    *file_size = get_file_size(filename);
    if (*file_size == -1)
        return MAP_FAILED;
    int flags = MAP_FIXED_NOREPLACE | MAP_PRIVATE | MAP_DENYWRITE;
    void *file = mmap(addr, *file_size, PROT_READ | PROT_EXEC | PROT_WRITE, MAP_PRIVATE, filedes, 0);
    if (file == MAP_FAILED)
        return MAP_FAILED;
    set_elf_header(file);
    return file;
}

void free_file(char *ptr, int size)
{
    munmap(ptr, size);
}