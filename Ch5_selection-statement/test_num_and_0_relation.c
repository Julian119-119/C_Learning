//This is my program for example in C programming: a modern approach Ch5
//It is used to test whether the number is less tnan 0, equal to 0, or greater tnan 0
//Author:: Julian

#include <stdio.h>

int main(void)
{
  float n;

  printf("Enter a number: ");
  scanf("%f", &n);

  if (n < 0.00f)
    printf("n is less than 0\n");
  else
    if (n == 0.00f)
      printf("n is equal to 0\n");
    else
      printf("n is greater than 0\n");

  return 0;
}
