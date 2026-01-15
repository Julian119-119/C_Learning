// Asks user to guess a hidden number

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_NUM 100
#define MIN_NUM 1

// external variable
int secret_num;

// prototype
void choose_secret_num(void);
void play_a_game(void);

int main(void)
{
    char command;

    printf("Guess the secret number between %d and %d.\n\n", MIN_NUM, MAX_NUM);
    srand((unsigned)time(NULL));
    do {
      choose_secret_num();
      play_a_game();
      for (;;) {
        printf("\nPlay again? (Y/N)");
        scanf(" %c", &command);
        if (toupper(command) != 'Y' && toupper(command) != 'N') {
          printf("'Y' or 'N' !!!\n");
          continue;
        }
        break;
      }
    } while (toupper(command) != 'N');
    

    return 0;
}

void choose_secret_num(void)
{
    secret_num = (rand() % 100) + 1;
}

void play_a_game(void)
{
    int num, no_guess = 0;

    for (;;)
    {
        printf("Enter guess: ");
        scanf("%d", &num);
        if (num > MAX_NUM || num < MIN_NUM)
        {
            printf("Please guess a number between 1 and 100\n");
            continue;
        }
        if (num > secret_num)
        {
            printf("Too high; try again\n");
            no_guess++;
            continue;
        }
        if (num < secret_num)
        {
            printf("Too low; try again\n");
            no_guess++;
            continue;
        }
        no_guess++;
        break;
    }

    printf("You won in %d guesses!\n", no_guess);
}