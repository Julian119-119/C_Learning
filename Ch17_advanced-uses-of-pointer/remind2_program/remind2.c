// Prints a one-month reminder list (dynamic string version)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read_line.h"

#define MAX_REMIND 50  // maximum number of reminders
#define MSG_LEN 60     // max length of reminder message

int main(void) {
  char* reminders[MAX_REMIND];
  char day_str[3], msg_str[MSG_LEN + 1];
  int day, i, j, num_remind = 0;

  for (;;) {
    // 功能：判斷是否超過能儲存的總數
    // 不同點：這裡的判斷方式是以計數的形式來判斷，
    //         而我的則是以二維陣列中下一個空白的
    //         row 是否超出二維陣列來判斷。
    if (num_remind == MAX_REMIND) {
      printf("-- No space left --\n");
      break;
    }

    // 功能：格式化輸入數字，並判斷是否為零
    printf("Enter day and reminder: ");
    scanf("%2d", &day);
    if (day == 0) break;
    // 將格式化後的 day 放入 day_str 中
    sprintf(day_str, "%2d", day);
    read_line(msg_str, MSG_LEN);

    // 找尋適合 day_str 的位址
    // 並將其儲存進 i
    for (i = 0; i < num_remind; i++) {
      if (strcmp(day_str, reminders[i]) < 0) break;
    }
    // 移動騰出空間給 j
    // 如果是第一格字串的話，根本就不會被移動
    for (j = num_remind; j > i; j--) reminders[j] = reminders[j - 1];

    // 分配空間給 reminders 好讓它可以儲存字串
    reminders[i] = malloc(2 + strlen(msg_str) + 1);
    if (reminders[i] == NULL) {
      printf("--No space left --\n");
      break;
    }

    strcpy(reminders[i], day_str);
    strcat(reminders[i], msg_str);
  }
}
