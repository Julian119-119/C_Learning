// Sums a series of numbers (using long variables)

#include <stdio.h>

int main(void)
{
   long i, sum = 0;

    printf("This program sums a series of integers\n");

    printf("Enter integers (0 to terminate): ");
    scanf("%ld", &i);

    while (i != 0) {
      sum += i;
      scanf("%ld", &i);
    }
    printf("The sum is: %ld\n", sum);

    return 0;
}

