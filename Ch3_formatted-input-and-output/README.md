#  C program: a modern approach Ch.2 note 
<br>

## I. printf

- 用途：展示 format stings
- fomat stings 中又包含了 ordinary characters 與 **conversion specification** 

#### 1. ordinary characters

- 也就是一般的字元，會直接顯示出你打的字
- E.g
	```
	指令:
	
	int i, j;
	float x, y;
	
	i = 10;
	j = 20;
	x = 43.2892f;
	y = 5527.0f;
	
	printf("i = %d, j = %d, x = %f, y = %f/n",
	    i, j, x, y)
	
	
	outcome:
	i= 10, j = 20, x = 43.289200, y = 5527.000000
	
	其中的i =, j = 等直接顯示出他的字元的就是 ordinary characters
	
	%d, %f 就是 conversion specifications
	```

#### 2. Conversion specifications

- 以 % 開頭，用於顯示後面 variable 的 value
- 格式： `%m.pX` 或 `%-m.pX`
	1. `m` 與 `p` 都是可選擇要或不要的值，如果沒有給`m` 或 `p` 的話，就都用預設值
	2. 前面的 - 代表靠左（也就是空格放在右側），沒有 - 就是靠右（空格放在左側）
	3. m 為 minimum field width。 規定最少要 print 幾個 characters，若要顯示的字元少於 m，則用空格補齊
	4. p 為 precision。會因為 X 的而改變他的作用
	5. X 為 conversion specifier。用於指稱 variable 的 value 的種類。<br>X 的種類：
		1. `d`：用於展示十進位制的 integer。p 在此則是代表最少要顯示的數字，若輸出的數字小於 p 則會將 0 放在數字前面去補齊到 p 個數字，預設是 1 （也就是不會補 0）。
		2. `e`：用於將 floating-point 以 exponential format 輸出。p 在此則代表要顯示到小數第 p 位，**是以 e 前面的小數為位數作為標準來看第幾位**。p 的預設值為 6，若 p 為 0 則沒有小數。
		3. `f`：用於將 floating-point 以 fixed decimal format 的形式(也就是用一般小數的形式) 顯示出來。p 也一樣是代表要顯示到小數第 p 位。
		4. `g`：用於將 floating-point 以 fixed decimal format 或 exponential format 的形式顯示出來。它會看 fixed decimal format 和 exponential format 哪個數字較少，就顯示哪一個。p 代表顯示出來的**最大有效數字**

###### 範例 1: Using printf to Format Numbers

1. program:
   ```tprintf.c
   /* Prints int and float values in various formats */

   #include <stdio.h>

   int main(void)
   {
	    int i = 40;
	    float x = 839.21f;
		
	    printf("|%d|%5d|%-5d|%5.3d|\n", i, i, i, i, i);
	    printf("|%10.3f|%10.3e|%-10g|\n", x, x, x, x);
		
	    return 0;
	}
   ```
<br>

2. output:
   ```
     |40|   40|40   |  040|
     |   839.210| 8.392e+02|839.21    |
     ```

#### 3. Escape Sequence

1. `\` 用於顯示特殊的字元。因為有些字對於 compiler 有特別得意義，所以得用 escape sequence 才可以顯示出來 (例如 \" 和 \* 與 \\)，將想顯示的字元放在 \\ 後方就可顯示出來<br>E.g：
	```
	1.
	printf ("\"Hello!\"");
	會顯示出
	"Hello!"
	
	2.
	printf("\\");
	會顯示出
	\
	```
2. 因為在 program 內用空格多數時候是沒有意義的，所以要換行或按 tab 進行縮排的時候就得用 escape sequence，用途與打法現在較常用的有以下 4 種

	| Alert (bell)   | \a  |
	| -------------- | --- |
	| Backspace      | \b  |
	| New line       | \n  |
	| Horizontal tab | \t  |

	- E.g: 
	```
	printf("Item\tUnit\tPurchase\n\tPrice\tDate\n") ;
	會顯示出
	Ttem    Unit    Purchase
	        Price   Date
	```
<br><br>

---
## II. scanf
<br>

#### 1. scanf 的運作方式

1. scanf 其實就是 pattern-matching function ，它會嘗試將 input characters 與 conversion specifications 結合
2. 讀取步驟
	1. 從左至右將 input data 轉換成合適的 type，在過程中如果必要的話會跳過 blank space
	2. 讀取剛剛執行的結果。如果遇到可能不屬於這個的 variable 的 characters 時就停下來（例如他是 %d ，然後在 input data 內的這個字元為 .）
	3. 讀取成功
		- 儲存進 variable 內，並且讀取下一個 characters
	4. 讀取不成功
		- 不繼續看下一個 characters，進到下一個指令

#### 2. 讀取 conversion specification
1. 在找尋數字的開頭時會忽略 white-space characters<br>E.g:
	```
	scanf ("%d%d%f%f", &i, &j, &X, &Y);
	
	如果使用者輸入了
	
	  1
	-20   .3
	   -4.0e3
	
	scanf 將會看他們為
	ww1n-20www.3nwww-4.0e3n
	*注：w 代表 white space ，n 代表 newline
	
	以下的 s 代表 skip ，r 代表它作為 input item 的一部分被讀取
	ww1n-20www.3nwww-4.0e3n
	ssrsrrrsssrrssssrrrrrss
	``` 
2.  scanf 只會窺視 new-line character 而不會讀取它，它會在下一個 scanf 的時候才會讀取它，所以如果你放了 `\n` ，就會造成下一次的讀取錯誤
3. scanf 判斷 integer 與 floating-point 的標準
	1. 在後方的 + 與 -
	2. 一連串的數字 (可能為 integer)
	3. exponent (e)，那就代表為 floating-point
4. 當 scanf 遇到不屬於這個 format strings 的符號時，這個 character 將會被 put back 到下一個 conversion specification 去<br>E.g:
	```
	scanf("%d%d%f%f", &i, &j, &x, &y)
	
	input data: 1-20.3-4.0e3n
	*n 為 new-line character
	```
	1. Conversion specification: %d。因為 1 可為 integer 的開頭而 - 不行，所以 - 被 "put back" 到下一個 conversion specification
	2. Conversion specification: %d。因為 -, 2, 0 可組合成 integer 而 . 不行，所以 . 被 "put back" 到下一個 Conversion specification
	3. Conversion specification: %f。 scanf 讀取 ., 3。然後將 - put back
	4. Conversion specification: %f。scanf 讀取 -4.0e3

<br>

#### 3. 在 format strings 中讀取 ordinary characters

1. White-space characters
	- 讀取時如果在 format strings 上遇到空格 (也就是在`" "`內中遇到空格)，則反覆讀取 input 的 white-space 直到不是 white-space，也就是說 **white-space 不管有多少，都與一個一樣**。如果 **input 內沒有 white-space 也一樣會讀取成功**。但在 **format strings 內沒有 white-space 的情況下，input 若有 white-space 就會讀取失敗**
2. other characters
	- 遇到非空白的字元時， `scanf` 會比較 input 與 format strings 有沒有一樣，若一樣就配對進去，若不一樣則放棄讀取在此字元之後的所有字元。

#### 範例 2: adding fractions

1. program:
   ```addfrac.c
	// Add two fractions
	
	#include <stdio.h>
	
	int main(void)
	{
	    int num1, denom1, num2, denom2, result_num, result_denom;
		
	    printf("Enter first fraction: ");
	    scanf("%d /%d", &num1, &denom1);
		
	    printf("Enter second fraction: ");
	    scanf("%d /%d", &num2, &denom2);
		
	    result_num = num1 * denom2 + denom1 * num2;
	    result_denom = denom1 * denom2;
		
	    printf("The sum is %d/%d\n", result_num, result_denom);
		
	    return 0;
	}
	```

2.output: 
   ```
   Enter first fraction: 4/3
   Enter second fraction: 8/9
   The sum is 60/27
   ```