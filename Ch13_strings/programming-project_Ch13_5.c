// This is my program for programming project 5
// in C Programming: a modern approach
// This program is uesed to add up its command-line arguments

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) { 
    int sum; 

    for (char **p = &argv[1]; *p != NULL; p++) {
        sum += atoi(*p);
    }

    printf("Total: %d\n", sum);

    return 0;
}