// This is my version 2 program for programming project 2 in C Programming: a modern approach Ch6
#include <stdio.h>

int main(void)
{
  int num1, num2, gcd;

  printf("Enter two integers: ");
  scanf("%d %d", &num1, &num2);

  if (num1 <= num2)
    gcd = num1;
  else
    gcd = num2;
  for (; num1 % gcd != 0 || num2 % gcd !=0; gcd--) ;

  printf("Greatest common divisor: %d\n", gcd);

  return 0;
}
