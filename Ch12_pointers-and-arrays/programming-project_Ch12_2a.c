// This is my program for programming project 2 (a)
// in C Programming: a modern approach
// This program is used to checks whether it's a palindrome

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_NUM 100

// external variable
char message[MAX_NUM];
int num_word = 0;

// prototype
void read_message(void);
bool check_palin(void);

int main(void) {
  printf("Enter a message: ");
  read_message();

  if (check_palin())
    printf("Palindrome\n");
  else
    printf("Not a palindrome\n");

  return 0;
}

void read_message(void) {
  char ch;

  while ((ch = getchar()) != '\n') {
    message[num_word] = toupper(ch);
    num_word++;
  }
}

bool check_palin(void) {
  int initial_num_word = 0;

  while (initial_num_word < num_word) {
    // 檢查是否是字母
    if (message[num_word] > 'Z' || message[num_word] < 'A') {
      num_word--;
      continue;
    }
    if (message[initial_num_word] > 'Z' || message[initial_num_word] < 'A') {
      initial_num_word++;
      continue;
    }

    // 檢查是否為 palindrome
    if (message[initial_num_word] == message[num_word]) {
      initial_num_word++;
      num_word--;
      continue;
    } else {
      return false;
    }
  }
  return true;
}