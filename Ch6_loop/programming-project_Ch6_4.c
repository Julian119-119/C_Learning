// Calculates a broker's commision version 2
// This is my program for programming project 4 in C Programming: a modern approach

#include <stdio.h>
#define percent 0.01f

int main(void)
{
    float commission, value;

    printf("0=exit\n");

    for (;;) {
      printf("Enter value of trade: ");
      scanf("%f", &value);
      if (value == 0.00f)
        break;
      else if (value < 2500.00f)
        commission = 30.00f + 1.7f * percent * value;
      else if (value < 6250.00f)
        commission = 56.00f + 0.66f * percent * value;
      else if (value < 20000.00f)
        commission = 76.00f + 0.34f * percent * value;
      else if (value < 50000.00f)
        commission = 100.00f + 0.22f * percent * value;
      else if (value < 500000.00f)
        commission = 155.00f + 0.11f * percent * value;
      else
        commission = 255.00f + 0.22f * percent * value;
      printf("Commission: $%.2f\n", commission);
      printf("\n");
      }

    return 0;
}
