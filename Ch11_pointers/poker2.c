// Classifies a poker hand

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NO_SUIT 4
#define NO_RANK 13
#define NO_CARD 5

// prototype
void read_cards(int no_in_rank[], int no_in_suit[]);
void analyze_hand(int no_in_rank[], int no_in_suit[],
                  bool* straight, bool* flush, bool* four_of_a_kind,
                  bool* three_of_a_kind, int* pairs);
void print_result(bool* straight, bool* flush, bool* four_of_a_kind,
                  bool* three_of_a_kind, int* pairs);

// main: Calls rea_card, analyze_hand, and print_result
//       repeatedly
int main(void) {
  for (;;) {
    int no_in_rank[NO_RANK] = {0};
    int no_in_suit[NO_SUIT] = {0};
    bool straight, flush, four_of_a_kind, three_of_a_kind;
    int pairs;  // it can be 0, 1, or, 2

    read_cards(no_in_rank, no_in_suit);
    analyze_hand(no_in_rank, no_in_suit, &straight, 
                 &flush, &four_of_a_kind, &three_of_a_kind, 
                 &pairs);
    print_result(&straight, &flush, &four_of_a_kind, 
                 &three_of_a_kind,  &pairs);
  }
}

// read_cards: Reads the cardss into external variables;
//             checks for bad cards and duplicate cards.
void read_cards(int no_in_rank[], int no_in_suit[]) {
  int card_exists[NO_RANK][NO_SUIT] = {false};
  int rank, suit;
  char rank_ch, suit_ch;

  // 修正點：歸零全域變數
  for (int i = 0; i < NO_RANK; i++) {
    no_in_rank[i] = 0;
  }
  for (int i = 0; i < NO_SUIT; i++) {
    no_in_suit[i] = 0;
  }

  int i = 0;
  while (i < NO_CARD) {
    printf("Enter a card: ");

    // 接下來用 switch 將輸入的文字轉換成對應的數字
    // 讀取並轉換 rank
    scanf(" %c", &rank_ch);
    switch (rank_ch) {
      case '0':
        exit(EXIT_SUCCESS);
      case 'a':
      case 'A':
        rank = 0;
        break;
      case '2':
        rank = 1;
        break;
      case '3':
        rank = 2;
        break;
      case '4':
        rank = 3;
        break;
      case '5':
        rank = 4;
        break;
      case '6':
        rank = 5;
        break;
      case '7':
        rank = 6;
        break;
      case '8':
        rank = 7;
        break;
      case '9':
        rank = 8;
        break;
      case 't':
      case 'T':
        rank = 9;
        break;
      case 'j':
      case 'J':
        rank = 10;
        break;
      case 'q':
      case 'Q':
        rank = 11;
        break;
      case 'k':
      case 'K':
        rank = 12;
        break;
      default:
        while (getchar() != '\n');
        printf("Please enter a correct rank\n");
        printf("Ranks: a 2 3 4 5 6 7 8 9 10 j q k\n");
        continue;
    }

    // 讀取並轉換 suit
    scanf(" %c", &suit_ch);
    while (getchar() != '\n');
    switch (suit_ch) {
      case 'c':
      case 'C':
        suit = 0;
        break;
      case 'd':
      case 'D':
        suit = 1;
        break;
      case 'h':
      case 'H':
        suit = 2;
        break;
      case 's':
      case 'S':
        suit = 3;
        break;
      default:
        printf("Please enter a correct suit\n");
        printf("Suits: c d h s\n");
        continue;
    }

    // 檢查是否是已有的牌
    if (card_exists[rank][suit]) {
      printf("Duplicate card; ignored.\n");
      continue;
    } else {
      i++;
      card_exists[rank][suit] = true;
    }
  }

  // 檢查手上的牌，
  // 並計算 rank 中每個數字出現的數字
  // 與 suit 中每個花色出現的次數
  for (int rank = 0; rank < NO_RANK; rank++)
    for (int suit = 0; suit < NO_SUIT; suit++)
      if (card_exists[rank][suit]) {
        no_in_rank[rank]++;
        no_in_suit[suit]++;
      }
}

// analyze_hand: Determines whether the hand contains a
//               straight, a flush, four-of-a-kind,
//               and/or three-of-a-kind; determines the
//               number of pairs; stores the results into
//               external variables
void analyze_hand(int no_in_rank[], int no_in_suit[],
                  bool* straight, bool* flush, bool* four_of_a_kind,
                  bool* three_of_a_kind, int* pairs) {
  *four_of_a_kind = false;
  *flush = false;
  *straight = false;
  *three_of_a_kind = false;
  *pairs = 0;

  // 檢查花色
  for (int i = 0; i < NO_SUIT; i++) {
    // flush
    if (no_in_suit[i] == 5) {
      *flush = true;
      break;
    }
  }

 

  // 檢查點數
  for (int i = 0; i < NO_RANK; i++) {
     int consec_num = 0;
    // 檢查 four_of_a_kind
    if (no_in_rank[i] == 4) {
      *four_of_a_kind = true;
      break;
    }

    // 檢查 three_of_a_kind
    if (no_in_rank[i] == 3) {
      *three_of_a_kind = true;
    }

    // 檢查 pair
    if (no_in_rank[i] == 2) {
      (*pairs)++;
    }

    // 檢查 straight
    for (int y = 0; i + y < NO_RANK && y < 5; y++) {
      if (no_in_rank[i + y] == 1)
        consec_num++;
      else {
        consec_num = 0;
        break;
      }
    }
    if (consec_num == 5) {
      *straight = true;
      break;
    }
  }
}

void print_result(bool* straight, bool* flush, bool* four_of_a_kind,
                  bool* three_of_a_kind, int* pairs) {
  if (*straight && *flush)
    printf("straight flush\n");
  else if (*four_of_a_kind)
    printf("four of a kind\n");
  else if (*three_of_a_kind && *pairs)
    printf("full house\n");
  else if (*flush)
    printf("flush\n");
  else if (*straight)
    printf("straight\n");
  else if (*three_of_a_kind)
    printf("three of a kind\n");
  else if (*pairs == 2)
    printf("two pair\n");
  else if (*pairs)
    printf("pair\n");
  else
    printf("High card\n");
  printf("\n");
}
