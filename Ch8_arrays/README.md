# C program: a modern approach Ch.8 note

## Program overview

| 題號     | 功能                          | 觀念                                      | 連結                    |
| ------ | --------------------------- | --------------------------------------- | --------------------- |
| 範例一    | 將數字的前後順序顛倒並印出來              | 學習 for statement 與一維陣列的搭配               | [view](./reverse.c)   |
| 範例二    | 判斷是否有重複的數字                  | 學習一維陣列與 boolean value 的搭配。這是我寫的 program | [view](./repdigit.c)  |
| 範例二 v2 | 同上                          | 同上，且這是課本的 program                       | [view](./repdigit2.c) |
| 範例三    | 計算 n 年之後的金額與增加 1 到 4% 利息的狀況 | 利用兩個 for statement 操控兩個變數並且搭配一維陣列       | [view](./interest.c)  |
| 範例四    | 輸入牌數後抽牌                     | 將二維陣列作為檢查表，並且將一維陣列當作對照表                 | [view](./deal.c)      |


---
## I. One-Dimensional Arrays

#### 一，Intro

- array: 一種包含了數個數字的 data structure，裡面的數字就稱為 elements (元素)
- 宣告陣列<br>E.g: 內含 10 個 int type 的 element 的 array
	```c
	int a[10];
	```
	- **注意**裡面不存在 a[10] 這一個元素，因為從 0 開始數到 9
- 也可以運用 definition 宣告他的 element 數<br>E.g:
	```c
	#define N 10
	...
	int a[N];
	```
<br>

#### 二， Array Subscripting

- element 的名字是從 a[0] 開始數，一路數到 a[n-1]，裡面的 0 與 n-1 就稱為 **subscripting 或 indexing (下標)**
- **每一個 a[i] 皆為 lvalue**，所以可以像一般變數一樣運用<br>E.g:
	```c
	a[0] = 1;
	printf("%d\n", a[5]);
	++a[i];
	```
- 每一個的 **element 的運作原理都是和他的所屬的型別一樣**，例如前面宣告了 a[i] 皆是 `int` 那他們的運作方式就和 `int` 一模一樣
- for statement 可以與 array 搭配，進而去對**多個 element 下指令**<br>E.g:
	1. 
		```c
		for (i = 0; i < N; i++)
		  a[i] = 0;
		// clears a
		```
	2. 
		```c
		for (i = 0; i < N; i++)
		  scanf("%d", &a[i])
		// reads data into a
		```
	3. 
		```c
		for (i = 0; i < N; i++)
		  sum += a[i]
		// sums the elements of a
		```
	- **注意** 在用 for statement 的時候要小心元素是從 0 開始數到 n-1，如果不小心寫到了 a[n]，那就會是 **undefined behavior**
- subscript 也可以用 **expression 來作代表**，有 side effect 的 expression 也可<br>E.g:
	1. 
		```c
		a[i + j*10] = 0;
		```
	2. 
		```c
		i = 0;
		while (i < N)
		  a[i++] = 0;
		```
		- 運作方式：先判斷 i < N，再將原本 subscript 是 i 的 element 指派為 0 (因為是 postfix increment)，接著執行 increment (也就是換成**下一個 subscript 的 element**)
		- **注意**，如果用 ++i 的話會導致它更換 subscript 再指派，也就是**原來的 i 不會被指派到**
<br>

#### 三，範例一：Reversing a Series of Numbers

- program:
	```c reverse.c
	// Reverses a series of numbers
	
	#include <stdio.h>
	#define N 10
	
	int main(void)
	
	{
	    int a[N];
	
	    printf("Enter 10 numbers: ");
	    for (int i = 0; i < N; i++)
	      scanf("%d", &a[i]);
	
	    printf("In reverse order: ");
	    for (int i = N - 1; i >= 0; i--)
	      printf("%d ", a[i]);
	    printf("\n");
	
	    return 0;
	}
	```
- output:
	```
	Enter 10 numbers: 123 456 789 12 45 78 36 54 15 78
	In reverse order: 78 15 54 36 78 45 12 789 456 123 
	```
- 在寫 program 的時候犯的錯：
	1. 在 `printf("%d ", a[i])` 這行不小心寫成了 `printf("%d ")`，沒指定變數導致 ouput 變成了以下這樣
		```
		 Enter 10 numbers: 34 82 99 321 123 456 789 555 147 361
		 3 In reverse order: -286638054
		```
	2. 在第二個 for loop 在 ( ) 後就直接加了 ; 導致 gcc 報錯，說我的 i 沒有宣告（因為 i 是在 loop 內宣告的，在外面就等於沒宣告
		- gcc 的報錯
			```
			2 $ gcc -o reverse reverse.c
			33 reverse.c: In function ‘main’:
			34 reverse.c:17:23: error: ‘i’ undeclared (first use in this function)
			35    17 |       printf("%d ", a[i]);
			36       |                       ^
			37 reverse.c:17:23: note: each undeclared identifier is reported only once for each function it appears in
			```
		- 我錯的 program:
			```c
			56     for (int i = N - 1; i >= 0; i--);
			57       printf("%d ", a[i]);
			```
<br>

#### 四，Array Initialization

###### 1. list
- 其中一個 array initializer 的方式就是用一個 list
- 如果在初始化的時候沒有給予它元素數量的話，就會以 list 的個數來作為元素的數量
- 如果你初始化的數字小於他的元素數量的話，剩餘的就都會是 0<br>E.g:
	1. 
		```c
		int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		```
	2. 
		```c
		int a[10] = {0};
		// initial value of a is {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
		```
	3. 
		```c
		int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
		// 有 10 個 element
		```
###### 2. Designated Initializers in C99

- 用途：只想要初始化特定的元素，其他的元素用預設的數字 (也就是 0)<br>E.g:
	```c
	int a[15] = {[2] = 29, [9] = 7, [14] = 48};
	```
	等價於
	```c
	int a[15] = {0, 0, 29, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 48}
	```
	- 其中的 2, 9, 14 被稱為 **designator**
- 如果沒有給予陣列長度的話，那就會以最大的 designator 來當做最後一項<br>E.g:
	```c
	int b[] = {[5] = 10, [23] = 23, [11] = 36, [15] = 29};
	// a[23] 為最後一個元素，也就是說有 24 個元素
	```
- 也可以新舊方法混和初始化<br>E.g:
	```c
	int c[10] = {5, 1, 9, [4] = 3, 7, 2, [8] = 6}
	// 陣列的前三項會是 5, 1, 9
	// a[4] 會是 3
	// a[4] 後面的兩個元素為 7, 2
	// a[8] 會是 6
	// 剩下的皆為 0
	```
<br>

#### 五，範例二：Checking a Number for Repeated Digits

- Hint: 這個 program 有結合到 ch5 中的 boolean value，忘記的話可以去看一下
- 我的 program:
	```c
	// check numbers for repeated digits
	
	#include <stdbool.h>
	#include <stdio.h>
	
	int main(void)
	{
	    bool digit_seen[10] = {false};
	    int digit;
	    long n;
	
	    printf("Enter a number: ");
	    scanf("%ld", &n);
	
	    while (n != 0) {
	      digit = n % 10;
	      n /= 10;
	      if  (digit_seen[digit] == false)
	        digit_seen[digit] = true;
	      else
	        break;
	    }
	
	    if (n == 0)
	      printf("No repeated digit\n");
	    else
	      printf("Repeated digit\n");
	
	    return 0;
	}
	```
	- 因為是先更新 n 值才 break 所以就會導致在 if statement 的時候多除一個 10，導致結果有錯
- 課本上的 program:
	```c
	// check numbers for repeated digits
	
	#include <stdbool.h>
	#include <stdio.h>
	
	int main(void)
	{
	    bool digit_seen[10] = {false};
	    int digit;
	    long n;
	
	    printf("Enter a number: ");
	    scanf("%ld", &n);
	
	    while (n != 0) {
	      digit = n % 10;
	      if  (digit_seen[digit])
	        break;
	      digit_seen[digit] = true;
	      n /= 10;
	    }
	
	    if (n == 0)
	      printf("No repeated digit\n");
	    else
	      printf("Repeated digit\n");
	
	    return 0;
	}
	```
- 在寫 program 的時候犯的錯
	- 在 `scanf` 這行的 我不小心寫成了 `scanf("ld", &n)` 在編譯的過程中編譯器也沒報錯，導致我每次輸入完值的判斷的結果都是錯的。我一開始的時候還以為是 if statement 出錯，看了一段時間後才發現是少打了 `%`
- 學習到的東西
	1. 在宣告的時候要思考一下會不會需要較大的位數或精度來儲存值，以判斷要用哪一種的 type
	2. 要判斷位數的話就用除以 10 的方式
	3. 要看已經儲存進去的 variable 的每個位數的數字就用除以 10 的餘數
	4. array 可以結合 boolean value 來作判斷
	5. 在寫 if statement 的時候可以直接寫 `digit_seen[digit]` 就好而不用寫 == true，因為只要是非零的值就會被視為是 true
<br>

#### 六，using the `sizeof` Operator with Arrays

- 利用 `sizeof` 來算出陣列的元素個數
- form:
	```c
	sizeof(a) / sizeof(a[0])
	```
	- *全部的位元數除以單一元素用的位元數 = 陣列內的元素個數*
- 但有些編譯器可能會在以下的 expression 報錯
	```c
	i < sizeof(a) / sizeof(a[0])
	```
	因為 i 是 `int` 而 `sizeof(a) / sizeof(a[0])` 是 `size_t` (一種 unsigned type)，這時候就要搭配 casting 來使用
	```c
	i < (int) (sizeof(a) / sizeof(a[0]))
	``` 
- 好處：如果陣列長度要調整的話，就不需要手動調整數值了
- 也可以搭配 macro 來讓 program 更好讀 (也就是 \#define)<br>E.g:
	```c
	#define SIZE ((int) (sizeof(a) / sizeof(a[0])))
	
	for (i = 0; i < SIZE; i++)
	  a[i] = 0
	```
<br>

#### 七，範例三：Computing Interest

- 題目
- program:
	```c interest.c
	// Prints a table of compound interest
	
	#define PERCENT 0.01
	#define NUM_RATE ((int)(sizeof(money) / sizeof(money[0])))
	#include <stdio.h>
	
	int main(void)
	{
	    float  money[5];
	    int rate, num_year, initial_money;
	
	    printf("Enter initial investment amount: ");
	    scanf("%d", &initial_money);
	    for (int i = 0; i < NUM_RATE; i++)
	      money[i] = initial_money;
	    printf("Enter interest rate: ");
	    scanf("%d", &rate);
	    printf("Enter number of years: ");
	    scanf("%d", &num_year);
	
	    printf("\n");
	
	    printf("years   ");
	    for (int i = 0; i <= 4; i++) {
	      printf("%3d%%   ", rate + i);
	    }
	    printf("\n");
	
	    for (int i = 1; i <= num_year; i++) {
	      printf("%3d     ", i);
	      for(int y = 0; y < NUM_RATE; y++) {
	        money[y] *= (1 + (rate + y) * PERCENT);
	        printf("%6.2f ", money[y]);
	      }
	      printf("\n");
	    }
	    printf("\n");
	    return 0;
	}
	```
- output:
	```
	Enter initial investment amount: 100
	Enter interest rate: 2
	Enter number of years: 8
	
	years     2%     3%     4%     5%     6%   
	  1     102.00 103.00 104.00 105.00 106.00 
	  2     104.04 106.09 108.16 110.25 112.36 
	  3     106.12 109.27 112.49 115.76 119.10 
	  4     108.24 112.55 116.99 121.55 126.25 
	  5     110.41 115.93 121.67 127.63 133.82 
	  6     112.62 119.41 126.53 134.01 141.85 
	  7     114.87 122.99 131.59 140.71 150.36 
	  8     117.17 126.68 136.86 147.75 159.38 
	
	```
- 在這個 program 當中，我額外做了一個可以輸入初始的投資金額的問句
- 而且我寫完後才發現我的 program 的邏輯與範例的不太一樣
- 學習到的東西
	1. 排版可以用 %md 與空格來搭配，來達成置中的效果
	2. 在寫 program 的時候可以寫到一半，先確認一次會不會出錯在繼續寫，我這次是在
		```
	    printf("years   ");
	    for (int i = 0; i <= 4; i++) {
	      printf("%3d%%   ", rate + i);
	    }
		```
		這幾行來做測試，以確保排版與輸出正確
<br>

## II. Multidimensional Arrays

#### 一，Intro

- array 除了一維以外，還有更高維度的<br>E.g: 二維的陣列 (也就是數學上的 matrix)
	```c
	int m[5] [9];
	// 5 個 row，9 個 column
	```
- row-major order: 陣列是優先填完 row 0，再填 row 1，以此類推的
- 如果要像一維的陣列一樣與 for statement 搭配，就用多層的 for statement<br>E.g: 寫出 identity matrix
	```c
	#define N 10
	
	double ident[N][N];
	
	for (int row = 0; row < N; row++)
	  for (int col = 0; col < N; col++)
	    if (col == row)
	      ident[row][col] = 1.0;
	    else
	      ident[row][col] = 0.0;
	```
- 高維的陣列在 C 中扮演的角色反而沒那麼重要，因為 C 中還有 arrays of pointers (在 ch13.7)
<br>

#### Initializing a Multidimensional Array

- 一樣可以用 list (記住，是 row-major order)
	```c
	int m[5][9] = { {1, 1, 1, 1, 1, 1, 1, 1, 1},
	                {1, 1, 1, 1, 1, 1, 1, 1, 1},
	                {1, 1, 1, 1, 1, 1, 1, 1, 1},
	                {1, 1, 1, 1, 1, 1, 1, 1, 1},
	                {1, 1, 1, 1, 1, 1, 1, 1, 1} };
	```
- 一樣，如果有沒填到的數字就是 0<br>E.g:
	1. 有 row 完全沒填到，剩下的 row 全部都是 0：
		```c
		int m[5][9] = { {1, 1, 1, 1, 1, 1, 1, 1, 1},
		                {1, 1, 1, 1, 1, 1, 1, 1, 1} };
		```
	2. 有 row 沒填滿，一樣，沒填到的就是 0：
		```c
		int m[5][9] = { {1, 1, 1, 1, 1, 1, 1, 1, 1},
		                {1, 1, 1, 1, 1, 1, 1, 1},
		                {1, 1, 1, 1, 1, 1, 1},
		                {1, 1, 1, 1, 1, 1}
		                {1, 1, 1, 1, 1}};
		```
- designated initializer，與一維的一樣 <br>E.g:
	```c
	double ident[2][2] = {[0][0] = 1.0, [1][1] = 1.0};
	```
- 內層的 {} 可以省去，但編譯器可能會報錯
<br>

#### 二，Constant Arrays

- constant array 是指說不能被 program 所改動的 array
- 通常是用於儲存裡面有我們不想改動的資料的時候
- 不管幾維，只要在前面加上 `const` 就會變成 constant array<Br>E.g:
	```c
	const char hex_chars[] =
	  {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', 
	  'A', 'B', 'C', 'D', 'E', 'F'};
	```
<BR>

#### 三，範例四：Dealing a Hand of Cards

- 因為這一題光看它題目的說明就知道它用了一堆的沒學過的套件，所以我選擇了先將 program 抄下來，再將其分段理解
- program:
	```c
	// Deals a random hand of cards
	
	#include <stdbool.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	
	#define NUM_SUIT 4
	#define NUM_RANKS 13
	
	int main(void)
	{
	  bool in_hand[NUM_SUIT][NUM_RANKS] = {false};
	  int num_cards, rank, suit;
	  const char rank_code[] = {'2', '3', '4', '5', '6', '7', '8',
	                            '9', 't', 'j', 'q', 'k', 'a'};
	  const char suit_code[] = {'c', 'd', 'h', 's'};
	
	  srand((unsigned) time(NULL));
	
	  printf("Enter number of cards in hand: ");
	  scanf("%d", &num_cards);
	
	  printf("Your hand:");
	  while (num_cards) {
	    suit = rand() % NUM_SUIT;    // picks a random suit
	    rank = rand() % NUM_RANKS;    // picks a random rank
	    if (!in_hand[suit][rank]) {
	      in_hand[suit][rank] = true;
	      num_cards--;
	      printf(" %c%c", rank_code[rank], suit_code[suit]);
	    }
	  }
	  printf("\n");
	
	  return 0;
	}
	```
- 他的運作邏輯：
	1. 使用的套件
		```c
		#include <stdbool.h>  // 為了可以直接寫 true 與 false
		#include <stdlib.h>   // 為了用 rand(), strand()
		#include <time.h>     // 為了用 time()
		```
	2. 創建一個手上有哪張牌的檢查表 (一開始都沒牌)
		```c
		bool in_hand[NUM_SUIT][NUM_RANKS] = {false};
		```
	3. 創建一個對照表，將數字與代號 (花色與數字)連接起來
		```c
	  const char rank_code[] = {'2', '3', '4', '5', '6', '7', '8',
	                            '9', 't', 'j', 'q', 'k', 'a'};
	  const char suit_code[] = {'c', 'd', 'h', 's'};
		```
	4. 設定隨機
		```c
		srand((unsigned) time(NULL));
		// 這行是為了等一下的 rand() 的
		// rand() 就是一個有隨機亂數的書
		// 但如果不設定從哪一頁翻就都會從第一頁去翻
		// srand() 就是設定要從哪一頁開始翻的
		// 利用 time(NULL) 來找出現在的時間，並且當作頁數
		// 因為時間不會重複， 所以就一定不會有重複的
		```
	5. 輸入手上的牌數
		```c
		printf("Enter number of cards in hand: ");
		scanf("%d", &num_cards);
		```
	6. while statement
		```c
		while (num_cards) {
		// 判斷手上是否還需要牌
		  suit = rand() % NUM_SUIT;   
		  rank = rand() % NUM_RANKS;
		  // 利用前面在 strand() 就決定好的頁數來產生新的亂數
		  // rand() 就是那個亂數
		  // 利用餘數來決定是要用幾號牌與幾號的花色
		  // (利用餘數必定會有與餘數的值相同的可能性)
		  // (例如除 4 就可能餘 0, 1, 2, 3，四種)
		  if (!in_hand[suit][rank]) {
		    in_hand[suit][rank] = true;
		    num_cards--;
			printf(" %c%c", rank_code[rank], suit_code[suit]);
			// 進行判斷是否是重複的牌
			// !in_hand[suit][rank] 中的 ! 代表如果是 false
			// 則將其設定為有該張牌 (true)
			// 需要的牌 - 1
			// 利用剛剛餘的數與對照表找出真實的花色與數字
			// 否則，就直接執行下一次，而不做任何的事情
		  }
		}
		```
- 重點：
	1. 用 array 當作對照表
	2. 結合 boolean value 來作為檢查表
<br>

## III. Variable-Length Arrays

- variable-length array (簡稱 VLA)：宣告陣列的時候不給它一個實際的元素個數，而是用一個變數取代，讓它可以依照所需的元素數量來建造陣列<br>E.g:
	```c
	int n;
	int a[n];
	```
- 不一定要是單一一個 variable， expression 也可<br>E.g:
	```c
	int a[3*i +5];
	int b[j+k];
	int c[m][n];
	```
<br><br>

# Exercises

#### Ex.1: 用 sizeof(a) / sizeof(t) 為何較差

- 我的答案：因為如果在宣告上改了陣列元素的型別，但 `sizeof(t)` 中的 type 卻沒有改，就會不對了
<br>

#### Ex.2: 用 character 來寫 subscript

- 我的答案：
	```
	digit_count[ch - '0']
	```
- Reason: 因為 ASCII 是從 0 開始往上數他的代碼 (0 是 48)
<br>

#### Ex.3: 初始化陣列為 boolean value

- 我的答案：
	```c
	#include <stdbool.h>
	
	bool weekend[7] = {true, false, false, false, false, false, true};
	```
<br>

#### Ex.4: 用 designated initializer 初始化

- 我的答案
	```c
	#include <stdbool.h>
	
	bool seekend[7] = {[0] = true, [6] = true};
	```
<br>

#### Ex.5: 用 for loop 來創建 fibonaccin numbers

- 我的答案
	```c
	int fib_numbers[40] = {0, 1};
	
	for (int i = 2; i < 40; i++)
	  fib_numbers[i] = fib_numbers[i-1] + fib_numbers[i-2];
	```
<br>

#### Ex.6: 寫出二維陣列，並初始化

- 我的答案
	```c
	const int segments[10][7] = {{1, 1, 1, 1, 1, 1, 0},  // 0
	                             {0, 1, 1, 0, 0, 0, 0},  // 1
	                             {1, 1, 0, 1, 1, 0, 1},  // 2
	                             {1, 1, 1, 1, 0, 0, 1},  // 3
	                             {0, 1, 1, 0, 0, 1, 1},  // 4
	                             {1, 0, 1, 1, 0, 1, 1},  // 5
	                             {1, 0, 1, 1, 1, 1, 1},  // 6
	                             {1, 1, 1, 0, 0, 0, 0},  // 7
	                             {1, 1, 1, 1, 1, 1, 1},  // 8
	                             {1, 1, 1, 1, 0, 1, 1}}; // 9
	```
<br>

#### Ex.7:
- 因為只是將上面的改用 designated initialize，所以就不寫了
<br>

#### Ex.8: 宣告二維矩陣
- 我的答案： 
	```c
	#define DAYS_IN_MONTH 30
	#define HOURS_IN_DAY 24
	
	float temperature_readings[DAYS_IN_MONTH][HOURS_IN_DAY]
	```
<br>

#### Ex.9: 計算二維陣列的平均
- 我的答案：
```c
#define DAYS_IN_MONTH 30
#define HOURS_IN_DAY 24

float sum_temperature = 0.0f, ave_temperature;
float temperature_readings[DAYS_IN_MONTH][HOURS_IN_DAY];

for (int day = 0; day < DAYS_IN_MONTH; day++)
  for (int hour = 0; hour < HOURS_IN_DAY; hour++)
    sum_temperature += temperature_readings[day][hour];
ave_temperature = sum_temperature / (DAYS_IN_MONTH * HOURS_IN_DAY);

```
<br>

#### Ex.10: 二維矩陣的初始化
- 我的答案
```c
char chess_board[8][8] = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
                          {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                          {' ', '.', ' ', '.', ' ', '.', ' ', '.'},
                          {'.', ' ', '.', ' ', '.', ' ', '.', ' '},
                          {' ', '.', ' ', '.', ' ', '.', ' ', '.'},
                          {'.', ' ', '.', ' ', '.', ' ', '.', ' '},
                          {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                          {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
```
<br>

#### Ex.11: 用 for statement 來指派二維矩陣
- 我的答案
```c
#define NUM_ROW 8
#define NUM_COL 8

char checker_board[NUM_ROW][NUM_COL];

for (int i = 0; i < NUM_ROW; i++)    // row i
  for (int j = 0; j < NUM_COL; j++)  // col i
    if ((i + j) % 2)
      checker_board[i][j] = 'R';
    else
      checker_board[i][j] = 'B';
```
<br><br>