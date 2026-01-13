// Prints a countdown

#include <stdio.h>

void printf_count(int n)
{
  printf("T minus %d and counting\n", n);
}

int main(void)
{
  for (int i = 10; i > 0; i--)
    printf_count(i);

  return 0;
}
