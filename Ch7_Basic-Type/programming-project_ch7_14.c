// This is my program for programming project 14 in c programming: a modern approach
// This program is used to find a square root for a positive number by Neqton's method

#include <stdio.h>
#include <math.h>

int main(void)
{
    double old_y, y = 1.00;
    int x;

    printf("Enter a positive number: ");
    scanf("%d", &x);

    do {
      old_y = y;
      y = (x/y + old_y) / 2;
    } while (fabs(y - old_y) > .00001);

    printf("Square root: %lf\n", y);

    return 0;
}
