// sort an array of integers using Quicksort algorithm

#include <stdio.h>
#define N 10

void quicksort(int a[], int low, int high);
int split(int a[], int low, int high);

int main(void)
{
  int a[N];

  printf("Enter 10 numbers to be sorted: ");
  for (int i = 0; i < N; i++)
    scanf("%d", &a[i]);

  quicksort(a, 0, N - 1);

  for (int i = 0; i < N; i++)
    printf("%d ", a[i]);
  printf("\n");
}

void quicksort(int a[], int low, int high)
{
  int middle;

  if (high <= low) return;
  middle = split(a, low, high);
  quicksort(a, low, middle - 1);
  quicksort(a, middle + 1, high);
}

int split(int a[], int low, int high)
{
  int base_value;

  base_value = a[low];
  for (;;) {
    // 移動 high
    while (low < high && a[high] >= base_value)
    // 修正點1：如果等於的話應該就要執行 break 才對
      high--;
    if (low >= high) break;
    // 修正點2：low 有可能跟 high 剛好交叉
    a[low++] = a[high];

    // 移動 low
    while (low < high && a[low] <= base_value)
    // 修正點3：如果等於的話應該要執行 break 才對
      low++;
    if (low >= high) break;
    // 修正點4：low 有可能與 high 剛好交叉
    a[high--] = a[low];
  }

    a[low] = base_value;
    // 修正點5：將最後的洞填滿
    return low;
}
