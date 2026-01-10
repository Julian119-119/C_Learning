// This is my program for programming project 15 (g) in C programming: a modern approach
// This program is used to compute the factorial of a positivie integer

#include <stdio.h>

int main(void)
{
    int n;
    long double factorial = 1.00L;

    printf("Enter a positive integer: ");
    scanf("%d", &n);

    if (n < 0)
      printf("Factorial is not defined for negative numbers.\n");
    else {
      for(int i = 1; i <= n; i++) {
        factorial *= i;
        }
      printf("Factorial of %d: %Lf\n",n, factorial);
    }

    return 0;
}
