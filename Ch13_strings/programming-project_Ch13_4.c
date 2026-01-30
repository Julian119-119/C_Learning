//// This is my program for programming project 4
// in C Programming: a modern approach
// This program is used to echoes its command-line arguments
// in reverse

#include <stdio.h>

int main(int argc, char *argv[]) {
    for (char **p = &argv[argc - 1]; p > &argv[0]; p--)
      printf("%s ", *p);
    printf("\n");
}