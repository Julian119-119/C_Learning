// This is my answer for project 2 in C programming: a modern approach Ch5

#include <stdio.h>

int main(void)
{
    int hr, min;

    printf("Enter a 24-hour time: ");
    scanf("%d :%d", &hr, &min);

    printf("Equivalent 12-hour time: ");
    if (hr <= 12)
      printf("%d:%.2d AM\n", hr, min);
    else
      printf("%d:%.2d PM\n", hr - 12, min);

    return 0;
}
