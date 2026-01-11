// Prints a table of compound interest

#define PERCENT 0.01
#define NUM_RATE ((int)(sizeof(money) / sizeof(money[0])))
#include <stdio.h>

int main(void)
{
    float  money[5];
    int rate, num_year, initial_money;

    printf("Enter initial investment amount: ");
    scanf("%d", &initial_money);
    for (int i = 0; i < NUM_RATE; i++)
      money[i] = initial_money;
    printf("Enter interest rate: ");
    scanf("%d", &rate);
    printf("Enter number of years: ");
    scanf("%d", &num_year);

    printf("\n");

    printf("years   ");
    for (int i = 0; i <= 4; i++) {
      printf("%3d%%   ", rate + i);
    }
    printf("\n");

    for (int i = 1; i <= num_year; i++) {
      printf("%3d     ", i);
      for(int y = 0; y < NUM_RATE; y++) {
        money[y] *= (1 + (rate + y) * PERCENT);
        printf("%6.2f ", money[y]);
      }
      printf("\n");
    }
    printf("\n");
    return 0;
}
