# C program: a modern approach Ch.10 note

## Program overview


| 題號      | 功能                 | 觀念                                       | 連結                       |
| ------- | ------------------ | ---------------------------------------- | ------------------------ |
| example | stack 結構的模板        | 學習 stack 的觀念，並利用全域變數在 C 重現。              | [view](./simulate_stack) |
| 範例一     | 玩猜數字遊戲             | 實際運用全域變數                                 | [view](./guess.c)        |
| 範例二     | 輸入五張撲克牌的花色與點數後判斷牌型 | 綜和目前所學的，並且利用複雜的程式學習 program organization | [view](./poker.c)        |
<br><br>

---
# Note

## I. Local Variables (區域變數)

#### 一，Local Variables


- local variable: 當變數在 function 的 body 中被宣告的時候，這個變數就是這個 functio 的 local variable
- local variabel 的特性
	1. automatic storage duration:
		1. storage duration (儲存期): 變數可以保留他的值的時間
		2. automatic sotrage duration: 當他的 function 開始執行得時候，這個變數就會開始運作，並能夠保有他的值，但當他的 function 結束的時候，這個變數的值就會自動消失，不能夠被其他的 function 引用。
	2. Block scope (區域作用域)
		1. scope (作用域): 變數實際存在的時間 (基本上就是宣告後才開始存在)
		2. block scope: 只有在宣告的 function 內可見，只要離開這個 function 就不能夠再存取它
		3. \**補：因為在 C99 內可以在 function 的中間宣告，所以可能有較小的 scope

#### 二，Static Local Variable

- 特性：
	1. storage duration: 永久。也就是說在往後，**他的值會被永久保留下來**
	2. block scope: 這代表了其他的 function 一樣不能讀取它。**但同一個 function 重復被執行時，他的數值會被保留，不會重製**
- form: 在變數的前面加上 `static`<br>E.g:
	```c
	void f(void)
	{
	  static int i; 
	  // static local variable
	  ...
	}
	```

#### 三，Parameters

- 與 local variable 一樣，屬於 automatic storage duration 與 block scope
<br>

## II. External Variables (global variable，全域變數)

#### 一，Intro

- external variable: 被宣告在 function 之外的變數
- 與 argument 一樣，都是可以用來傳遞資訊給其他的 function 的
- 特性：
	1. static storage duration: 數值永遠存在
	2. file scope: 從宣告當下一路到程式的結尾都可以被讀取到。也就是說其他的 function 也可以讀取到

#### 二，Example: Using External Variables to Implement a Stack

- **stack**：一種資料結構 (data structure)
- 特性
	1. 與陣列一樣，都是可以用來儲存相同型別的數字，但可操作性相對於陣列限縮了一點
	2. 可以 **push** 一個物件到 stack 中 (將其塞進 stack 的頭)
	3. 可以從 stack 中 **pop** (拿取) 一個物件 (移除物件)
	4. 但**不可測試或修改除了頂端的物件**
- program outline:
	- 接下來會用陣列來當作 stack (叫做 contents)
	- 用 `top` 來當作 stack top 的位置
	- 為了要 push 物件進去 stack ，會先存進去 top 的位置，再遞增 top
	- 要 pop 的時候就只能從 top 的位置曲取出
- 因為 contents 與 top 必須在全部的 function 都可以用，所以就要將它宣告成 external variables

- program:
	```c
	#include <stdbool.h>
	#define STACK_SIZE 100
	
	// external variables
	
	int contents[STACK_SIZE];
	int top = 0;
	
	void make_empty(void)
	{
	top = 0;
	} 
	
	bool is_empty(void)
	{
	return top == 0;
	} 
	
	bool is_ful(void)
	{
	return top == STACK_SIZE;
	}
	
	void push(int i)
	{
	if (is_full())
	  stack_overflow();
	else
	  contents[top++] = i;
	}
	
	int pop(void)
	{
	if (is_empty())
	  stack_underflow();
	else
	  return contents[--top]
	}
	```
<br>

#### 三， Pros and Cons of External Variables

- 在很多的情況下用參數來去傳遞數值會比全域變數來好
- 以下是 external variable 的缺點
	1. 在維護的時候需要花很多時間去看它是怎麼在全部的 function 之中運作的
	2. 如果全域變數的型別是錯的，會很難抓出來
	3. 依賴全域變數的 function 是很難被其他程式所運用的
- 所以如果要用的時候，一定要將其設定為**有意義的名稱**，如果發現它只是暫存，就用 local variable 就行了 
<br>

#### 四，範例一：Guessing a Number

- [[C_Programming-A_Modern_Approach_ocr_Ch10.pdf#page=6|題目]]
- 用途：隨機產生 1 到 100 的數字，並讓使用者去猜說他的數值為何
- 如果太低就說 「Too low; try again.」，太高就說「Too high; try again」
- 這一次的 program 由於是我自己嘗試寫的，所以一樣是採用分段的寫法與測試
- 第幾版就是這個意思

###### 1. 初版：隨機選擇一個祕密數字

>[!success]- program
>```c
>// Asks user to guess a hidden number
>
>#include <stdio.h>
>#include <stdlib.h>
>#include <time.h> 
>
>// external variable
>int secret_num;
>
>// prototype
>void choose_secret_num(void);
>
>int main(void)
>{
>srand((unsigned) time(NULL));
>choose_secret_num();  
>
>printf("%d\n", secret_num);
>
>return 0;
>}
>
>void choose_secret_num(void)
>{
>secret_num = (rand() % 100) + 1;
>}
>```

>[!success]- output
>$ ./guess 
>24

###### 2. 第二版：執行一次的猜數字遊戲

>[!success]- program
>```c
>// Asks user to guess a hidden number
>
>#include <stdio.h>
>#include <stdlib.h>
>#include <time.h>
>
>#define MAX_NUM 100
>#define MIN_NUM 1
>
>// external variable
>int secret_num;
>
>// prototype
>void choose_secret_num(void);
>void choose_new_num(void);
>
>int main(void)
>{
>    srand((unsigned) time(NULL));
>    choose_secret_num();
>    choose_new_num();
>
>    return 0;
>}
>
>void choose_secret_num(void)
>{    
>   secret_num = (rand() % 100) + 1;
>}
>
>void choose_new_num(void)
>{
>    int num, no_guess = 0;
>    
>    for (;;) {
>      printf("Enter guess: ");
>      scanf("%d", &num);
>      if (num > MAX_NUM || num < MIN_NUM) {
>        printf("Please guess a number between 1 and 100\n");
>        continue;
>      }
>      if (num > secret_num) {
>        printf("Too high; try again\n");
>        no_guess++;
>        continue;
>      }
>      if (num < secret_num) {
>        printf("Too low; try again\n");
>        no_guess++;
>        continue;
>      }
>      no_guess++;
>      break;
>    }
>
 >   printf("You won in %d guesses!\n", no_guess);
>}
>```

>[!success]- output
>```
>Enter guess: 50
>Too low; try again
>Enter guess: 75
>Too low; try again
>Enter guess: 90
>Too low; try again
>Enter guess: 99
>Too high; try again
>Enter guess: 95
>Too low; try again
>Enter guess: 98
>Too high; try again
>Enter guess: 96
>You won in 7 guesses!
>```


###### 3. 最終版：執行多次的猜數字遊戲

>[!success]- program
>```c
>// Asks user to guess a hidden number
>
>#include <stdio.h>
>#include <stdlib.h>
>#include <time.h>
>#include <ctype.h>
>
>#define MAX_NUM 100
>#define MIN_NUM 1
>
>// external variable
>int secret_num;
>
>// prototype
>void choose_secret_num(void);
>void play_a_game(void);
>
>int main(void)
>{
>    char command;
>
>    printf("Guess the secret number between %d and %d.\n\n",
>       MIN_NUM, MAX_NUM);
>    srand((unsigned)time(NULL));
>    do {
>      choose_secret_num();
>      play_a_game();
>      for (;;) {
>        printf("\nPlay again? (Y/N)");
>        scanf(" %c", &command);
>        if (toupper(command) != 'Y' && toupper(command) != 'N') {
>          printf("'Y' or 'N' !!!\n");
>          continue;
>        }
>        break;
>      }
>    } while (toupper(command) != 'N');
>    
>
>    return 0;
>}
>
>void choose_secret_num(void)
>{
>    secret_num = (rand() % 100) + 1;
>}
>
>void play_a_game(void)
>{
>    int num, no_guess = 0;
>
>    for (;;)
>    {
>        printf("Enter guess: ");
>        scanf("%d", &num);
>        if (num > MAX_NUM || num < MIN_NUM)
>        {
>            printf("Please guess a number between 1 and 100\n");
>            continue;
>        }
>        if (num > secret_num)
>        {
>            printf("Too high; try again\n");
>            no_guess++;
>            continue;
>        }
>        if (num < secret_num)
>        {
>            printf("Too low; try again\n");
>            no_guess++;
>            continue;
>        }
>        no_guess++;
>        break;
>    }
>
>    printf("You won in %d guesses!\n", no_guess);
>}
>```

>[!success]- output
>```
>Guess the secret number between 1 and 100.
>
>Enter guess: 50
>Too high; try again
>Enter guess: 25
>Too low; try again
>Enter guess: 35
>Too low; try again
>Enter guess: 40
>Too high; try again
>Enter guess: 38
>You won in 5 guesses!
>
>Play again? (Y/N)c
>'Y' or 'N' !!!
>
>Play again? (Y/N)y
>Enter guess: 50
>Too high; try again
>Enter guess: 25
>Too high; try again
>Enter guess: 13
>Too low; try again
>Enter guess: 20
>Too high; try again
>Enter guess: 15
>Too low; try again
>Enter guess: 18
>Too high; try again
>Enter guess: 17
>Too high; try again
>Enter guess: 16
>You won in 8 guesses!
>
>Play again? (Y/N)N
>```

<br><br>

## II. Blocks

- block: 也就是在 compound statement 中的 `{}` 
- form:
	```c
	{ declarations statements }
	```
- E.g: 一個 block
	```c
	if (i > j) {
	  // swap values of i and j
	  int temp = i;
	  i = j;
	  j = temp;
	}
	```
- 被宣告在 block 變數的特性
	1. automatic storage duration: 數值只會在這個 block 之中被保存
	2. block scope: 只能夠在這個 block 中使用
<br>

## III. Scope

- scope 的規則
	1. 當一個變數在一個 block 被宣告的時候，同名的變數會被隱藏起來，無法使用，當脫離這個 block 後它才可以再度被使用<br>E.g:
		```c
		int i;
		// Declaration 1
		
		void f(int i)
		// Declaration 2
		{
		  i = 1;
		}
		
		void g(void)
		{
		  int i = 2;
		  // Declaration 3
		  
		  if (i > 0) {
		    int i;
		    // Declaration 4
		    i = 3;
		  }
		  
		  i = 4;
		}
		
		void h(void)
		{
		  i = 5
		}
		```
		- Declaration 1: i 為 external variable
		- Declaration 2: i 為參數
		- Declaration 3: i 為 local variable
		- Declaration 4: i 一樣是 local variable
	- 說明：
		- 在 f 這個 function 中，因為 i 在 function 中被宣告為參數，所以 decalration 2 會先蓋掉 declaration 1 的 i ，導致數值不會互相影響
		- 在 g 這個 function 中，因為 i 在 function 中被宣告為區域變數，所以 decalration 3 會蓋掉 declaration2 
		- 除了 h 以外其他的就同上
		- 在 h 中是 declaration 中的全域變數（因為沒有宣告）
<br>

## IV. Organizing a C Program

#### 一，Classifying a Poker Hand

- 建議的 function 結構
	1. `#include` directives
	2. `#define` directives
	3. Type definitions
	4. Declarations of extrnal variables
	5. Prototypes for functions other than `main`
	6. Definition of `main`
	7. Definitions of other functions
<br>

### 二：範例二：Classifying a Poker Hand

- 這一次一樣是採用分段的寫法

###### 初版: 輸入撲克牌的數字

- 檢查方式：用 `printf` 印出已有的牌
- 學習重點：用 `switch` 將牌的數字與花色轉成數字，並當作陣列的位置

>[!success]- program
>```c
>// Classifies a poker hand
>
>#include <stdbool.h>
>#include <stdio.h>
>#include <stdlib.h>
>
>#define NO_SUIT 4
>#define NO_RANK 13
>#define NO_CARD 5
>
>// prototype
>void read_cards(void);
>void analyze_hand(void);
>void print_result(void);
>
>int main(void) {
>  read_cards();
>
>  return 0;
>}
>
>void read_cards(void) {
>  int card_exists[NO_RANK][NO_SUIT] = {false};
>  int rank, suit;
>  char rank_ch, suit_ch;
>
>  int i = 0;
>  while (i < NO_CARD) {
>    printf("Enter a card: ");
>
 >   // 接下來用 switch 將輸入的文字轉換成對應的數字
 >   // 讀取並轉換 rank
 >   switch (rank_ch) {
>      case '0':
>        exit(EXIT_SUCCESS);
>      case 'a':
>      case 'A':
>        rank = 0;
>        break;
>      case '2':
>        rank = 1;
>        break;
>      case '3':
>        rank = 2;
>        break;
>      case '4':
>        rank = 3;
>        break;
>      case '5':
>        rank = 4;
>        break;
>      case '6':
>        rank = 5;
>        break;
>      case '7':
>        rank = 6;
>        break;
>      case '8':
>        rank = 7;
>        break;
>      case '9':
>        rank = 8;
>        break;
>      case 't':
>      case 'T':
>        rank = 9;
>        break;
>      case 'j':
>      case 'J':
>        rank = 10;
>        break;
>      case 'q':
>      case 'Q':
>        rank = 11;
>        break;
>      case 'k':
>      case 'K':
>        rank = 12;
>        break;
>      default:
>        while (getchar() != '\n')
>        // 先清空 buffer
>        printf("Please enter a correct rank\n");
>        printf("Ranks: a 2 3 4 5 6 7 8 9 10 j q k\n");
>        continue;
>    }
>    // 讀取並轉換 suit
>    scanf(" %c", &suit_ch);
>    switch (suit_ch) {
>      case 'c':
>      case 'C':
>        suit = 0;
>        break;
>      case 'd':
>      case 'D':
>        suit = 1;
>        break;
>      case 'h':
>      case 'H':
>        suit = 2;
>        break;
>      case 's':
>      case 'S':
>        suit = 3;
>        break;
>      default:
>        printf("Please enter a correct suit\n");
>        printf("Suits: c d h s\n");
>        continue;
>    }
>
>    // 檢查是否是已有的牌
>    if (card_exists[rank][suit]) {
>      printf("Duplicate card; ignored.\n");
>      continue;
>    } else {
>      i++;
>      card_exists[rank][suit] = true;
>    }
>  }
>
>  // 測試用：列印出已有的牌
>  for (int row = 0; row < NO_RANK; row++)
>    for (int col = 0; col < NO_SUIT; col++)
>      if (card_exists[row][col]) {
>        printf("[%d, %d]\n", row, col);
>      }
>}
>```

>[!success]- output
>```
>Enter a card: as
>Enter a card: 2s
>Enter a card: 2s
>Duplicate card; ignored.
>Enter a card: 1s
>Please enter a correct rank
>Ranks: a 2 3 4 5 6 7 8 9 10 j q k
>Enter a card: 3s
>Enter a card: 4s
>Enter a card: 5s
>[0, 3]
>[1, 3]
>[2, 3]
>[3, 3]
>[4, 3]
>
>```

###### 第二版：將牌的花色與數字分開並計數

- 概念：因為要判斷牌型是透過各個花色有幾個，相同的點數又有幾個
- 所以必須宣告兩個陣列 `no_in_rank` 與 `no_in_suit` 來計數
- 且這兩個會在各個 function 中被使用，所以必須要用全域變數

>[!success]- program
>```c
>// Classifies a poker hand
>
>#include <stdbool.h>
>#include <stdio.h>
>#include <stdlib.h>
>
>#define NO_SUIT 4
>#define NO_RANK 13
>#define NO_CARD 5
>
>// external variable
>int no_in_rank[NO_RANK] = {0};
>int no_in_suit[NO_SUIT] = {0};
>
>// prototype
>void read_cards(void);
>void analyze_hand(void);
>void print_result(void);
>
>// main: Calls rea_card, analyze_hand, and print_result
>//       repeatedly
>int main(void) {
>  read_cards();
>  analyze_hand();
>
>  return 0;
>}
>
>// read_cards: Reads the cardss into external variables;
>//             checks for bad cards and duplicate cards.
>void read_cards(void) {
>  int card_exists[NO_RANK][NO_SUIT] = {false};
>  int rank, suit;
>  char rank_ch, suit_ch;
>
>  int i = 0;
>  while (i < NO_CARD) {
>    printf("Enter a card: ");
>
>    // 接下來用 switch 將輸入的文字轉換成對應的數字
>    // 讀取並轉換 rank
>    scanf(" %c", &rank_ch);
>    switch (rank_ch) {
>      case '0':
>        exit(EXIT_SUCCESS);
>      case 'a':
>      case 'A':
>        rank = 0;
>        break;
>      case '2':
>        rank = 1;
>        break;
>      case '3':
>        rank = 2;
>        break;
>      case '4':
>        rank = 3;
>        break;
>      case '5':
>        rank = 4;
>        break;
>      case '6':
>        rank = 5;
>        break;
>      case '7':
>        rank = 6;
>        break;
>      case '8':
>        rank = 7;
>        break;
>      case '9':
>        rank = 8;
>        break;
>      case 't':
>      case 'T':
>        rank = 9;
>        break;
>      case 'j':
>      case 'J':
>        rank = 10;
>        break;
>      case 'q':
>      case 'Q':
>        rank = 11;
>        break;
>      case 'k':
>      case 'K':
>        rank = 12;
>        break;
>      default:
>        while (getchar() != '\n'); 
>        printf("Please enter a correct rank\n");
>        printf("Ranks: a 2 3 4 5 6 7 8 9 10 j q k\n");
>        continue;
>    }
>    // 讀取並轉換 suit
>    scanf(" %c", &suit_ch);
>    while(getchar() != '\n');
>    switch (suit_ch) {
>      case 'c':
>      case 'C':
>        suit = 0;
>        break;
>      case 'd':
>      case 'D':
>        suit = 1;
>        break;
>      case 'h':
>      case 'H':
>        suit = 2;
>        break;
>      case 's':
>      case 'S':
>        suit = 3;
>        break;
>      default:
>        printf("Please enter a correct suit\n");
>        printf("Suits: c d h s\n");
>        continue;
>    }
>
>    // 檢查是否是已有的牌
>    if (card_exists[rank][suit]) {
>      printf("Duplicate card; ignored.\n");
>      continue;
>    } else {
>      i++;
>      card_exists[rank][suit] = true;
>    }
>  }
>
>  // 檢查手上的牌，
>  // 並計算 rank 中每個數字出現的數字
>  // 與 suit 中每個花色出現的次數
>  for (int rank = 0; rank < NO_RANK; rank++)
>    for (int suit = 0; suit < NO_SUIT; suit++)
>      if (card_exists[rank][suit]) {
>        no_in_rank[rank]++;
>        no_in_suit[suit]++;
>      }
>}
>
>// analyze_hand: Determines whether the hand contains a 
>//               straight, a flush, four-of-a-kind,
>//               and/or three-of-a-kind; determines the 
>//               number of pairs; stores the results into
>//               external variables
>void analyze_hand(void) {
>  // 測試用：印出 rank 與 suit 中非零的數字
>  for (int i = 0; i < NO_RANK; i++) {
>    if (no_in_rank[i])
>      printf("[%d, %d] ", i, no_in_rank[i]);
>  }
>  printf("\n\n");
>  for(int i = 0; i < NO_SUIT; i++) {
>    if (no_in_suit[i])
>      printf("[%d, %d] ", i, no_in_suit[i]);
>  }
>  printf("\n");
>}
>```

>[!success]- output
>```
>Enter a card: as
>Enter a card: 2s
>Enter a card: 3s
>Enter a card: 4s
>Enter a card: 5s
>[0, 1] [1, 1] [2, 1] [3, 1] [4, 1] 
>
>[3, 5] 
>// [轉換過後的數字， 次數]
>```

###### 第三版：測試 four of a kind, flush, straight, three of a kind, pair

- 這一版新增了判斷各個牌型的基本條件（例如 straight flush 就是 straight + flush; full house 就是 three of a kind + pair）

>[!success]- program
>```c
>// Classifies a poker hand
>
>#include <stdbool.h>
>#include <stdio.h>
>#include <stdlib.h>
>
>#define NO_SUIT 4
>#define NO_RANK 13
>#define NO_CARD 5
>
>// external variable
>int no_in_rank[NO_RANK] = {0};
>int no_in_suit[NO_SUIT] = {0};
>bool straight, flush,four_of_a_kind, three_of_a_kind;
>int pairs;  // it can be 0, 1, or, 2
>
>// prototype
>void read_cards(void);
>void analyze_hand(void);
>void print_result(void);
>
>// main: Calls rea_card, analyze_hand, and print_result
>//       repeatedly
>int main(void) {
>  read_cards();
>  analyze_hand();
>  print_result();
>
>  return 0;
>}
>
>// read_cards: Reads the cardss into external variables;
>//             checks for bad cards and duplicate cards.
>void read_cards(void) {
>  int card_exists[NO_RANK][NO_SUIT] = {false};
>  int rank, suit;
>  char rank_ch, suit_ch;
>
>  int i = 0;
>  while (i < NO_CARD) {
>    printf("Enter a card: ");
>
>    // 接下來用 switch 將輸入的文字轉換成對應的數字
>    // 讀取並轉換 rank
>    scanf(" %c", &rank_ch);
>    switch (rank_ch) {
>      case '0':
>        exit(EXIT_SUCCESS);
>      case 'a':
>      case 'A':
>        rank = 0;
>        break;
>      case '2':
>        rank = 1;
>        break;
>      case '3':
>        rank = 2;
>        break;
>      case '4':
>        rank = 3;
>        break;
>      case '5':
>        rank = 4;
>        break;
>      case '6':
>        rank = 5;
>        break;
>      case '7':
>        rank = 6;
>        break;
>      case '8':
>        rank = 7;
>        break;
>      case '9':
>        rank = 8;
>        break;
>      case 't':
>      case 'T':
>        rank = 9;
>        break;
>      case 'j':
>      case 'J':
>        rank = 10;
>        break;
>      case 'q':
>      case 'Q':
>        rank = 11;
>        break;
>      case 'k':
>      case 'K':
>        rank = 12;
>        break;
>      default:
>        while (getchar() != '\n');
>        printf("Please enter a correct rank\n");
>        printf("Ranks: a 2 3 4 5 6 7 8 9 10 j q k\n");
>        continue;
>    }
>    // 讀取並轉換 suit
>    scanf(" %c", &suit_ch);
>    while(getchar() != '\n');
>    switch (suit_ch) {
>      case 'c':
>      case 'C':
>        suit = 0;
>        break;
>      case 'd':
>      case 'D':
>        suit = 1;
>        break;
>      case 'h':
>      case 'H':
>        suit = 2;
>        break;
>      case 's':
>      case 'S':
>        suit = 3;
>        break;
>      default:
>        printf("Please enter a correct suit\n");
>        printf("Suits: c d h s\n");
>        continue;
>    }
>
>    // 檢查是否是已有的牌
>    if (card_exists[rank][suit]) {
>      printf("Duplicate card; ignored.\n");
>      continue;
>    } else {
>      i++;
>      card_exists[rank][suit] = true;
>    }
>  }
>
>  // 檢查手上的牌，
>  // 並計算 rank 中每個數字出現的數字
>  // 與 suit 中每個花色出現的次數
>  for (int rank = 0; rank < NO_RANK; rank++)
>    for (int suit = 0; suit < NO_SUIT; suit++)
>      if (card_exists[rank][suit]) {
>        no_in_rank[rank]++;
>        no_in_suit[suit]++;
>      }
>}
>
>// analyze_hand: Determines whether the hand contains a 
>//               straight, a flush, four-of-a-kind,
>//               and/or three-of-a-kind; determines the 
>//               number of pairs; stores the results into
>//               external variables
>void analyze_hand(void) {
>  four_of_a_kind = false;
>  flush = false;
>  straight = false;
>  three_of_a_kind = false;
>  pairs = 0;
>
>  // 檢查花色
>  for (int i = 0; i < NO_SUIT; i++) {
>    // flush
>    if (no_in_suit[i] == 5) {
>      flush = true;
>      break;
>    }
>  }
>
>  int consec_num = 0;
>
>  // 檢查點數
>  for (int i = 0; i < NO_RANK; i++) {
>    // 檢查 four_of_a_kind
>    if (no_in_rank[i] == 4) {
>        four_of_a_kind = true;
>        break;
>    }
> 
>    // 檢查 three_of_a_kind
>    if (no_in_rank[i] == 3)
>      three_of_a_kind = true;
>
>    // 檢查 pair
>    if (no_in_rank[i] == 2)
>      pairs++;
>
>    // 檢查 straight
>    for(int y = 0; i + y < NO_RANK && y < 5; y++) {
>      if (no_in_rank[i+y] == 1) 
>         consec_num++;
>      else {
>         consec_num = 1;
>         break;
>      }
>    }
>    if (consec_num == 5) {
>      straight = true;
>      break;
>    }
>  }
>}
>
>void print_result(void) {
>  // 測試用
>  // 檢查各個變數的值是否正確
>  printf("four of a kind = %d\n", four_of_a_kind);
>  printf("flush = %d\n", flush);
>  printf("straight = %d\n", straight);
>  printf("three of a kind = %d\n", three_of_a_kind);
>  printf("pair = %d\n", pairs);
>}
>```

>[!success]- output
>```
>Enter a card: as
>Enter a card: 2s
>Enter a card: 3s
>Enter a card: 4s
>Enter a card: 5s
>four of a kind = 0
>flush = 1
>straight = 1
>three of a kind = 0
>pair = 0
>```

###### 第四版：判斷牌型

- 利用上一版的結果來判斷牌型

>[!success]- program
>```c
> // Classifies a poker hand
> 
> #include <stdbool.h>
> #include <stdio.h>
> #include <stdlib.h>
> 
> #define NO_SUIT 4
> #define NO_RANK 13
> #define NO_CARD 5
> 
> // external variable
> int no_in_rank[NO_RANK] = {0};
> int no_in_suit[NO_SUIT] = {0};
> bool straight, flush,four_of_a_kind, three_of_a_kind;
> int pairs;  // it can be 0, 1, or, 2
> 
> // prototype
> void read_cards(void);
> void analyze_hand(void);
> void print_result(void);
> 
> // main: Calls rea_card, analyze_hand, and print_result
> //       repeatedly
> int main(void) {
>   read_cards();
>   analyze_hand();
>   print_result();
> 
>   return 0;
> }
> 
> // read_cards: Reads the cardss into external variables;
> //             checks for bad cards and duplicate cards.
> void read_cards(void) {
>   int card_exists[NO_RANK][NO_SUIT] = {false};
>   int rank, suit;
>   char rank_ch, suit_ch;
> 
>   int i = 0;
>   while (i < NO_CARD) {
>     printf("Enter a card: ");
> 
>     // 接下來用 switch 將輸入的文字轉換成對應的數字
>     // 讀取並轉換 rank
>     scanf(" %c", &rank_ch);
>     switch (rank_ch) {
>       case '0':
>         exit(EXIT_SUCCESS);
>       case 'a':
>       case 'A':
>         rank = 0;
>         break;
>       case '2':
>         rank = 1;
>         break;
>       case '3':
>         rank = 2;
>         break;
>       case '4':
>         rank = 3;
>         break;
>       case '5':
>         rank = 4;
>         break;
>       case '6':
>         rank = 5;
>         break;
>       case '7':
>         rank = 6;
>         break;
>       case '8':
>         rank = 7;
>         break;
>       case '9':
>         rank = 8;
>         break;
>       case 't':
>       case 'T':
>         rank = 9;
>         break;
>       case 'j':
>       case 'J':
>         rank = 10;
>         break;
>       case 'q':
>       case 'Q':
>         rank = 11;
>         break;
>       case 'k':
>       case 'K':
>         rank = 12;
>         break;
>       default:
>         while (getchar() != '\n');
>         printf("Please enter a correct rank\n");
>         printf("Ranks: a 2 3 4 5 6 7 8 9 10 j q k\n");
>         continue;
>     }
>     // 讀取並轉換 suit
>     scanf(" %c", &suit_ch);
>     while(getchar() != '\n');
>     switch (suit_ch) {
>       case 'c':
>       case 'C':
>         suit = 0;
>         break;
>       case 'd':
>       case 'D':
>         suit = 1;
>         break;
>       case 'h':
>       case 'H':
>         suit = 2;
>         break;
>       case 's':
>       case 'S':
>         suit = 3;
>         break;
>       default:
>         printf("Please enter a correct suit\n");
>         printf("Suits: c d h s\n");
>         continue;
>     }
> 
>     // 檢查是否是已有的牌
>     if (card_exists[rank][suit]) {
>       printf("Duplicate card; ignored.\n");
>       continue;
>     } else {
>       i++;
>       card_exists[rank][suit] = true;
>     }
>   }
> 
>   // 檢查手上的牌，
>   // 並計算 rank 中每個數字出現的數字
>   // 與 suit 中每個花色出現的次數
>   for (int rank = 0; rank < NO_RANK; rank++)
>     for (int suit = 0; suit < NO_SUIT; suit++)
>       if (card_exists[rank][suit]) {
>         no_in_rank[rank]++;
>         no_in_suit[suit]++;
>       }
> }
> 
> // analyze_hand: Determines whether the hand contains a 
> //               straight, a flush, four-of-a-kind,
> //               and/or three-of-a-kind; determines the 
> //               number of pairs; stores the results into
> //               external variables
> void analyze_hand(void) {
>   four_of_a_kind = false;
>   flush = false;
>   straight = false;
>   three_of_a_kind = false;
>   pairs = 0;
> 
>   // 檢查花色
>   for (int i = 0; i < NO_SUIT; i++) {
>     // flush
>     if (no_in_suit[i] == 5) {
>       flush = true;
>       break;
>     }
>   }
> 
>   int consec_num = 0;
> 
>   // 檢查點數
>   for (int i = 0; i < NO_RANK; i++) {
>     // 檢查 four_of_a_kind
>     if (no_in_rank[i] == 4) {
>         four_of_a_kind = true;
>         break;
>     }
>  
>     // 檢查 three_of_a_kind
>     if (no_in_rank[i] == 3)
>       three_of_a_kind = true;
> 
>     // 檢查 pair
>     if (no_in_rank[i] == 2)
>       pairs++;
> 
>     // 檢查 straight
>     for(int y = 0; i + y < NO_RANK && y < 5; y++) {
>       if (no_in_rank[i+y] == 1) 
>          consec_num++;
>       else {
>          consec_num = 1;
>          break;
>       }
>     }
>     if (consec_num == 5) {
>       straight = true;
>       break;
>     }
>   }
> }
> 
> void print_result(void) {
>   if (straight && flush)
>     printf("straight flush\n");
>   else if (four_of_a_kind)
>     printf("four of a kind\n");
>   else if (three_of_a_kind && pairs)
>     printf("full house\n");
>   else if (flush)
>     printf("flush\n");
>   else if (straight)
>     printf("straight\n");
>   else if (three_of_a_kind)
>     printf("three of a kind\n");
>   else if (pairs == 2)
>     printf("two pair\n");
>   else if (pairs)
>     printf("pair\n");
>   else 
>     printf("High card\n");
> }
>```

>[!success]- output
>```
>Enter a card: as
>Enter a card: 2s
>Enter a card: 3s
>Enter a card: 4s 
>Enter a card: 5s
>straight flush
>```

###### 最終版：輸入多次的牌

- 錯誤點：全域變數在執行第二次的函數時沒有被歸零，導致上一次的結果被留了下來

>[!bug]- 錯誤的 program
>```c
> // Classifies a poker hand
> 
> #include <stdbool.h>
> #include <stdio.h>
> #include <stdlib.h>
> 
> #define NO_SUIT 4
> #define NO_RANK 13
> #define NO_CARD 5
> 
> // external variable
> int no_in_rank[NO_RANK] = {0};
> int no_in_suit[NO_SUIT] = {0};
> bool straight, flush,four_of_a_kind, three_of_a_kind;
> int pairs;  // it can be 0, 1, or, 2
> 
> // prototype
> void read_cards(void);
> void analyze_hand(void);
> void print_result(void);
> 
> // main: Calls rea_card, analyze_hand, and print_result
> //       repeatedly
> int main(void) {
>   for (;;) {
>     read_cards();
>     analyze_hand();
>     print_result();
>   }
> }
> 
> // read_cards: Reads the cardss into external variables;
> //             checks for bad cards and duplicate cards.
> void read_cards(void) {
>   int card_exists[NO_RANK][NO_SUIT] = {false};
>   int rank, suit;
>   char rank_ch, suit_ch;
> 
>   int i = 0;
>   while (i < NO_CARD) {
>     printf("Enter a card: ");
> 
>     // 接下來用 switch 將輸入的文字轉換成對應的數字
>     // 讀取並轉換 rank
>     scanf(" %c", &rank_ch);
>     switch (rank_ch) {
>       case '0':
>         exit(EXIT_SUCCESS);
>       case 'a':
>       case 'A':
>         rank = 0;
>         break;
>       case '2':
>         rank = 1;
>         break;
>       case '3':
>         rank = 2;
>         break;
>       case '4':
>         rank = 3;
>         break;
>       case '5':
>         rank = 4;
>         break;
>       case '6':
>         rank = 5;
>         break;
>       case '7':
>         rank = 6;
>         break;
>       case '8':
>         rank = 7;
>         break;
>       case '9':
>         rank = 8;
>         break;
>       case 't':
>       case 'T':
>         rank = 9;
>         break;
>       case 'j':
>       case 'J':
>         rank = 10;
>         break;
>       case 'q':
>       case 'Q':
>         rank = 11;
>         break;
>       case 'k':
>       case 'K':
>         rank = 12;
>         break;
>       default:
>         while (getchar() != '\n');
>         printf("Please enter a correct rank\n");
>         printf("Ranks: a 2 3 4 5 6 7 8 9 10 j q k\n");
>         continue;
>     }
> 
>     // 讀取並轉換 suit
>     scanf(" %c", &suit_ch);
>     while(getchar() != '\n');
>     switch (suit_ch) {
>       case 'c':
>       case 'C':
>         suit = 0;
>         break;
>       case 'd':
>       case 'D':
>         suit = 1;
>         break;
>       case 'h':
>       case 'H':
>         suit = 2;
>         break;
>       case 's':
>       case 'S':
>         suit = 3;
>         break;
>       default:
>         printf("Please enter a correct suit\n");
>         printf("Suits: c d h s\n");
>         continue;
>     }
> 
>     // 檢查是否是已有的牌
>     if (card_exists[rank][suit]) {
>       printf("Duplicate card; ignored.\n");
>       continue;
>     } else {
>       i++;
>       card_exists[rank][suit] = true;
>     }
>   }
> 
>   // 檢查手上的牌，
>   // 並計算 rank 中每個數字出現的數字
>   // 與 suit 中每個花色出現的次數
>   for (int rank = 0; rank < NO_RANK; rank++)
>     for (int suit = 0; suit < NO_SUIT; suit++)
>       if (card_exists[rank][suit]) {
>         no_in_rank[rank]++;
>         no_in_suit[suit]++;
>       }
> }
> 
> // analyze_hand: Determines whether the hand contains a 
> //               straight, a flush, four-of-a-kind,
> //               and/or three-of-a-kind; determines the 
> //               number of pairs; stores the results into
> //               external variables
> void analyze_hand(void) {
>   four_of_a_kind = false;
>   flush = false;
>   straight = false;
>   three_of_a_kind = false;
>   pairs = 0;
> 
>   // 檢查花色
>   for (int i = 0; i < NO_SUIT; i++) {
>     // flush
>     if (no_in_suit[i] == 5) {
>       flush = true;
>       break;
>     }
>   }
> 
>   int consec_num = 0;
> 
>   // 檢查點數
>   for (int i = 0; i < NO_RANK; i++) {
>     // 檢查 four_of_a_kind
>     if (no_in_rank[i] == 4) {
>         four_of_a_kind = true;
>         break;
>     }
>  
>     // 檢查 three_of_a_kind
>     if (no_in_rank[i] == 3)
>       three_of_a_kind = true;
> 
>     // 檢查 pair
>     if (no_in_rank[i] == 2)
>       pairs++;
> 
>     // 檢查 straight
>     for(int y = 0; i + y < NO_RANK && y < 5; y++) {
>       if (no_in_rank[i+y] == 1) 
>          consec_num++;
>       else {
>          consec_num = 0;
>          break;
>       }
>     }
>     if (consec_num == 5) {
>       straight = true;
>       break;
>     }
>   }
> }
> 
> void print_result(void) {
>   if (straight && flush)
>     printf("straight flush\n");
>   else if (four_of_a_kind)
>     printf("four of a kind\n");
>   else if (three_of_a_kind && pairs)
>     printf("full house\n");
>   else if (flush)
>     printf("flush\n");
>   else if (straight)
>     printf("straight\n");
>   else if (three_of_a_kind)
>     printf("three of a kind\n");
>   else if (pairs == 2)
>     printf("two pair\n");
>   else if (pairs)
>     printf("pair\n");
>   else 
>     printf("High card\n");
>   printf("\n");
> }
>```

>[!failure]- 錯誤的 output
>```
>Enter a card: 2s
>Enter a card: 5s
>Enter a card: 4s
>Enter a card: 3s
>Enter a card: 6s
>straight flush
>
>Enter a card: 2s
>Enter a card: 5s
>Enter a card: 4s
>Enter a card: 3s
>Enter a card: 6s
>pair
>
>Enter a card: 0
>```

>[!success]- 正確的 program
>```c
> // Classifies a poker hand
> 
> #include <stdbool.h>
> #include <stdio.h>
> #include <stdlib.h>
> 
> #define NO_SUIT 4
> #define NO_RANK 13
> #define NO_CARD 5
> 
> // external variable
> int no_in_rank[NO_RANK] = {0};
> int no_in_suit[NO_SUIT] = {0};
> bool straight, flush,four_of_a_kind, three_of_a_kind;
> int pairs;  // it can be 0, 1, or, 2
> 
> // prototype
> void read_cards(void);
> void analyze_hand(void);
> void print_result(void);
> 
> // main: Calls rea_card, analyze_hand, and print_result
> //       repeatedly
> int main(void) {
>   for (;;) {
>     read_cards();
>     analyze_hand();
>     print_result();
>   }
> }
> 
> // read_cards: Reads the cardss into external variables;
> //             checks for bad cards and duplicate cards.
> void read_cards(void) {
>   int card_exists[NO_RANK][NO_SUIT] = {false};
>   int rank, suit;
>   char rank_ch, suit_ch;
> 
>   // 修正點：歸零全域變數
>   for (int i = 0; i < NO_RANK; i++)
>     no_in_rank[i] = 0;
>   for (int i = 0; i < NO_SUIT; i++)
>     no_in_suit[i] = 0;
> 
>   int i = 0;
>   while (i < NO_CARD) {
>     printf("Enter a card: ");
> 
>     // 接下來用 switch 將輸入的文字轉換成對應的數字
>     // 讀取並轉換 rank
>     scanf(" %c", &rank_ch);
>     switch (rank_ch) {
>       case '0':
>         exit(EXIT_SUCCESS);
>       case 'a':
>       case 'A':
>         rank = 0;
>         break;
>       case '2':
>         rank = 1;
>         break;
>       case '3':
>         rank = 2;
>         break;
>       case '4':
>         rank = 3;
>         break;
>       case '5':
>         rank = 4;
>         break;
>       case '6':
>         rank = 5;
>         break;
>       case '7':
>         rank = 6;
>         break;
>       case '8':
>         rank = 7;
>         break;
>       case '9':
>         rank = 8;
>         break;
>       case 't':
>       case 'T':
>         rank = 9;
>         break;
>       case 'j':
>       case 'J':
>         rank = 10;
>         break;
>       case 'q':
>       case 'Q':
>         rank = 11;
>         break;
>       case 'k':
>       case 'K':
>         rank = 12;
>         break;
>       default:
>         while (getchar() != '\n');
>         printf("Please enter a correct rank\n");
>         printf("Ranks: a 2 3 4 5 6 7 8 9 10 j q k\n");
>         continue;
>     }
> 
>     // 讀取並轉換 suit
>     scanf(" %c", &suit_ch);
>     while(getchar() != '\n');
>     switch (suit_ch) {
>       case 'c':
>       case 'C':
>         suit = 0;
>         break;
>       case 'd':
>       case 'D':
>         suit = 1;
>         break;
>       case 'h':
>       case 'H':
>         suit = 2;
>         break;
>       case 's':
>       case 'S':
>         suit = 3;
>         break;
>       default:
>         printf("Please enter a correct suit\n");
>         printf("Suits: c d h s\n");
>         continue;
>     }
> 
>     // 檢查是否是已有的牌
>     if (card_exists[rank][suit]) {
>       printf("Duplicate card; ignored.\n");
>       continue;
>     } else {
>       i++;
>       card_exists[rank][suit] = true;
>     }
>   }
> 
>   // 檢查手上的牌，
>   // 並計算 rank 中每個數字出現的數字
>   // 與 suit 中每個花色出現的次數
>   for (int rank = 0; rank < NO_RANK; rank++)
>     for (int suit = 0; suit < NO_SUIT; suit++)
>       if (card_exists[rank][suit]) {
>         no_in_rank[rank]++;
>         no_in_suit[suit]++;
>       }
> }
> 
> // analyze_hand: Determines whether the hand contains a 
> //               straight, a flush, four-of-a-kind,
> //               and/or three-of-a-kind; determines the 
> //               number of pairs; stores the results into
> //               external variables
> void analyze_hand(void) {
>   four_of_a_kind = false;
>   flush = false;
>   straight = false;
>   three_of_a_kind = false;
>   pairs = 0;
> 
>   // 檢查花色
>   for (int i = 0; i < NO_SUIT; i++) {
>     // flush
>     if (no_in_suit[i] == 5) {
>       flush = true;
>       break;
>     }
>   }
> 
>   int consec_num = 0;
> 
>   // 檢查點數
>   for (int i = 0; i < NO_RANK; i++) {
>     // 檢查 four_of_a_kind
>     if (no_in_rank[i] == 4) {
>         four_of_a_kind = true;
>         break;
>     }
>  
>     // 檢查 three_of_a_kind
>     if (no_in_rank[i] == 3)
>       three_of_a_kind = true;
> 
>     // 檢查 pair
>     if (no_in_rank[i] == 2)
>       pairs++;
> 
>     // 檢查 straight
>     for(int y = 0; i + y < NO_RANK && y < 5; y++) {
>       if (no_in_rank[i+y] == 1) 
>          consec_num++;
>       else {
>          consec_num = 0;
>          break;
>       }
>     }
>     if (consec_num == 5) {
>       straight = true;
>       break;
>     }
>   }
> }
> 
> void print_result(void) {
>   if (straight && flush)
>     printf("straight flush\n");
>   else if (four_of_a_kind)
>     printf("four of a kind\n");
>   else if (three_of_a_kind && pairs)
>     printf("full house\n");
>   else if (flush)
>     printf("flush\n");
>   else if (straight)
>     printf("straight\n");
>   else if (three_of_a_kind)
>     printf("three of a kind\n");
>   else if (pairs == 2)
>     printf("two pair\n");
>   else if (pairs)
>     printf("pair\n");
>   else 
>     printf("High card\n");
>   printf("\n");
> }
>```

>[!success]- 正確的 output
>```
> Enter a card: 2s
> Enter a card: 5s
> Enter a card: 4s
> Enter a card: 3s
> Enter a card: 6s
> straight flush
> 
> Enter a card: 8c
> Enter a card: as
> Enter a card: 8c
> Duplicate card; ignored.
> Enter a card: 7c
> Enter a card: ad
> Enter a card: 3h
> pair
> 
> Enter a card: 6s
> Enter a card: d2
> Please enter a correct rank
> Ranks: a 2 3 4 5 6 7 8 9 10 j q k
> Enter a card: 2d
> Enter a card: 9c
> Enter a card: 4h
> Enter a card: ts
> High card
> 
> Enter a card: 0
>```