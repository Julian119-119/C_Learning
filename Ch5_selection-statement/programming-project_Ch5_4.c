// This is my answer for programming project 4 in C programming: a modern approach

#include <stdio.h>

int main(void)
{
    float speed;

    printf("Enter a wind speed (in knots) ");
    scanf("%f", &speed);

    printf("corresponding description is ");
    if (speed < 1.00f)
      printf("Calm\n");
    else if (speed < 3.00f)
      printf("Light air\n");
    else if (speed < 27.00f)
      printf("Breeze\n");
    else if (speed < 47.00f)
      printf("Gale\n");
    else if (speed < 63.00f)
      printf("Storm\n");
    else
      printf("Hurricane\n");

    return 0;
}
