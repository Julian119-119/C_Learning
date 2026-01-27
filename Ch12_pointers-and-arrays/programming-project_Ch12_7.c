// Finds the largest and smallest elements in an array

#include <stdio.h>

#define N 10

// prototype
void max_min(int a[], int n, int *max, int *min);

int main(void) {
  int b[N], big, small;

  printf("Enter 10 nubers: ");
  for (int *p = b; p < b + N; p++) {
    scanf("%d", p);
  }

  max_min(b, N, &big, &small);

  printf("Largest: %d\n", big);
  printf("Smallest: %d\n", small);

  return 0;
}

void max_min(int a[], int n, int *max, int *min) {
  *max = *a;
  *min = *a;

  for (int *p = a + 1; p < a + n; p++) {
    if (*p > *max) {
      *max = *p;
    }
    if (*p < *min) {
      *min = *p;
    }
  }
}

