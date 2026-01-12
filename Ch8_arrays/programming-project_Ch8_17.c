// This is my program for programming project 17 in C Programming: a modern approach
// This program is used to create a magic sauare

#include <stdio.h>

int main(void)
{
    int n;

    printf("This program creates a magic square of a specified size\n");
    printf("The size must be an odd number between 1 and 99\n");
    for (;;) {
      printf("Enter size of magic square: ");
      scanf("%d", &n);
      if (!(n % 2)) {
        printf("\nPlease enter an odd number\n");
        continue;
      }
      else if (n < 1 || n > 99) {
        printf("\nPlease enter a number between 1 and 99\n");
        continue;
      }
      else
        break;
    }

    int magic_square[n][n];
    int row = 0, col = n / 2;

    for (int x = 0; x < n; x++)
      for (int y = 0; y < n; y++)
        magic_square[x][y] = 0;

    magic_square[row][col] = 1;                 // 將 1 放置在 row 0 的中間
    for (int num = 2; num <= n * n; num++) {    // num 為 magic square 內的數字
      int next_row = row - 1;
      int next_col = col + 1;
      if (next_row < 0)
        next_row += n;
      if (next_col >= n)
        next_col -= n;
      if (magic_square[next_row][next_col]) {
        next_row = row + 1;
        next_col = col;
      }
      row = next_row;
      col = next_col;
      magic_square[row][col] = num;
    }

    for(int x = 0; x < n; x++) {
      printf("\n");
      for (int y = 0; y < n; y++)
        printf("%5d", magic_square[x][y]);
    }
    printf("\n");

    return 0;
}
