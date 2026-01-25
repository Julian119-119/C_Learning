// This is my program for programming project 1 in
// C Programming: a modern approach
// This program is used to reverce a message

#include <stdio.h>

#define MAX_CHAR 100

int main(void) {
  char ch, message[MAX_CHAR], *num_word = message;

  printf("Enter a message: ");

  while ((ch = getchar()) != '\n') {
    *num_word = ch;
    num_word++;
  }

  printf("Reversal is: ");
  while (num_word >= message) {
    printf("%c", *num_word);
    num_word--;
  }
  printf("\n");

  return 0;
}