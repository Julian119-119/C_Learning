//This is myanswer for progrmming project 5 in c programming project Ch2

#include <stdio.h>

int main(void)
{
    float x, y;

    printf("Enter a value: ");
    scanf("%f", &x);

    y = ((((3 * x +2) * x - 5) * x - 1) * x + 7) * x - 6;
    printf("%.2f\n", y);

    return 0;
}
