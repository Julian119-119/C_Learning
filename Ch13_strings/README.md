# C program: a modern approach Ch.13 note

## Program overview


| 題號      | 功能                 | 觀念                      | 連結                                      |
| ------- | ------------------ | ----------------------- | --------------------------------------- |
| 範例一     | 輸入一個月內的事情，並依日期排序輸出 | string.h 中關於 string 的操作 | [view](./remind.c)                      |
| 範例二     | 檢查行星的名字            | 學習使用命令列引數               | [view](./planet.c)                      |
| Proj.4  | 將命令列引數倒著列印         | 用雙重指標移動 argument vector | [view](./programming-project_Ch13_4.c)  |
| Proj.5  | 將命令列引數轉為數值並加總      | 學習使用命令列引數，並將子串轉換為數值     | [view](./programming-project_Ch13_5.c)  |
| Proj.18 | 將數字的月份轉為月份名        | 使用指標的陣列來對照月份            | [view](./programming-project_Ch13_18.c) |
<br><br>

---
## Note
### I. String Literals

#### 一，Intro

- string literals (字串常值)： 被包含在 "" 中的一連串字元<br>E.g:
	```
	"When you come to a fork in the road, take it"
	```

#### 二，Escape Sequences in String Literals

- 在 Ch7 中所出現的 escape sequence 也都可以出現在 string literals 中<br>E.g:
	```
	"Cand\nIs dandy\nBut liquor\nIs quicker.\n --Ogden Nash\n"
	```
	結果會是
	```
	Candy
	Is dandy
	But liquor
	Isquicker.
	 --Ogden Nash
	```
- 雖然也可以用 octal 與 hexadecimal escape ，但並不常見

#### 三，Continuing a String Literal

- 如果覺得 string literal 太長，可以**用 \\ 來換行** (與終端機相同)<br>E.g:
	```c
	printf("When you come to a fork in the road, take it. \
	--YogiBerra");
	```
- 但因為用\\ 的話必須要在 \\ 後就直接接上字元，所以會**破壞縮排**
- 如果不想破壞縮排的話，可以直接用**多個 \""**<br>E.g:
	```c
	printf("When you come to a fork in the road, take it. "
	       "--Yogi Berra");
	```
	- *備註，這樣不會換行，因為沒有換行符*

#### 四，How String Literals Are Stored

- 物理儲存：
	- 當遇到 string literals 的時後， C 會將其作為**陣列來儲存**
	- 而如果長度為 n，則 C 會提供 n + 1 個 byte 的位置，而最後一個位置需要**作為 straing literals 結束的符號**
	- 而結束的符號就是 **null character**，也就是 **'\0'** (與 0 不同， 0 的 ASCII 代號為 48，而 null character 為 0)
- 邏輯使用：
	- 在運用 string literals 時，他是作為**指標來運作**的
	- 他的型別為 `char *` (\* 代表的是**指標**，不是值)
	- 以 `printf("abc");` 為例
		1. C 會先以陣列的形式來儲存 abc<br>示意圖如下<br>![](./Ch13_attachment/c-programming_a-modern-approach_ch13_1.png)
		2. 接著以 "abc" 呼叫出來 (用指標的概念去想)
<br>

#### 五，Operations on String Literals

- 因為 string literal 的型別為 `char *p`，所以照著**指標的邏輯去使用**<br>E.g:
	```c
	char *p;
	
	p = "abc"
	```
	也可以**加入 indexing**
	```c
	char ch;
	
	ch = "abc"[1]
	```
	這樣的話 ch 就是指向字母 b (0 是 a， 1 是 b， 2 是 c)
- 範例，將一般的數字換成 hex digit
```c
char digit_to_hex_char(int digit)
{
  return "0123456789ABCDER"[digit]
}
```
- 注意，**如果調整字會造成 undefined behavior**<br>E.g:
	```C
	char *p = "abc";
	
	*p = 'd';
	// WRONG
	```
<br>

#### 六，String Literals versus Character Constants

- string literals 用 **""** 包起來，而 character constants 用 **''** 包起來
- string literal 代表的是一個**指標**，而 character constants  則是 **integer** (也就是 numerical code 字元碼)
- 注意，這兩者不可混用<br>E.g:
	```c
	printf("\n");
	
	printf('\n');
	// WRONG
	// 因為 printf() 需要的引數為 char *，所以不可以用 ''
	```
<Br>

### II. String Variables

#### 一，Intro

- 任何一個 **char 型別的一維陣列都可以用來儲存 string literal** (但要記得要保留最後一格**加上 \\0**)<br>idiom:
	```c
	#define STR_LEN 80
	...
	char str[STR_LEN+1];
	```
- 雖然陣列長度為 80 + 1 ，但不必然 string literal 長度比然是 80 ，因為 string literal 的**結束是由 null characters 決定** ，不是看陣列長度， 80 僅僅是**最大值**
<br>

#### 二，Initializing a String Variable

- string variable 的 initialize <br>E.g:
	```c
	char date1[8] = "June 14";
	```
	記憶體中的示意圖<br>![](./Ch13_attachment/c-programming_a-modern-approach_ch13_2.png)
- 雖然以上的例子為 string variable，但 c 其實是將其視為陣列初始化的縮寫，也就是等價於
	```c
	char date1[8] = {'J', 'u', 'n', 'e', ' ', '1', '4', '\0'};
	```
- 如果字數太少的話編譯器會**自動增加 null character**<br>E.g:
	```c
	char date2[9] = "June 14";
	```
	示意圖：![](./Ch13_attachment/c-programming_a-modern-approach_ch13_3.png)
- 如果格子數太少的話， **null character 會被丟棄，導致不能被作為 string variable 來使用**<br>E.g:
	```c
	char date3[7] = "June 14";
	```
	示意圖<br>![](./Ch13_attachment/c-programming_a-modern-approach_ch13_4.png)
- 如果陣列沒有指定長度，則編譯器會自動算出 string literal + null character 的長度，讓它可以**剛好放下去** (**長度之後不可被變動**)<Br>E.g:
	```c
	char date4[] = "June 14";
	```
<br>

#### 三，Character Arrays versus Character Pointers

- 在 C 之中
	```c
	char date[] = "June 14";
	```
	與
	```c
	char *date = "June 14";
	```
	雖然皆是**合法**的，但兩者有不同之處
- 不同之處
	1. 在陣列中，裡面的元素**可以被更換**<br>在指標中，因為指向的是 string literal，所以它**無法被更換**
	2. 在陣列中， date 為**陣列的名字**<br>在指標中， date 則為**指標變數**，可以被**更改指向其他的字串**
- 不同的初始化方式
	1. 
		```c
		char *p;
		```
		編譯器先給與 p 一個儲存位址的空間，但並**沒有給予它儲存 string 的空間，所以還不能直接給予 string**
	2. 給予 string 空間的方式<br>E.g:
		```c
		char str[STR_LEN+1], *p;
		
		p = str;
		```
	- 注意：**不可以用沒有給予 string 空間就直接指向 character**<Br>E.g:
		```c
		char *p;
		
		p[0] = 'a';   // WRONG
		p[1] = 'b';   // WRONG
		p[2] = 'c';   // WRONG
		p[3] = '\0';  // WRONG
		```
<br>

### III. Reading and Writing Strings

#### 一，Writing Strings Using `printf` and `puts`

1. `printf()`
	- string 所用的 conversion specification 為 `%s`<br>E.g:
		```c
		char str[] = "Are we having fun yet?"
		
		printf("%s\n", str);
		```
		output:
		```
		Are we having fun yet?
		```
	- `printf` 會一路印出，直到遇到 null character
	- 如果要印出一部份的字串的話，可以加上 `%.ps` (p 為要印出的字數)<br>E.g:
		```c
		printf("%.6s\n", str);
		```
		將會印出
		```
		Are we
		```
	- 在 `%ms` 中的 m 則與 integer 相同，至少要顯示到多少格。- 號為置左， + 號為置右
1. `puts`
	- E.g:
		```c
		puts(str);
		```
		因為 `puts` 只有一個引數，所以它永遠會寫入一個換行符
<br>

#### 二，Reading Strings Using `scanf` and `gets`

1. `scanf()`
	- 讀取字串所用的 conversion specification 為 `%s`<br>E.g:
		```c
		scanf("%s", str);
		```
	- **不需要用 &**，因為 str 被視為 pointer (因為陣列的名稱為第一個元素的指標)
	- 它會自動放置一個 \\0 在後面
	- 但 `scanf()` 會**忽略所有的空白**，且 **\\n, tab, space 皆會會導致它停止輸入**
2. `gets`
	- 與 `scanf` 不同之處
		1. `gets` **不會跳過空白**
		2. **只有遇到 \\n 的時候會停下來**
	- 與 `scanf` 一樣會放置 \\0 在最後面與 \\n 不會被儲存進陣列中<br>E.g: 輸入 To C, or not to C: that is the question.
		1. `scanf`<br>Program:
			```c
			char sentence[SENT_LEN+1];
			
			printf("Enter a sentence:\n");
			scanf("%s", sentence);
			```
			結果：只會讀到 To (因為後面接的是空白鍵)
		2. `gets`<br>將 `scanf` 那行改成
			```c
			gets(sentence);
			```
			結果：會讀到To C, or not to C: that is the question. (也就是全部)
- 注意：`scanf` 與 `gets` 都**不會偵測到陣列是否滿了**，但
	- `scanf` 可以使用 %ns 來限制輸入的大小 (n 為最大輸入值)
	- `gets` 則沒有，所以建議改用 `fgets` (在 ch22.5 會講)
<br>

#### 三，Reading Strings Character by Character

- 因為用 `scanf` 或 `gets` 都有相同的問題，所以可以自己設計一個讀取的 function 來輸入字串
- 需要考量的要點：
	1. 是否要跳過空白
	2. 要用什麼來當做結束的符號
	3. 如果長度超過陣列怎麼辦
- E.g: 不跳過空白鍵，且遇到 \n 的時候結束
	- prototype
		```c
		int read_line(char str[], int n);
		```
		str\[] 是用來讀取字串，而 n 則是最大輸入值 (也就是陣列長度 - 1，保留最後一格給 \\0)
	- program
		```c
		int read_line(char str[], int n)
		{
		  int ch, i = 0;
		  
		  while ((ch = getchar) != '\n')
		    if (i < n)
		      str[i++] = ch;
		  str[i] = '\n';
		  // terminates string
		  return i;
		  // number of characters stored
		}
		```
		注意： ch 的型別為 **`int`，因為要接受 getchar()**，所以必須用 `int`
<br><Br>

### IV. Accessing the Characters in a String

- 因為字串是以陣列的方式來儲存的，所以可以以陣列的方式來使用<br>E.g: 計算在字串內的空白有多少
	1. 一般變數的寫法 
		```c
		int count_space(const char s[])
		{
		  int count = 0;
		  
		  for (int i = 0; s[i] != '\0'; i++)
		    if (s[i] == ' ')
		      count++;
		  return count;
		}
		```
	2. 指標的寫法
		```c
		int count_space(const char *s)
		{
		  int count = 0;
		  
		  while (*s != '\0') {
		    if (*s == ' ')
		      count++;
		    s++;
		  }
		  return count;
		}
		```
<br>

### V. Using the C String Library

#### 一，Intro

- 在一般的狀況下，因為字串的運作原理是陣列，所以**無法使用 operator 來複製與比較**<br>E.g:
	1. 
		```c
		char str1[10], str2[10];
		
		str1 = "abc"; // WRONG
		str2 = str1; // WRONG
		```
		因為在 Ch12.3 中有說過**陣列名稱不可以作為 lvalue**，但下面的 statement 可以
		```c
		char str1[10] = "abc";
		```
		因為這是**初始化**
	2. 
		```c
		if (str1 == str2)... // WRONG
		```
		這個也不行，因為兩者的記憶體恆不相同，所以這個是恆等式
- 接下來會用的 statement，皆是屬於 **<string.h>** 這個標頭檔的
- 在 <string.h> 中的 function 大部分都需要至少一個字串作為引數
- 且 string parameter 皆為 `char *` 的型別
<br>

#### 二，The `strcpy`(string copy) Function

1. strcpy:
	- 在 <string.h> 中的 prototype
		```c
		char *strcpy(char *s1, const char *s2);
		```
	- `strcpy` 會將**字串 s2 複製進字串 s1**，且會回傳 s1，因為 s2 不會被動到，所以增加了一個 `const` 的型別
	- 雖然有回傳值，但其實也可以直接丟棄 (只要是 function 皆可)
	- 用以代替字串無法直接複製進陣列的問題<br>E.g:
		```c
		str2 = "abcd";
		// WRONG
		```
		要改成
		```c
		strcpy(str2, "abcd");
		// str2 now contains "abcd"
		```
		接著可以直接複製進 str1
		```c
		strcpy(str1, str2);
		```
	- 雖然絕大多數的時間都會直接丟棄回傳值，但有時候也可以多加利用<br>E.g:
		```c
		strcpy(str1, strcpy(str2, "abcd"))
		// both str1 and str2 now contain "abcd"
		```
	- 但要小心，strcpy **不會檢查陣列是否塞的進去**
2. strncpy:
	- 有**三個引數**<Br>E.g: 將 str2 複製進 str1
		```c
		strncpy(str1, str2, sizeof(str1))
		```
	- 如果超過 str1 所能容納的範圍，它會**停止在剛好 str1  塞滿的時候**，但**不會有 null character**
	- 更安全的作法
		```c
		strncpy(str1, str2, sizeof(str1) - 1);
		str1[sizeof(str1 - 1)] = '\0'
		```
		這樣最後一格就確保會是 null character
<Br>

#### 三，The `strlen` (String Length) Function

- prototype
	```c
	size_t strlen(const char *s);
	```
	- `size_t` 為  `typedef` 名字，代表 **unsigned integer types**
- `strlen` 會**回傳字串 s 的長度** (從開頭到 null character，但不包含到 null character)，**不是陣列的長度**
- E.g:
	```c
	int len;
	
	len = strlen("abc");  // len is now 3
	len = strlen("");     // len is now 0
	strcpy(str1, "abc");
	len = strlen(str1);   // len is now 3
	```
<br>

#### 四，The `strcat` (String Concatenation) Function

1. strcat
	- prototype
		```c
		char *strcat(char *s1, const char *s2);
		```
	- `strcat` 會將**字串 s2 複製進字串 s1 的後面**
	- **回傳 s1** (也就是結果字串的指標)
	- E.g:
		1. 不使用回傳值
			```c
			strcpy(str1, "abc");
			strcat(str1, "def");    // str1 now contains "abcdef"
			strcpy(str1, "abc");
			strcpy(str2, "def");
			strcat(str1, str2);    // str1 now contains "abcdef"
			```
		2. 使用回傳值
			```c
			strcpy(str1, "abc");
			strcpy(str2, "def");
			strcat(str1, strcat(str2, "ghi"));
			  // str1 now contains "abcdefghi";
			  // str2 contains "defghi"
			```
	- 注意：**如果 str1 的大小不夠將字串 str2 放入，會產生 undefined behavior**
2. strncat
	- 與 strncpy 一樣，都是**較為安全的版本**
	- 有**三個引數**
	- E.g:
		```c
		strncat(str1, str2, sizeof(str1) - strlen(str1) - 1);
		```
		- *注，最後一個的用意引數為：總空間 sizeof(str1) 減去已用去的時間 strlen(str1) 最後再減掉 null character 所需的空間*
<br>

#### 五，The `strcmp` (String Comparison) Function

- prototype
	```c
	int stcmp(const char *s1, const char *s2);
	```
- 回傳值
	- s1 **<** s2: 回傳值**小於 0**
	- s1 **\==** s2: 回傳值**等於 0**
	- s1 **>** s2: 回傳值**大於 0**
- E.g:
	1. 
		```c
		if (strcmp(str1, str2) < 0)
		// 如果 str1 小於 str2
		  ...
		```
	2. 
		```c
		if (strcmp(str1, str2) <= 0)
		// 如果 str1 小於或等於 str2
		  ...
		```
- 比較大小的邏輯
	- 依據 lexicographic ordering (字典序) 來比較大小
	- 由左置右來比大小<br>E.g:
		1. "abc" 與 "bcd"
			- 因為 a 比 b 小，所以 "abc" 比 "bcd" 還小，其他的根本不會被比較
		2. "abd" 與 "abe"
			- 理由同上，因為 d 比 e 小 (前兩個相等)，所以 "abd" 比 "abe" 小
	- 長度較小的就比較小<br>E.g:
		- "abc" 與 "abcd"
			- 因為前兩項相等，且 "abc" 比較短，所以 "abc" 小於 "abcd" (可以想成已經遇到 null character，所以後面的字母必定比較大)
	- 依據 ASCII 的編碼比較
		- 由大到小編碼順序為 **A-Z, a-z, 0-9**
<br>

#### 六，範例一：Printing a One-Month Reminder List

###### 第一版：讀取一行的字串

>[!success]- program
>```c
> // Prints a one-month reminder list
> 
> #include <stdio.h>
> #include <string.h>
> 
> #define MAX_WORD 50
> #define MAX_DAY 15
> 
> // prototype
> void read_line(char str[], int n);
> 
> int main(void) {
>   char str[MAX_DAY][MAX_WORD], temp_str[MAX_WORD];
> 
>   printf("Enter day and reminder: ");
>   read_line(temp_str, MAX_WORD);
> 
>   printf("%s\n", temp_str);
> }
> 
> void read_line(char str[], int n) {
>   int ch;
>   char* p;
> 
>   for (p = str; (ch = getchar()) != '\n'; p++)
>     if (p < str + n - 1)
>       *p = ch;
>     else
>       break;
>   p[1] = '\0';
> }
>```

>[!success]- output
>```
>$ ./remind 
>Enter day and reminder: 24 Susan's birthday
>24 Susan's birthday
>```

###### 第二版：讀取多行的字串，並排列順序

- 問題點：
	1. 如果要儲存陣列的 row 的指標的話，要宣告一維陣列的指標
	2. 一維陣列的指標要記得加上 ()
	3. \* 的意思是指向的東西的實際值，因為在 assignment 時所用的就是陣列的名稱，所以解值時就會變成陣列的名稱 (也就是**前面所宣告的陣列中第一個元素的位址**)

>[!bug]- program
>```c
> // Prints a one-month reminder list
> 
> #include <stdio.h>
> #include <string.h>
> 
> #define MAX_WORD 50
> #define MAX_DAY 15
> 
> // prototype
> int read_line(void);
> void store_str(char* last_reminder_row);
> void print_str(char* last_reminder_row);
> 
> // external variable
> char str[MAX_DAY][MAX_WORD], temp_str[MAX_WORD];
> 
> int main(void) {
>   char* last_reminder_row = str;
> 
>   for (;;) {
>     printf("Enter day and reminder: ");
>     if (!read_line()) {
>       break;
>     }
>     last_reminder_row++;
>     store_str(last_reminder_row);
>   }
> 
>   print_str(last_reminder_row);
> 
>   return 0;
> }
> 
> int read_line(void) {
>   int ch;
>   char* p;
> 
>   // 檢查第一個字元是否為 0
>   if ((ch = getchar()) == '0') {
>     return 1;
>   } else {
>     str[0] = ch;
>   }
> 
>   // 輸入第二個以後的字元
>   for (p = str + 1; (ch = getchar()) != '\n'; p++)
>     if (p < str + MAX_WORD - 1)
>       *p = ch;
>     else
>       break;
>   p[1] = '\0';
> 
>   return 0;
> }
> 
> void store_str(char* last_reminder_row) {
>   char *row_position = str, *move_row;
> 
>   // 找出 temp_str 所適合的位置
>   while (strcmp(temp_str, row_position) < 0) {
>     row_position++;
>   }
> 
>   // 從最後的 reminder (也就是 row) 開始移動
>   // 空出空間給新的字串
>   for (move_row = last_reminder_row; row_position <= move_row; move_row--) {
>     strcpy(move_row + 1, move_row);
>   }
> 
>   // 新的字串放入正確的位子中
>   strcpy(row_position, temp_str);
> }
> 
> void print_str(char* last_reminder_row) {
>   for (char* p = str; p <= last_reminder_row; p++) {
>     printf("%s", *p);
>   }
> }
>```

>[!failure]- 編譯器的報錯
>```
>$ gcc -o remind remind.c 
>remind.c: In function ‘main’:
>remind.c:18:29: warning: initialization of ‘char *’ from incompatible pointer type ‘char (*)[50]’ [-Wincompatible-pointer-types]
>   18 |   char* last_reminder_row = str;
>      |                             ^~~
>remind.c: In function ‘read_line’:
>remind.c:42:12: error: assignment to expression with array type
>   42 |     str[0] = ch;
>      |            ^
>remind.c:46:10: warning: assignment to ‘char *’ from incompatible pointer type ‘char (*)[50]’ [-Wincompatible-pointer-types]
>   46 |   for (p = str + 1; (ch = getchar()) != '\n'; p++)
>      |          ^
>remind.c:47:11: warning: comparison of distinct pointer types lacks a cast
>   47 |     if (p < str + MAX_WORD - 1)
>      |           ^
>remind.c: In function ‘store_str’:
>remind.c:57:24: warning: initialization of ‘char *’ from incompatible pointer type ‘char (*)[50]’ [-Wincompatible-pointer-types]
>   57 |   char *row_position = str, *move_row;
>      |                        ^~~
>remind.c: In function ‘print_str’:
>remind.c:75:18: warning: initialization of ‘char *’ from incompatible pointer type ‘char (*)[50]’ [-Wincompatible-pointer-types]
>   75 |   for (char* p = str; p <= last_reminder_row; p++) {
>      |                  ^~~
>```

- 問題點：
	- 因為 `strcmp` 是以字典排序來比較大小的，所以會造成 12 比 5 小
	- 因此必須要用 scanf 來強制讓它變成 05
- 學習重點
	- `sprintf` 用途：把格式化的資料（文字、數字）輸出到**記憶體中的字串陣列**

>[!bug]- 修改後的 program
>```c
> // Prints a one-month reminder list
> 
> #include <stdio.h>
> #include <string.h>
> 
> #define MAX_WORD 50
> #define MAX_DAY 15
> 
> // prototype
> int read_line(void);
> void store_str(char (*last_reminder_row)[MAX_WORD]);
> void print_str(char (*last_reminder_row)[MAX_WORD]);
> 
> // external variable
> char str[MAX_DAY][MAX_WORD], temp_str[MAX_WORD];
> 
> int main(void) {
>   // 修正點：要存入一整個 row 的話，就必須要宣告一個
>   // 一維陣列的指標
>   char (*last_reminder_row)[MAX_WORD] = str;
> 
>   for (;;) {
>     printf("Enter day and reminder: ");
>     if (read_line() == 1) {
>       break;
>     }
>     store_str(last_reminder_row);
>     last_reminder_row++;
>   }
> 
>   print_str(last_reminder_row);
> 
>   return 0;
> }
> 
> int read_line(void) {
>   int ch;
>   char* p;
> 
>   // 檢查第一個字元是否為 0
>   if ((ch = getchar()) == '0') {
>     return 1;
>   } else {
>     temp_str[0] = ch;
>   }
> 
>   // 輸入第二個以後的字元
>   for (p = temp_str + 1; (ch = getchar()) != '\n'; p++)
>     if (p < temp_str + MAX_WORD - 1)
>       *p = ch;
>     else
>       break;
>   *p = '\0';
> 
>   return 0;
> }
> 
> void store_str(char (*last_reminder_row)[MAX_WORD]) {
>   // 修正點：
>   char (*row_position)[MAX_WORD] = str, (*move_row)[MAX_WORD];
> 
>   // 找出 temp_str 所適合的位置
>   while (strcmp(temp_str, *row_position) < 0 &&
>          row_position < last_reminder_row) {
>     row_position++;
>   }
> 
>   // 從最後的 reminder (也就是 row) 開始移動
>   // 空出空間給新的字串
>   for (move_row = last_reminder_row; row_position <= move_row; move_row--) {
>     strcpy(move_row[1], *move_row);
>   }
> 
>   // 新的字串放入正確的位子中
>   // 修正點：因為之前指派 row_position 為 str
>   // 所以當用上 * 的時候會變成 str (也就是陣列的位址)
>   strcpy(*row_position, temp_str);
> }
> 
> void print_str(char (*last_reminder_row)[MAX_WORD]) {
>   printf("\n");
>   for (char (*p)[MAX_WORD] = str; p <= last_reminder_row; p++) {
>     printf("%s\n", *p);
>   }
> }
>```

>[!failure]- output
>```
>Enter day and reminder: 24 Susan's birthday
>Enter day and reminder: 5 6:00 - Dinner with Marge and Russ
>Enter day and reminder: 26 Movie - "Chinatown"
>Enter day and reminder: 7 10:30 - Dental appointment
>Enter day and reminder: 12 Movie - "Dazed and Confused"
>Enter day and reminder: 5 Saturday class
>Enter day and reminder: 12 Saturday class
>Enter day and reminder: 0
>
>7 10:30 - Dental appointment
>5 Saturday class
>5 6:00 - Dinner with Marge and Russ
>26 Movie - "Chinatown"
>24 Susan's birthday
>12 Saturday class
>12 Movie - "Dazed and Confused"
>```

>[!success]- 修正後的 program
>```c
> // Prints a one-month reminder list
> 
> #include <stdio.h>
> #include <string.h>
> 
> #define MAX_WORD 50
> #define MAX_DAY 15
> 
> // prototype
> void read_line(char msg_str[MAX_WORD], int n);
> void store_str(char day_str[MAX_WORD], char (*next_empty_row)[MAX_WORD]);
> void print_str(char (*next_empty_row)[MAX_WORD]);
> 
> // external variable
> char month_str[MAX_DAY][MAX_WORD];
> 
> int main(void) {
>   // 修正點：要存入一整個 row 的話，就必須要宣告一個
>   // 一維陣列的指標
>   char (*next_empty_row)[MAX_WORD] = month_str;
>   int day;
>   char msg_str[MAX_WORD], day_str[MAX_WORD];;
> 
>   for (;;) {
>     // 判斷是否有位子繼續輸入
>     if (next_empty_row >= month_str + MAX_DAY) {
>       printf("---no space left---");
>       break;
>     }
> 
>     printf("Enter day and reminder: ");
>     // 讀取前面的數字並格式化
>     scanf("%2d", &day);
>     // 判斷是否為 0
>     if (!day) break;
>     // 讀取剩餘的字
>     read_line(msg_str, MAX_WORD);
>     // 黏合數字與文字並儲存在 day_str 之中
>     sprintf(day_str, "%2d %s", day, msg_str);
> 
>     // 將 day_str 儲存進 month_str 之中
>     store_str(day_str, next_empty_row);
>     next_empty_row++;
>   }
> 
>   print_str(next_empty_row);
> 
>   return 0;
> }
> 
> void read_line(char msg_str[], int n) {
>   int ch;
>   char* p;
> 
>   // 清空前面的空白
>   while ((ch = getchar()) == ' ');
> 
>   // 輸入第一個字元
>   msg_str[0] = ch;
> 
>   // 輸入第二個以後的字元
>   for (p = msg_str + 1; (ch = getchar()) != '\n'; p++)
>     if (p < msg_str + n - 1)
>       *p = ch;
>     else
>       break;
>   *p = '\0';
> }
> 
> void store_str(char day_str[], char (*next_empty_row)[MAX_WORD]){
>   // 修正點：
>   char (*row_position)[MAX_WORD] = month_str, (*move_row)[MAX_WORD];
> 
>   // 找出 temp_str 所適合的位置
>   while (strcmp(day_str, *row_position) >= 0 &&
>          row_position < next_empty_row) {
>     row_position++;
>   }
> 
>   // 從最後的 reminder (也就是 row) 開始移動
>   // 空出空間給新的字串
>   for (move_row = next_empty_row; row_position <= move_row; move_row--) {
>     strcpy(*move_row, *(move_row - 1));
>   }
> 
>   // 新的字串放入正確的位子中
>   // 修正點：因為之前指派 row_position 為 str
>   // 所以當用上 * 的時候會變成 str (也就是陣列的位址)
>   strcpy(*row_position, day_str);
> }
> 
> void print_str(char (*next_empty_row)[MAX_WORD]) {
>   printf("\n");
>   for (char (*p)[MAX_WORD] = month_str; p <= next_empty_row; p++) {
>     printf("%s\n", *p);
>   }
> }
>```

>[!success]- output
>```
>Enter day and reminder: 24 Susan's birthday
>Enter day and reminder: 5 6:00 - Dinner with Marge and Russ
>Enter day and reminder: 26 Movie - "Chinatown"
>Enter day and reminder: 7 10:30 - Dental appointment
>Enter day and reminder: 12 Movie - "Dazed and Confused"
>Enter day and reminder: 5 Saturday class
>Enter day and reminder: 12 Saturday class
>Enter day and reminder: 0
>
> 5 6:00 - Dinner with Marge and Russ
> 5 Saturday class
> 7 10:30 - Dental appointment
>12 Movie - "Dazed and Confused"
>12 Saturday class
>24 Susan's birthday
>26 Movie - "Chinatown"
>```

- 重構重點
	1. 因為 month_st\[]\[] 只有少數的 function 需要用到，所以更適合用 local variable，而不是 external variable
	2. 將格式化數字與合併剩餘的字放到另外一個 function 中，使 `main` 可以只負責控制整個程式

>[!success]- 重構後的 program
>```c
> // Prints a one-month reminder list
> 
> #include <stdio.h>
> #include <string.h>
> 
> #define MAX_WORD 50
> #define MAX_DAY 15
> 
> int read_and_format_line(char day_str[MAX_WORD], char msg_str[MAX_WORD], int n);
> void read_line(char msg_str[MAX_WORD], int n);
> void store_str(char month_str[MAX_DAY][MAX_WORD], char day_str[MAX_WORD],
>                char (*next_empty_row)[MAX_WORD]);
> void print_str(char month_str[MAX_DAY][MAX_WORD],
>                char (*next_empty_row)[MAX_WORD]);
> 
> int main(void) {
>   // 修正點：要存入一整個 row 的話，就必須要宣告一個
>   // 一維陣列的指標
>   int day;
>   char msg_str[MAX_WORD], day_str[MAX_WORD], month_str[MAX_DAY][MAX_WORD];
>   char (*next_empty_row)[MAX_WORD] = month_str;
> 
>   for (;;) {
>     // 判斷是否有位子繼續輸入
>     if (next_empty_row >= month_str + MAX_DAY) {
>       printf("---no space left---");
>       break;
>     }
> 
>     printf("Enter day and reminder: ");
>     if (!read_and_format_line(day_str, msg_str, MAX_WORD)) {
>       break;
>     }
> 
>     // 將 day_str 儲存進 month_str 之中
>     store_str(month_str, day_str, next_empty_row);
>     next_empty_row++;
>   }
> 
>   print_str(month_str, next_empty_row);
> 
>   return 0;
> }
> 
> int read_and_format_line(char day_str[MAX_WORD], char msg_str[MAX_WORD],
>                          int n) {
>   int day;
> 
>   // 讀取前面的數字並格式化
>   scanf("%2d", &day);
>   // 判斷是否為 0
>   if (!day) return 0;
>   // 讀取剩餘的字
>   read_line(msg_str, n);
>   // 黏合數字與文字並儲存在 day_str 之中
>   sprintf(day_str, "%2d %s", day, msg_str);
> 
>   return 1;
> }
> 
> void read_line(char msg_str[], int n) {
>   int ch;
>   char* p;
> 
>   // 清空前面的空白
>   while ((ch = getchar()) == ' ');
> 
>   // 輸入第一個字元
>   msg_str[0] = ch;
> 
>   // 輸入第二個以後的字元
>   for (p = msg_str + 1; (ch = getchar()) != '\n'; p++)
>     if (p < msg_str + n - 1)
>       *p = ch;
>     else
>       break;
>   *p = '\0';
> }
> 
> void store_str(char month_str[MAX_DAY][MAX_WORD], char day_str[MAX_WORD],
>                char (*next_empty_row)[MAX_WORD]) {
>   char (*row_position)[MAX_WORD] = month_str, (*move_row)[MAX_WORD];
> 
>   // 找出 day_str 所適合的位置
>   while (strcmp(day_str, *row_position) >= 0 && row_position < next_empty_row) {
>     row_position++;
>   }
> 
>   // 從最後的 reminder (也就是 row) 開始移動
>   // 空出空間給新的字串
>   for (move_row = next_empty_row; row_position <= move_row; move_row--) {
>     strcpy(*move_row, *(move_row - 1));
>   }
> 
>   // 新的字串放入正確的位子中
>   // 修正點：因為之前指派 row_position 為 str
>   // 所以當用上 * 的時候會變成 str (也就是陣列的位址)
>   strcpy(*row_position, day_str);
> }
> 
> void print_str(char month_str[MAX_DAY][MAX_WORD],
>                char (*next_empty_row)[MAX_WORD]) {
>   printf("\n");
>   for (char (*p)[MAX_WORD] = month_str; p <= next_empty_row; p++) {
>     printf("%s\n", *p);
>   }
> }
>```

>[!success]- output
>```
>Enter day and reminder: 24 Susan's birthday
>Enter day and reminder: 5 6:00 - Dinner with Marge and Russ
>Enter day and reminder: 26 Movie - "Chinatown"
>Enter day and reminder: 7 10:30 - Dental appointment
>Enter day and reminder: 12 Movie - "Dazed and Confused"
>Enter day and reminder: 5 Saturday class
>Enter day and reminder: 12 Saturday class
>Enter day and reminder: 0
>
> 5 6:00 - Dinner with Marge and Russ
> 5 Saturday class
> 7 10:30 - Dental appointment
>12 Movie - "Dazed and Confused"
>12 Saturday class
>24 Susan's birthday
>26 Movie - "Chinatown"
>
>```


###### 最終版：列印出一整個月的記事並一日期排序

- 新增的 statement
	- 增加了輸出的第一行標題

>[!success]- 最終的 program
>```c
> // Prints a one-month reminder list
> 
> #include <stdio.h>
> #include <string.h>
> 
> #define MAX_WORD 50
> #define MAX_DAY 15
> 
> int read_and_format_line(char day_str[MAX_WORD], char msg_str[MAX_WORD], int n);
> void read_line(char msg_str[MAX_WORD], int n);
> void store_str(char month_str[MAX_DAY][MAX_WORD], char day_str[MAX_WORD],
>                char (*next_empty_row)[MAX_WORD]);
> void print_str(char month_str[MAX_DAY][MAX_WORD],
>                char (*next_empty_row)[MAX_WORD]);
> 
> int main(void) {
>   // 修正點：要存入一整個 row 的話，就必須要宣告一個
>   // 一維陣列的指標
>   char msg_str[MAX_WORD], day_str[MAX_WORD], month_str[MAX_DAY][MAX_WORD];
>   char (*next_empty_row)[MAX_WORD] = month_str;
> 
>   for (;;) {
>     // 判斷是否有位子繼續輸入
>     if (next_empty_row >= month_str + MAX_DAY) {
>       printf("---no space left---");
>       break;
>     }
> 
>     printf("Enter day and reminder: ");
>     if (!read_and_format_line(day_str, msg_str, MAX_WORD)) {
>       break;
>     }
> 
>     // 將 day_str 儲存進 month_str 之中
>     store_str(month_str, day_str, next_empty_row);
>     next_empty_row++;
>   }
> 
>   print_str(month_str, next_empty_row);
> 
>   return 0;
> }
> 
> int read_and_format_line(char day_str[MAX_WORD], char msg_str[MAX_WORD],
>                          int n) {
>   int day;
> 
>   // 讀取前面的數字並格式化
>   scanf("%2d", &day);
>   // 判斷是否為 0
>   if (!day) return 0;
>   // 讀取剩餘的字
>   read_line(msg_str, n);
>   // 黏合數字與文字並儲存在 day_str 之中
>   sprintf(day_str, "%2d %s", day, msg_str);
> 
>   return 1;
> }
> 
> void read_line(char msg_str[], int n) {
>   int ch;
>   char* p;
> 
>   // 清空前面的空白
>   while ((ch = getchar()) == ' ');
> 
>   // 輸入第一個字元
>   msg_str[0] = ch;
> 
>   // 輸入第二個以後的字元
>   for (p = msg_str + 1; (ch = getchar()) != '\n'; p++)
>     if (p < msg_str + n - 1)
>       *p = ch;
>     else
>       break;
>   *p = '\0';
> }
> 
> void store_str(char month_str[MAX_DAY][MAX_WORD], char day_str[MAX_WORD],
>                char (*next_empty_row)[MAX_WORD]) {
>   char (*row_position)[MAX_WORD] = month_str, (*move_row)[MAX_WORD];
> 
>   // 找出 day_str 所適合的位置
>   while (strcmp(day_str, *row_position) >= 0 && row_position < next_empty_row) {
>     row_position++;
>   }
> 
>   // 從最後的 reminder (也就是 row) 開始移動
>   // 空出空間給新的字串
>   for (move_row = next_empty_row; row_position < move_row; move_row--) {
>     strcpy(*move_row, *(move_row - 1));
>   }
> 
>   // 新的字串放入正確的位子中
>   // 修正點：因為之前指派 row_position 為 str
>   // 所以當用上 * 的時候會變成 str (也就是陣列的位址)
>   strcpy(*row_position, day_str);
> }
> 
> void print_str(char month_str[MAX_DAY][MAX_WORD],
>                char (*next_empty_row)[MAX_WORD]) {
>   printf("\n");
>   printf("Day Reminder\n");
>   for (char (*p)[MAX_WORD] = month_str; p < next_empty_row; p++) {
>     printf(" %s\n", *p);
>   }
> }
>```

>[!success]- 最終的 output
>```
>Enter day and reminder: 24 Susan's birthday
>Enter day and reminder: 5 6:00 - Dinner with Marge and Russ
>Enter day and reminder: 26 Movie - "Chinatown"
>Enter day and reminder: 7 10:30 - Dental appointment
>Enter day and reminder: 12 Movie - "Dazed and Confused"
>Enter day and reminder: 5 Saturday class
>Enter day and reminder: 12 Saturday class
>Enter day and reminder: 0
>
>Day Reminder
>  5 6:00 - Dinner with Marge and Russ
>  5 Saturday class
>  7 10:30 - Dental appointment
> 12 Movie - "Dazed and Confused"
> 12 Saturday class
> 24 Susan's birthday
> 26 Movie - "Chinatown"
>```

<br><br>

### IV. String Idioms

#### 一，Searching for the End of a String

- 找尋字串的結尾<br>E.g:
	1. 最簡易的版本<br>重點：**字串的結尾一定是 null character**，所以可以用這個來**定位**
		```c
		size_t strlen(const char *s) 
		{
		  size_t n;
		  
		  for (n = 0; *s != '\0'; s++)
		    n++
		  return n;
		}
		```
	2. 濃縮版<br>重點：因為 '\\0' 的 ASCII 代號就是 **0 (false)**，所以可以直接用來判斷 (**其他的皆為非零**，也就是 ture)
		```c
		size_t strlen(const char *s)
		{
		  size_t n = 0;
		  
		  for (; *s; s++)
		    n++
		  return n;
		}
		```
	3. 再濃縮<br>重點：利用 **postfix 的 increment** 來化簡
		```c
		size_t strlen(const char *s)
		{
		  size_t n = 0;
		  
		  while (*s++)
		    n++
		  return n;
		}
		```
	4. 加快運作的版本<br>重點：利用指標直接**省略變數**
		```c
		size_t strlen(const char *s)
		{
		  const char *p = s;
		  
		  while (*s)
		     s++;
		  return s - p;
		}
		```
		- *注：因為在 `const char *s` 中 s 已經被變成了普通的指標，所以可以被移動*
- idiom:
	- 意思：找尋在字串中最後面的 null character
	1. 
		```c
		while (*s)
		  s++;
		```
	2. 
		```c
		while (*s++) ;
		```
<br>

#### 二，Copying a String

 - 複製字串：
1. 最初版的 program
	```c
	char *strcat(char *s1, const char *s2)
	{
	  char *p = s1;
	  
	  while (*p != '\0')
	    p++;
	  while (*s2 != '\0') {
	    *p = *s2;
	    p++;
	    s2++;
	  }
	  *p = '\0';
	  return s1;
	}
	```
	- 示意圖：
		1. 初始狀態<br>![](./Ch13_attachment/c-programming_a-modern-approach_ch13_5.png)
		2. 第一個 while loop 結束<br>![](./Ch13_attachment/c-programming_a-modern-approach_ch13_6.png)
		3. 第二個 while loop 的初始狀態<br>![](./Ch13_attachment/c-programming_a-modern-approach_ch13_7.png)
		4. 執行完第二個 while loop<br>![](./Ch13_attachment/c-programming_a-modern-approach_ch13_8.png)
		5. 最後再補上 '\\0'<br>![](./Ch13_attachment/c-programming_a-modern-approach_ch13_9.png)
1. 濃縮過後的 program
	```c
	char *strcat(char *s1, const char *s2)
	{
	  char *p = s1;
	  
	  while (*p)
	    p++;
	  while (*p++ = *s2++) ;
	  return s1;
	}
	```
- **Idiom**:<br>用途：**複製字串**
	```c
	while (*p++ = *s2++) ;
	```
	- 注意
		1. side effect 一定會發生在 \* 之後，但在進入 loop body 的之前
		2. 慢動作觀看：
			1. 先記住後綴的 increment (因為 \*p++ 等價於 \*(p++))
			2. 接著再 assignment
			3. 判斷是否為真
			4. 如果是 '\\0' (也就是 false) 的話，就停止迴圈
			5. 因為在前面就被記住需要執行 increment ，所以 increment 依然會發生，也就是說**結束後的 p 與 s2 會被指向 '\\0' 之後**
<br><br>

### IIV. Arrays of Strings

#### 一，Intro

- 過往用的陣列都會浪費空間，因為**多出來的空間會被 '\\0' 給填滿**，且每個 row 的長度都相同<br>E.g:
	```c
	char planets[][8] = {"Mercury", "Venus", "Earth",
	                     "Mars", "Jupiter", "Saturn", 
	                     "Uranus", "Neptune", "Pluto"};
	```
	示意圖：<br>![](./Ch13_attachment/c-programming_a-modern-approach_ch13_10.png)
- **`*a[NUM_COLS]` 與 `(*a)[NUM_COLS]` 的差異**
	- C 語言的讀法規則，由先到後為
		1. ()
		2. \[]
		3. \*
	- `(*a)[NUM_COLS]`：**指向陣列的指標**
		1. 先看到 ()，所以  (\*a) 是黏在一起的，因此為**一個指標**
		2. 接著再看到 \[] ，所以是**指向陣列**
	- `*a[NUM_cols]`：**指向指標的陣列**
		1. 先看到 \[]，所以 a 與 \[] 是黏在一起的，因此為**陣列**
		2. 接著才看到 \*，所以是儲存指標
- 用**指向指標的陣列**來儲存，就可以使每個 row 都儲存**不同的長度的字串**，也就是說這個陣列所**儲存的都是位置**<br>E.g:
	```c
	char *planets[] = {"Mercury", "Venus", "Earth",
	                   "Mars", "Jupiter", "Saturn",
	                   "Uranus", "Neptune", "pluto"};
	```
	示意圖：<br>![](./Ch13_attachment/c-programming_a-modern-approach_ch13_11.png)
	利用方式：雖然他是一維陣列，但**使用方式與二維陣列相同**<br>E.g:
	```c
	for (i = 0; i < 9; i++)
	  if (planets[i][0] == 'M')
	    printf("%s begins with M\N", planets[i]);
	```
<br><br>

#### 二，Command-Line Arguments (program parameters)

- 用途：**讀取指令列中的引數**<br>E.g: 在終端機中
	```
	ls -l remind.c
	```
	- 讀取 -l 這個引數
	- 雖然用途是來讀取引數，但其實**全部都會被讀到**
- 用法：在 `main` 中增加 `argc` 與 `argv[]`<br>E.g:
	```c
	int main(int argc, char *argv[])
	{
	  ...
	}
	```
	- `argc` (argument count): 命令列中的**引數數量**，包括**程式名字**
	- `argv` (argument vecter): 
		- 型別為**指標的陣列** (`char *argv[]`)
		- 用以**指向引數**
		- 因為是陣列，所以一樣是從 0 開始數
		- 最後一個指標為 **NULL pointer**，裡面存有 NULL，**標示陣列的結束** (也就是在 argv\[argc] 的位址)
	- E.g: 終端機中輸入
		```
		ls -l remind.c
		```
		- argc 為 3 (分別為 ls, -l, remind.c)，而 ls 就是 program name
		- argv 的示意圖：<br>![](./Ch13_attachment/c-programming_a-modern-approach_ch13_12.png)
- 取用 command-line arguments
	1. 用 interger variable 當作 index<br>E.g: 
		```c
		int i;
		
		for (i = 1; i < argc; i++)
		  printf("%s\n", argv[i]);
		```
	2. 運用多重指標<br>E.g:
		```c
		char **P;
		
		for (p = &argv[1]; *p != NULL; p++)
		  printf("%s\n", *p);
		```
		- \*\*p 為多重指標，用來**指向指標的位址**
		- 因為 argv 是指標的陣列，所以我們必須要在**指標的位址上跳轉**，因而只能用多重指標
		- 因為 \* 的意思就是**指向的東西的實際值**，所以 \*p 會變成是 argv\[] 的實際值，而 argv\[] 裡面所裝的實際值也就是字串的位址，因為 C 在處理中實際上都是**以字串的位址來代表字串本身**，所以  \*p 本身是字串
<br><br>

#### 三，範例二：Checking Planet Names

>[!success]- program
>```c
> // Checks planet names
> 
> #include <stdio.h>
> #include <string.h>
> 
> #define NUM_PLANETS 8
> 
> int main(int argc, char* argv[]) {
>   char* planet[] = {"Mercury", "Venus",  "Earth",  "Mars",
>                     "Jupiter", "Saturn", "Uranus", "Neptune"};
> 
>   int i, j;
> 
>   for (i = 1; i < argc; i++) {
>     for (j = 0; j < NUM_PLANETS; j++) {
>       if ((strcmp(argv[i], planet[j])) == 0) {
>         printf("%s is planet %d\n", argv[i], j + 1);
>         break;
>       }
>     }
>     if (j == NUM_PLANETS) {
>       printf("%s is not a planet\n", argv[i]);
>     }
>   }
> 
>   return 0;
> }
>```

>[!success]- output
>```
>Jupiter is planet 5
>venus is not a planet
>Earth is planet 3
>fred is not a planet
>```

<br><br>

---
## Exercise

### Section 13.3
#### **EX.1**

- 我的答案
	1. (b), 因為 %c 用於 character，而後面所接的 "\\n" 為 string
	2. (c), 因為 %s 用於 string，而後面所接的 '\\n' 為 character
	3. (e), printf 後面需要的是位址 (也就是字串的位址)，所以不能接 character
	4. (h), putchar 後面所需要的是 character，所以不能用 string
	5. (i), 因為 puts 後面所需的是 string，所以不能接 character
	6. **(j)**, 因為 puts 本身就會放置一個換行符在後面，所以會變成有兩個空行
<br>

#### **EX.2**

- 我的答案
	1. (a): `putchar` 是用來列印 character 的，不能用來列印字串
	2. **(b)**: 因為 `putchar` 是用來列印 character，且 p 實際上紀錄的是 'a' 的位址，所以代表 \*p 就是 character，因此是對的<br>output:
		```
		a
		```
	3. (c): 標準列印字串的方式<br>output:
		```
		abc
		```
	4. (d): 因為字串被視為是位址，所以 puts 後面必須放置字串位址，也就是 p 而不是 \*p
<br>

#### EX.3

- 我的答案:<br>i 為 12，而 s 為 abc34，j 則是 56，剩下的 def78 會被放到 buffer 中
- reason:<br>因為 scanf(%s) 遇到空白，換行與 tab 皆會停止輸入，而 j 又只能輸入數字，所以剩下的 def78 就無法被讀取了
<br>

#### EX.4

- 原本的 read_line function
	```c
	int read_line(char str[], int n)
	{
	  int ch, i = 0;
	  
	  while ((ch = getchar()) != '\n')
	    if (i < n)
	      str[i++] = ch;
	  str[i] = '\0';
	  // terminates string
	  return i;
	  // number of characters stored
	}
	```
1. (a)
	```c
	int read_line(char str[], int n)
	{
	  int ch, i = 0;
	  
	  while(isspace(ch = getchar()))
	    ;
	  
	  // 輸入第一個字
	  // 判斷是否為 EOF (檔案結尾)
	  if (ch != EOF && i < n)
	    str[i++] = ch;
	  
	  while ((ch = getchar()) != '\n' && ch != EOF)
	    if (i < n)
	      str[i++] = ch;
	  str[i] = '\0';
	  // terminates string
	  return i;
	  // number of characters stored
	}
	```
2. (b)
	```c
	int read_line(char str[], int n)
	{
	  int ch, i = 0;
	  
	  while (!isspace(ch = getchar()) && ch != EOF)
	    if (i < n)
	      str[i++] = ch;
	  str[i] = '\0';
	  // terminates string
	  return i;
	  // number of characters stored
	}
	```
3. (c)
	```c
	int read_line(char str[], int n)
	{
	  int ch, i = 0;
	  
	  while ((ch = getchar()) != '\n' && ch != EOF)
	    if (i < n)
	      str[i++] = ch;
	      
	  // 將換行符儲存進 str 之中
	  if (i < n)
	    str[i++] = '\n';
	    
	  str[i] = '\0';
	  // terminates string
	  return i;
	  // number of characters stored
	}
	```
4. (d)
	```c
	int read_line(char str[], int n)
	{
	  int ch, i = 0;
	  
	  while ((ch = getchar()) != '\n' && ch != EOF)
	    if (i < n)
	      str[i++] = ch;
	    else
	      break;
	
	  str[i] = '\0';
	  // terminates string
	  return i;
	  // number of characters stored
	}
	```
<br>

### Section 13.4

#### EX.5

1. (a)
	```c
	void capitalize(char str[])
	{
	  for (int i = 0; str[i]; i++)
	    str[i] = toupper(str[i]);
	}
	```
2. (b)
	```c
	void capitalize(char *str)
	{
	  while (*str) {
	    *str = toupper(*str);
	    str++;
	  }
	}
	```
<Br>

#### EX.6

- 我的答案
	```c
	void censor(char *str)
	{
	  int consec_ch = 0;
	  char *initial_ch;
	  
	  while (*str) {
	    // 判斷是否有可能是 foo
	    if (consec_ch == 0 && *str == 'f') {
	      consec_ch++;
	      initial_ch = str;
	    } else if ((conse_ch == 1 || conse_ch == 2) && *str == 'o') {
	      consec_ch++;
	    } else
	      consec_ch = 0;
	      
	    // 將 foo 替換成 xxx
	    if (consec_ch == 3) {
	      initial_ch[0] = 'x';
	      initial_ch[1] = 'x';
	      initial_ch[2] = 'x';
	    }
	    
	    str++;
	  }
	}
	```
- 問題點：
	- 如果是 fofoo 因為第二個 f 被判定說不連續，所以不會被檢查到
	- 最簡單的寫法是看到 f 後直接檢查後兩個字否為 oo
- 修正後的答案：
	```c
	void censot(char *str)
	{
	  while (*str) {
	    if (str[0] == 'f' && str[1] == 'o' && str1[2] == 'o') {
	      str[0] = 'x';
	      str[1] = 'x';
	      str[2] = 'x';
	      str += 3;
	      // 因為如果前面的檢查都通過了，就代表後面三個字元確實都存在
	    } 
	    str++;
	  }
	}
	```

### Section 13.5

#### EX.7

- 我的答案：
	- (d) 因為 strcat 會將 "" (空字串) 放進 str 中的最後面，其他的都是直接放置進最前面
	- *注: (a) 正確，因為 null character 的 ASCII 代號本來就是 0*
<br>

#### EX.8

- 我的答案：
	1. 執行 `strcpy(str, "tire-bouchon")` 後的 str 為
		```
		tire-bouchon
		```
	2. 執行 `strcpy(&str[4], "d-or-wi")` 後
		```
		tired-or-wi
		```
	3. 執行 `strcat(str, "red?")` 後
		```
		tired-or-wired?
		```
	- *注： 在第二步時， n 會被 "d-or-wi" 的 null character 所影響到，進而直接結束字串*
<br>

#### EX.9

- 我的答案
	```
	computer
	```
	```
	computers
	```
- Reason
	1. 因為 s1 中的第一個字母為 c ，s2 則是 s，所以 computer < science，因此會執行
		```c
		strcat(s1, s2)
		```
		將 s1 變成 computerscience
	2. strlen(s1) 為 15 ，所以 s1\[strlen(s1)-6] = '\\0' 會將computerscience 中第二個 c 變為 null character，所以結果就會變成 computers
<br>

#### **EX.10**

- 我的答案
	- 因為 p 並未被初始化，所以它不知道會被指向哪裡
<br>

#### EX.11

- 原本的 function
	```c
	int strcmp(char *s, char *t)
	{
	  int i;
	  
	  for (i = 0; s[i] == t[i]; i++)
	    if (s[i] == '\0')
	      return 0;
	  return s[i] - t[i];
	}
	```
- 用指標算術改寫
	```c
	int strcmp(char *s, char *t)
	{
	  while (*s == *t) {
	    if (*s == '\0')
	      return 0;
	    s++;
	    t++;
	  }
	  return *s - *t;
	}
	```
<Br>

#### EX.12

- 我的答案 
	```c
	void get_extension(const char *file_name, char *extension)
	{
	  const char *p;
	  int file_name_len = strlen(file_name);
	  
	  // 找出最後一個 . 的位址
	  for (p = file_name; *p != '\0'; p++)
	    if (*p == '.')
	      file_name = p + 1;
	      
	  // 將副檔名複製進 extension
	  if (strlen(file_name) == file_name_len)
	    *extension = '\0';
	  else 
	    strcpy(extension, file_name);
	}
	```
<br>

#### EX.13

- 我的答案：
```c
void build_index_url(const char *domain, char *index_url)
{
  char title_url[50];
  
  strcpy(title_url, "http://www.");
  strcat(title_url, domain);
  strcpy(index_url, title_url);
  strcat(index_url, "/index.html");
}
```
- 更簡潔的寫法：直接將字串放進 index_url 中
	```c
	void build_index_url(const char *domain, char *index_url)
	{
	  strcpy(index_url, "http://www.");
	  strcat(index_url, domain);
	  strcat(index_url, "/index.html");
	}
	```
<br>

### Section 13.6

#### **EX.14**

- 因為 --\*p 等價於 --(\*p) ，所以它會將全部的字母依照 ASCII 碼向前推一格，所以 output 為
	```
	Grinch
	```
<br>

#### EX.15

- 我的答案：
	1. (a): 3
	2. (b): 0
	3. (C): 回傳 s 字串中第一個不在 t 字串的字元索引值 (index)
<br>

#### EX.16

- 我的答案：
	```c
	int count_space(const char *s)
	{
	  int count = 0;
	  
	  while (*s) {
	    if (*s == ' ')
	      count++;
	    s++;
	  }
	  return count;
	}
	```
<Br>

#### **EX.17**

- 我的答案
```c
bool test_extension(const char *file_name,
                    const char *extension)
{
  const char *file_extension;

  // 將 file_extension 指向 file_name 中的副檔名
  for (; *file_name; file_name++) 
    if (*file_name == '.')
      file_extension = file_name + 1;
      
  for (;*file_extension && *extension; file_extension++, extension++) {
    if (!(toupper(*file_extension) == toupper(*extension)))
      return false;
  }
  return true;
}
```
- 錯誤點：
	1. 因為 file_name 不一定會有副檔名，如果沒有的時候就會讀到錯誤的位址
	2. 可以直接從最後一個位置來倒著找尋 .
- 修正後的答案：
	```c
	bool test_extension(const char *file_name,
	                    const char *extension)
	{
	  const char *p = file_name;
	  
	  // 將 p 設置到 file_name 的結尾
	  while (*p)
	    p++;
	
	  // 找尋 .    
	  for (; p >= file_name; p--)
	    if (*p == '.') {
	      // 因為要定位到 . 後面的字，
	      // 所以要 + 1
	      p++;
	      break;
	    }
	
	  // 沒有 . 就直接回傳 false
	  // 開頭的點代表的是隱藏檔，所以不算副檔名
	  if (p == file_name)
	    return false;
	    
	  // 判斷副檔名是否相同
	  while (toupper(*p) == toupper(*extension)) {
	    if (*p == '\0')
	      return true;
	    else {
	      p++;
	      extension++;
	    }
	  }
	  return false;
	}
	```
<br>

#### EX.18

- 我的答案：
```c
void remove_filename(char *url)
{
  char *p = url;
  
  // 將 p 移到 url 的最底部 
  while (*p)
    p++;
    
  // 將 p 移到最後一個 / 上
  while (p >= url && *p != '/')
    p--;
  *p = '\0';
}
```

## Programming Project

### Proj.4：將命令列引數倒著列印

>[!success]- program
>```c
>//// This is my program for programming project 4
>// in C Programming: a modern approach
>// This program is used to echoes its command-line arguments
>// in reverse
>
>#include <stdio.h>
>
>int main(int argc, char *argv[]) {
>    for (char **p = &argv[argc - 1]; p > &argv[0]; p--)
>      printf("%s ", *p);
>    printf("\n");
>}
>```

>[!success]- output
>```
>$ ./reverse aaaaaaaaaaaa and rrrrrrrrr
>rrrrrrrrr and aaaaaaaaaaaa 
>```

<br>

### Proj.5：將命令列引數轉為數值並加總

- 學習重點：
	- 要用指標的話必須要用多重指標才可以指向指標的位址，並且跳向下一個 argument vecter

>[!success]- program
>```c
> // This is my program for programming project 5
> // in C Programming: a modern approach
> // This program is uesed to add up its command-line arguments
> 
> #include <stdio.h>
> #include <stdlib.h>
> 
> int main(int argc, char* argv[]) { 
>     int sum; 
> 
>     for (char **p = &argv[1]; *p != NULL; p++) {
>         sum += atoi(*p);
>     }
> 
>     printf("Total: %d\n", sum);
> 
>     return 0;
> }
>```

>[!success]- output
>```
>$ ./programming-project_Ch13_5 8 24 62 12 456 879  55 5 55 5 55 5 5 2 2 2 22 4 4 4 48 9  4
>Total: 1727
>```

<br>

### Proj.18：將數字的月份轉為月份名

>[!success]- program
>```c
> // This my program for programming project 18
> // in C Programming: a modern approach
> // This program is uesed to acceopt a date form
> // the user in the form mm/dd/yyy and then displays
> // it in the form month dd, yyy
> 
> #include <stdio.h>
> 
> void enter_and_read_date(int* num_month, int* day, int* year);
> const char* trans_num_to_name_month(int num_month);
> void print_outcome(const char name_month[], int day, int year);
> 
> int main(void) {
>   int num_month, day, year;
>   const char *name_month;
> 
>   enter_and_read_date(&num_month, &day, &year);
>   name_month = trans_num_to_name_month(num_month);
> 
>   print_outcome(name_month, day, year);
> }
> 
> void enter_and_read_date(int* num_month, int* day, int* year) {
>   printf("Enter a date (mm/dd/yyyy): ");
>   scanf("%d /%d /%d", num_month, day, year);
> }
> 
> const char* trans_num_to_name_month(int num_month) {
>   const char* name_month_code[12] = {"January",
>                                      "February",
>                                      "March",
>                                      "April",
>                                      "May",
>                                      "June",
>                                      "July",
>                                      "August",
>                                      "September",
>                                      "October",
>                                      "November",
>                                      "December"};
> 
>   return name_month_code[num_month - 1];
> }
> 
> void print_outcome(const char name_month[], int day, int year) {
>   printf("You entered the date %s %d, %d\n", name_month, day, year);
> }
>```

>[!success]- output
>```
>$ ./programming-project_Ch13_18 
>Enter a date (mm/dd/yyyy): 2/17/2011
>You entered the date February 17, 2011
>```