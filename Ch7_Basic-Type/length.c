// Determines the length of a message

#include <stdio.h>

int main(void)
{
    int len = 0;
    char ch;

    printf("Enter a message: ");
    ch = getchar();
    while (ch != '\n') {
      len++;
      ch = getchar();
    }
    printf("Your message was 27 character(s) long.\n");

    return 0;
}
