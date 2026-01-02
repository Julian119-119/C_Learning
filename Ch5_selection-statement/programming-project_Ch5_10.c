// This is my answer for programming project 10 in C Program: a modern approach

#include <stdio.h>

int main(void)
{
    int num, tens;

    printf("Enter numerical grade: ");
    scanf("%d", &num);

    tens = num / 10;

    printf("Letter grade: ");
    switch (tens) {
      case 10: case 9:
        printf("A\n");
        break;
      case 8:
        printf("B\n");
        break;
      case 7:
        printf("C\n");
        break;
      case 6:
        printf("D\n");
        break;
      default:
        printf("F\n");
    }

    return 0;
}
