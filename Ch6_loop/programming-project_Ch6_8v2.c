// This is my program for programming project 8 in C Program: a modern approach
// It is used to prints a one-month calendar

#include <stdio.h>

int main(void)
{
    int num_day, month_day, day_of_week;

    printf("Enter number of days in month: ");
    scanf("%d", &month_day);
    printf("Enter starting day of the week (1=Sun, 7=Sat): ");
    scanf("%d", &day_of_week);

    for (int i = 1; i != day_of_week; i++)
      printf("   ");
    for (num_day = 1; num_day <= month_day; num_day++, day_of_week++) {
      printf("%2d ", num_day);
      if (day_of_week == 7) {
        printf("\n");
        day_of_week = 0;
      }
    }
    printf("\n");

    return 0;
}
