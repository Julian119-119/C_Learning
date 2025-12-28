//This is my answer for programming project 4 in c program : a modern approach Ch2

#include <stdio.h>

int main(void)
{
    float amount;

    printf("Enter an amount: ");
    scanf("%f", &amount);

    printf("With tax added: %.2f\n", amount * 1.05);

    return 0;
}
