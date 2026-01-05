// This is my program for programming project 6 in C Programming: a modern approach
// This is used to prompts the user to enter a number n,
// then prints all even squares between 1 and n

#include <stdio.h>

int main(void)
{
    int n, i;

    printf("Enter a number n: ");
    scanf("%d", &n);

    for (i = 2; i * i <= n; i += 2)
      printf("%d\n", i * i);

    return 0;
}
