// This is my version 3 program for programming project 2 in C Programming: a modern approach Ch6

#include <stdio.h>

int main(void)
{
  int m, n, remainder;

  printf("Enter two integers: ");
  scanf("%d %d", &m, &n);

  while (n != 0) {
    remainder = m % n;
    m = n;
    n = remainder;
  }

  printf("Greatest common divisor: %d\n", m);

  return 0;
}
