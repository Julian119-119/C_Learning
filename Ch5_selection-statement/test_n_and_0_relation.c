//This is my program for example in C programming: a modern approach Ch5
//It is used to test whether n is les tna 0, equal to 0, or greater tnan 0
//Author:: Julian

#include <stdio.h>

int main(void)
{
  int n = 3;
  if (n < 0)
    printf("n is less than 0\n");
  else
    if (n == 0)
      printf("n is equal to 0\n");
    else
      printf("n is greater than 0\n");

  return 0;
}
