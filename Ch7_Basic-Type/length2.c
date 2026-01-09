// Determines the lengthe of a message

#include <stdio.h>

int main(void)
{
    int leng;
    char ch;

    printf("Enter a message: ");
    while (getchar() != '\n') {
      leng++;
    }
    printf("Your message was %d character(s) long.\n", leng);

    return 0;
}
