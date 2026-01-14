// This is my program for programming project 1 in C Programming: a modern approach
// This program is used to sort a series of integers form low to high

#include <stdio.h>
#define MAX_LEN 100

void selection_sort(long a[], int n);

int main(void)
{
  int n = 0;
  long a[MAX_LEN];
  char ch;

  printf("Eneter a series of integers: ");
  do {
    scanf("%ld", &a[n]);
    n++;
    ch = getchar();
    // 先掃描下一個數字
    if (ch == '\n') break;
    // 測試下一個字元是否為 '\n'
    // 是的話就結束
  } while (n <= MAX_LEN);

  selection_sort(a, n);

  for (int i = 0; i < n; i++)
    printf("%ld ", a[i]);
  printf("\n");

  return 0;
}

void selection_sort(long a[], int no_element)
{
  int base_value = a[0], hollow = 0;
  int compare_num = no_element - 1;

  while (compare_num > 0) {
    while (compare_num > 0 && a[compare_num] <= base_value)
    // 修正點：有可能在內層就達到 0
      compare_num--;
    if (compare_num == 0) break;
    // 修正點：如果 compare_num 等於 0 的話就不應該更新數值
    hollow = compare_num;
    // 修正點：迴圈結束時 compare_num 會等於 0
    // 所以需要新的變數來儲存洞的位置
    base_value = a[compare_num--];
  }
  a[hollow] = a[no_element - 1];
  a[no_element - 1] = base_value;
  // 修正點：最後一格的位置要填的是最大的數字

  if (no_element <= 2) return;
  selection_sort(a, no_element - 1);
}
