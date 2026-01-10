// This is my program for programming project 13 in C Programming: a modern approach
// This program is used to calculate the average word length for a sentence

#include <stdio.h>

int main(void)
{
    char ch;
    int i = 0, len = 0;
    float ave_len;

    printf("Enter a sentence: ");
    for (;;) {
      ch = getchar();
      if (ch == '\n') {
        i++;
        break;
      }
      else if (ch == ' ')
        i++;
      else
        len++;
    }
    ave_len = (float) len / i;

    printf("Average word length: %.2f\n", ave_len);

    return 0;
}
