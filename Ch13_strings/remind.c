// Prints a one-month reminder list

#include <stdio.h>
#include <string.h>

#define MAX_WORD 50
#define MAX_DAY 15

// prototype
int read_line(void);
void store_str(char (*last_reminder_row)[MAX_WORD]);
void print_str(char (*last_reminder_row)[MAX_WORD]);

// external variable
char str[MAX_DAY][MAX_WORD], temp_str[MAX_WORD];

int main(void) {
  // 修正點：要存入一整個 row 的話，就必須要宣告一個
  // 一維陣列的指標
  char (*last_reminder_row)[MAX_WORD] = str;

  for (;;) {
    printf("Enter day and reminder: ");
    if (read_line() == 1) {
      break;
    }
    store_str(last_reminder_row);
    last_reminder_row++;
  }

  print_str(last_reminder_row);

  return 0;
}

int read_line(void) {
  int ch;
  char* p;

  // 檢查第一個字元是否為 0
  if ((ch = getchar()) == '0') {
    return 1;
  } else {
    temp_str[0] = ch;
  }

  // 輸入第二個以後的字元
  for (p = temp_str + 1; (ch = getchar()) != '\n'; p++)
    if (p < temp_str + MAX_WORD - 1)
      *p = ch;
    else
      break;
  *p = '\0';

  return 0;
}

void store_str(char (*last_reminder_row)[MAX_WORD]) {
  // 修正點：
  char (*row_position)[MAX_WORD] = str, (*move_row)[MAX_WORD];

  // 找出 temp_str 所適合的位置
  while (strcmp(temp_str, *row_position) < 0 &&
         row_position < last_reminder_row) {
    row_position++;
  }

  // 從最後的 reminder (也就是 row) 開始移動
  // 空出空間給新的字串
  for (move_row = last_reminder_row; row_position <= move_row; move_row--) {
    strcpy(move_row[1], *move_row);
  }

  // 新的字串放入正確的位子中
  // 修正點：因為之前指派 row_position 為 str
  // 所以當用上 * 的時候會變成 str (也就是陣列的位址)
  strcpy(*row_position, temp_str);
}

void print_str(char (*last_reminder_row)[MAX_WORD]) {
  printf("\n");
  for (char (*p)[MAX_WORD] = str; p <= last_reminder_row; p++) {
    printf("%s\n", *p);
  }
}