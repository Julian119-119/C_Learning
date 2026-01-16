// This is my program for programming project 7 in C Programming: a modern
// approach This program is used to prompts the user for a number and then
// displays the number

#include <stdio.h>
#include <ctype.h>

#define MAX_DIGITS 100

// external variable
// segments: 數字與哪一個位置要亮的對照表
const int segments[10][7] = {{1, 1, 1, 1, 1, 1, 0},   // 0
                             {0, 1, 1, 0, 0, 0, 0},   // 1
                             {1, 1, 0, 1, 1, 0, 1},   // 2
                             {1, 1, 1, 1, 0, 0, 1},   // 3
                             {0, 1, 1, 0, 0, 1, 1},   // 4
                             {1, 0, 1, 1, 0, 1, 1},   // 5
                             {1, 0, 1, 1, 1, 1, 1},   // 6
                             {1, 1, 1, 0, 0, 0, 0},   // 7
                             {1, 1, 1, 1, 1, 1, 1},   // 8
                             {1, 1, 1, 1, 0, 1, 1}};  // 9
// digits: 展示最終數字的顯示結果，每一個數字為 4 X 3，且
//         最旁邊要留一個空白的 col 區隔其他數字，所以為
//         4 X 4
char digits[4][MAX_DIGITS * 4];

// prototype
void clear_digits_array(void);
void process_digit(int num, int position);
void print_digits_array(int read_num);

int main(void) {
  int num, position = 0, read_num = 0;
  char ch;

  clear_digits_array();
  printf("Enter a number: ");
  while ((ch = getchar()) != '\n' && position < MAX_DIGITS) {
    if (isdigit(ch)) {
        num = ch - '0';
        process_digit(num, position);
        read_num++;
        position++;
    }
  }
  print_digits_array(read_num);

  return 0;
}

// clear_digits_array: 清空 digits[][]
void clear_digits_array(void) {
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < MAX_DIGITS * 4; col++) {
      digits[row][col] = ' ';
    }
  }
}

// process_digit: 將數字轉換成 seven-segment number，
//                並儲存進 digits[][]
void process_digit(int num, int position) {
  int array_position = position * 4;

  for (int i = 0; i < 7; i++) {
    if (segments[num][i]) {
      switch (i) {
        case 0:
          digits[0][array_position + 1] = '_';
          break;
        case 1:
          digits[1][array_position + 2] = '|';
          break;
        case 2:
          digits[2][array_position + 2] = '|';
          break;
        case 3:
          digits[2][array_position + 1] = '_';
          break;
        case 4:
          digits[2][array_position + 0] = '|';
          break;
        case 5:
          digits[1][array_position + 0] = '|';
          break;
        case 6:
          digits[1][array_position + 1] = '_';
          break;
      }
    }
  }
}

// 印出數字
void print_digits_array(int read_num) {
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < read_num * 4; col++) {
      switch (digits[row][col]) {
        case ' ':
          printf(" ");
          break;
        case '|':
          printf("|");
          break;
        case '_':
          printf("_");
          break;
      }
    }
    printf("\n");
  }
  printf("\n");
}

