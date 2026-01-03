// Calculates the number of digits in an integer

#include <stdio.h>

int main(void)
{
    int num, times = 0;

    printf("Enter a nonnegative integer: ");
    scanf("%d", &num);

    do {
      num /= 10;
      ++times;
    } while (num != 0);

    printf("The number has %d ", times);
    if (times != 1)
      printf("digits");
    else
      printf("digit");
    printf(".\n");

    return 0;
}
