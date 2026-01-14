// This is my program for programming project 8 in C Programming: a modern approach
// This program is used to simulates the game of craps

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int roll_dice(void);
bool play_game(void);

int main(void)
{
  int no_win = 0, no_lose = 0;
  char answer;

  srand((unsigned)time(NULL));
  // 修正：整個程式中只需要重新洗牌亂數表一次
  // 如果一直洗牌就會因為頁數都相同導致數字一樣
  // (因為程式執行很快，導致時間相同，頁數也相同)

  do
  {
    if (play_game())
    {
      printf("You win!!!\n");
      no_win++;
    }
    else
    {
      printf("You lose!!!\n");
      no_lose++;
    }

    printf("\nPlay again? ");
    answer = getchar();
    while (getchar() != '\n')
      ;
    // 一直吃掉剩下的數字直到換行符出現
    printf("\n");
    if (toupper(answer) == 'N')
      break;
  } while (1);

  printf("Wins: %d", no_win);
  printf("  ");
  printf("Losses: %d\n", no_lose);

  return 0;
}

bool play_game(void)
{
  int point, num;

  num = roll_dice();
  printf("You rolled: %d\n", num);
  if (num == 7 || num == 11)
    return true;
  else if (num == 2 || num == 3 || num == 12)
    return false;
  else
  {
    point = num;
    printf("Your point is %d\n", point);
    for (;;)
    {
      num = roll_dice();
      printf("You rolled %d\n", num);
      if (num == point)
        return true;
      if (num == 7)
        return false;
    }
  }
}

int roll_dice(void)
{
  int sum = 0;

  for (int i = 0; i < 2; i++)
  {
    sum += ((rand() % 6) + 1);
  }

  return sum;
}
