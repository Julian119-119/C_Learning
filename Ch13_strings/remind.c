// Prints a one-month reminder list

#include <stdio.h>
#include <string.h>

#define MAX_WORD 50
#define MAX_DAY 15

int read_and_format_line(char day_str[MAX_WORD], char msg_str[MAX_WORD], int n);
void read_line(char msg_str[MAX_WORD], int n);
void store_str(char month_str[MAX_DAY][MAX_WORD], char day_str[MAX_WORD],
               char (*next_empty_row)[MAX_WORD]);
void print_str(char month_str[MAX_DAY][MAX_WORD],
               char (*next_empty_row)[MAX_WORD]);

int main(void) {
  // 修正點：要存入一整個 row 的話，就必須要宣告一個
  // 一維陣列的指標
  char msg_str[MAX_WORD], day_str[MAX_WORD], month_str[MAX_DAY][MAX_WORD];
  char (*next_empty_row)[MAX_WORD] = month_str;

  for (;;) {
    // 判斷是否有位子繼續輸入
    if (next_empty_row >= month_str + MAX_DAY) {
      printf("---no space left---");
      break;
    }

    printf("Enter day and reminder: ");
    if (!read_and_format_line(day_str, msg_str, MAX_WORD)) {
      break;
    }

    // 將 day_str 儲存進 month_str 之中
    store_str(month_str, day_str, next_empty_row);
    next_empty_row++;
  }

  print_str(month_str, next_empty_row);

  return 0;
}

int read_and_format_line(char day_str[MAX_WORD], char msg_str[MAX_WORD],
                         int n) {
  int day;

  // 讀取前面的數字並格式化
  scanf("%2d", &day);
  // 判斷是否為 0
  if (!day) return 0;
  // 讀取剩餘的字
  read_line(msg_str, n);
  // 黏合數字與文字並儲存在 day_str 之中
  sprintf(day_str, "%2d %s", day, msg_str);

  return 1;
}

void read_line(char msg_str[], int n) {
  int ch;
  char* p;

  // 清空前面的空白
  while ((ch = getchar()) == ' ');

  // 輸入第一個字元
  msg_str[0] = ch;

  // 輸入第二個以後的字元
  for (p = msg_str + 1; (ch = getchar()) != '\n'; p++)
    if (p < msg_str + n - 1)
      *p = ch;
    else
      break;
  *p = '\0';
}

void store_str(char month_str[MAX_DAY][MAX_WORD], char day_str[MAX_WORD],
               char (*next_empty_row)[MAX_WORD]) {
  char (*row_position)[MAX_WORD] = month_str, (*move_row)[MAX_WORD];

  // 找出 day_str 所適合的位置
  while (strcmp(day_str, *row_position) >= 0 && row_position < next_empty_row) {
    row_position++;
  }

  // 從最後的 reminder (也就是 row) 開始移動
  // 空出空間給新的字串
  for (move_row = next_empty_row; row_position < move_row; move_row--) {
    strcpy(*move_row, *(move_row - 1));
  }

  // 新的字串放入正確的位子中
  // 修正點：因為之前指派 row_position 為 str
  // 所以當用上 * 的時候會變成 str (也就是陣列的位址)
  strcpy(*row_position, day_str);
}

void print_str(char month_str[MAX_DAY][MAX_WORD],
               char (*next_empty_row)[MAX_WORD]) {
  printf("\n");
  printf("Day Reminder\n");
  for (char (*p)[MAX_WORD] = month_str; p < next_empty_row; p++) {
    printf(" %s\n", *p);
  }
}
