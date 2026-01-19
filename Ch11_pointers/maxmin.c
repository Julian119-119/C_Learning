// Finds the largest and smallest elements in an array

#include <stdio.h>

#define N 10

// prtotype
void max_min(int a[], int n, int *max, int *min);

int main(void) {
  int b[N], big, small;

  printf("Enter 10 nubers: ");
  for (int i = 0; i < N; i++) {
    scanf("%d", &b[i]);
  }

  max_min(b, N, &big, &small);

  printf("Largest: %d\n", big);
  printf("Smallest: %d\n", small);

  return 0;
}

void max_min(int a[], int n, int *max, int *min) {
  *max = a[0];
  *min = a[0];

  for (int i = 1; i < n; i++) {
    if (a[i] > *max) {
      *max = a[i];
    }
    if (a[i] < *min) {
      *min = a[i];
    }
  }
}

