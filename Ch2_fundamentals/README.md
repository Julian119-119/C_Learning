# C program: a modern approach Ch.2 note
<br>

## I. 執行 c
一，寫出 C 的 program
* 名稱不拘，但句尾一定要是 `.c`
* 可用 nano，vim 亦或者是 VS Coding 寫

二，Conversion
* 將 program 轉換為電腦可讀懂的狀態，包含以下三步
	1. Preprocessing:
		* 執行 # 的部份（也就是 directives）
	2. Compiling:
		* 由 compiler 將指令轉換成 object code (機器可讀懂的語言)
	3. Linking;
		* 由 liker 將一個或多個 object code 與函數庫連結，這樣才有辦法執行

- 執行指令
	```
	gcc program.c

	也可以加上參數 o 命名編譯好的檔案
	gcc -o name program.c
	```

三，執行轉換出來的檔案
<br><br>

---
## II. C Program 的形式

- 一般形式
	```
	documentation
 
	directive
 
	int main(void)
	{
	   statement
	}    
	```

1. directivs

	- 在 preprocessing 時就被執行的部份，**由 `#` 開頭**。
	- `#include <stdio.h>`：用於將讀跟寫的指令叫出來
2. Functions

	- 基本上就是一連串的 statement 所組合而成，且也有不同種的 function ，但只有 main function 是必要的
	- main function: `int main` 的 int 是用於指出 main 要回傳一個整數值（integer）也就是後方的 return 0; 所回傳的 0。而 `main(void)` 的 void 則是表示沒有用 argument (引數)
3. statements
	- 當 program 在跑時所執行的指令
4. documentation
	- 用於辨認這個 program 的資訊（例如作者，用途等）
	- 可用`/*   ~~~   */` (**兩邊都一定要有，且可跨行用**)也可用<br>`//   ~~~`(單行)
	- E.g:
		```
		/* Name: pun.c
		Purpose: Prints a bad pun.
		Author: K.N. King */ 
		```
		<br>或<br>
		```
		// Name: pun.c
		// Purpose: Prints a bad pun.
		// Buthor: Κ. N. King
		```

<br><br>

---
## III. Variable and Assignment

1. Type
	- 可分為 integer (整數) 與 float (floating point 的縮寫，也就是我們所熟知的小數)
	- **如果遇到小數與整數，就全部換成小數** (例如換成 52.00f 之類的)，避免錯誤
2. declaration (宣告)
	- 用於定義該 variable 為 integer 還是 floating point
	- 在第一次用某一個 variable 時一定要先宣告他是 integer 還是 floating point 
	- 指令:
		```
		int variable_1, variable_2, variable_3;
		float variable_4;
		```
	- 位置:
		```
		int main(void)
		{
		    declarations
		    statements
		}
		```
3. assignment
	- 在 declaration 後，用指定 variable 的值或算式
	- 可為 constant 或 floating point 也可是 expression (前面都要先宣告)
	- **若為 floating poin， 數字後一定要加 f (例如 5.23f)**，因為如果沒加，預設會使用 double (雙精度)，加了就會用 float (單精度)
	- E.g:
		```
		float height, length, width,  volume;
		
		height = 8.00f;
		length = 6.87f;
		width = 3.00f;
		volume = height * length * width
		```

<br><br>

---
## IV. printf 指令

1. 用途: 顯示字串
2. `\n` 為換行符
3. 除了顯示出 `" "` 內的字以外，也可指定它顯示出 variable
	- %d 用於顯示 integer 的 variable
	- %f 用於顯示 floating point 的 variable (%.mf 則是限制他要顯示小數點後 m 位)
	- 反正 %d 與 %f 就是一個 placehold，留給後方指定的 variable
4. 也可指定它顯示某一個 expression 
5. E.g
	```
	printf("Height: %d\n", height); 
	/* 顯示 hight 這個 variable 的值 */

	printf("Height: %d\n, Length: %.2f\n", height, length); 
	/* 顯示兩個 variable */

	printf("Volume: %d\n", height * length * width); 
	/*  顯示 expression 計算出來的值 */

	```

<br><br>

---
## V. Initialization

1. 意思： 在宣告的同時給與它 assignment
2. uninitialization 的後果： 會造成它給一個垃圾值
3. 每一個 variable 都要有一個等號，不可共用
4. E.g
	```
	int height = 8; 
	/* 8被稱為 initializer */
	
	int height = 8, length = 12;
	
	*等號不可共用，所以下面只有 width 是 initialization
	int height, length, width = 10;
	
	```

<br><br>

---
## VI. scanf 指令

1. 用於將 input 儲存於指定的 variable 中
2. **在 variable 前一定要有 `&`**
3. 指令：
	```
	scanf("%d, &i")
	/* reads an integer; stores into i */
	
	scanf("%f", &x);
	/* reads a float value; stores into x */
	```

<br><br>

---
## VII. Defining names for constants

1. `#define` 為 preprocessing directive
2. 用於將常用的 integer 與 float 或 expression 用一個名稱代表，讓該 program 更易讀
3. 指令:
	```
	#define 自訂的variable 要帶換的數值或expression
	```

<br><br>

---
## VIII. Identifiers

1. 定義: variable, function, macros, ...的名字
2. **有區分大小寫**
3. 只能有**英文字母，下底線與數字**，且**不能用數字開頭**
4. 以下的 keyword 因為對 compilers 有特殊意義，所以不能當作  identifiers

	|   auto   |   enum   | restrict |  unsigned  |
	| :------: | :------: | :------: | :--------: |
	|  break   |  extern  |  return  |    void    |
	|   case   |  float   |  short   |  volatile  |
	|   char   |   for    |  signed  |   while    |
	|  const   |   goto   |  sizeof  |    Bool    |
	| continue |    if    |  static  |  _Complex  |
	| default  |  inline  |  struct  | _Imaginary |
	|    do    |   int    |  switch  |            |
	|  double  |   long   | typedef  |            |
	|   else   | register |  union   |            |

<br><br>

---
## IX. Layout of C Program

- 可以將 C 想成一連串的 token ，而 token 就是不可在不改變其意之下再被分割成更小單位的，的一連串 characters 
-  E.g:
	```
	printf ("Height: d\n", height);
	
	他有 7 個 token
	
	printf ( "Height: %d\n" ) height )   ;
	  1    2       3        4    5   6   7
	  
	  Tokens 1 和 5 是 identifiers, token 3 是一個 string literal, 然後 tokens 2, 4, 6, 和 7 是 punctuation.
	```
- 排版:
	1. statement 可被分成數行，如果太長的時候可以分行讓它更易讀<br>E.g:
		```
		printf ("Dimensional weight (pounds): %d\n",
			(volume + INCHES_PER_POUND - 1) / INCHES PER POUND);
		```
	2. 在每一個 token中間放一個 space會更容易讓眼睛去分辨他們<br>E.g:
		```
		volume = height * length * width;
		```
	3. Indentation 可以讓它更好讀
	4. 用 blank lines 將每個logical units分開來會使得 program 的架構更容易被看懂
