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
    if (ch == '\n') break;
  } while (n <= MAX_LEN);

  selection_sort(a, n);

  for (int i = 0; i < n; i++)
    printf("%ld ", a[i]);
  printf("\n");

  return 0;
}

void selection_sort(long a[], int n)
{
  int max_index;
  long temp_num;

  max_index = 0;
  // 先假設 a[0] 是最大的

  for (int i = 1; i < n; i++)
    if (a[i] > a[max_index])
      max_index = i;
  // 掃描數字，將比較大的數字紀錄到 max_index 上

  temp_num = a[max_index];
  a[max_index] = a[n - 1];
  a[n - 1] = temp_num;
  // 交換數字

  if (n <= 2) return;
  selection_sort(a, n - 1);
}
