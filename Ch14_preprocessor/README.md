# Note

## I. How the Preprocessor Works

- 前置處理器 (preprocessor) 的行為是依據 **preprocessing directives** 來做的
- 目前已使用過的 preprocessing directives
	1. `#define`： 創造一個 **macro** 來代表一個 expression
	2. `#include`： 告訴 preprocessor 說要包含到哪些檔案 (這也代表裡面的內容物都會被包含進來)<Br>E.g:
		```c
		#include <stdio.h>
		```
		包含 stdio.h 這個檔案
- preprocessor 在編譯當中的角色
	- 編譯流程示意圖：<br>![[c-programming_a-modern-approach_ch14_1.png]]
	- 解釋：
		1. preprocessor 會先處理 input 的 program，將裡面的 directive 都先處理掉，有的時候也會處理掉多餘的空白鍵
		2. 接著輸出成另一個沒有dierective 的 c progarm
		3. 將這個 c progarm 交給後續的編譯器處理
<br><Br>

## II. Preprocessing Directives

- preprocessing directive 的分類：
	1. macro definition: 
		- `#define` 定義 macro。
		- `#undef` 用來移除 macro 的定義
	2. file inclusion: 
		- `#include` 用來包含特殊檔案
	3. conditional compilaton:
		- `#if`, `#ifdef`, `#ifndef`, `#elif`, `else`, `#endif`： 用來測試條件
	4. 其他： `#error`, `#line`, `#pragma` 等特殊的 preprocessing directive
- preprocessing directive 使用規則：
	1. 必定**以 \# 開頭**
	2. 可以用**任何數量**的空白鍵或 tab 來隔開<br>E.g:
		```c
		#   define   N   100
		```
	3. 一定在**第一個換行就結束**，如果想分行就要用 \\<br>E.g:
		```c
		#define DISK_CAPACITY (STDES *              \
		                       TRACKS_PER_SIDE *    \
		                       SECTORS_PER_TRACK *  \
		                       BYTES_PER_SECTOR)
		```
	4. 可以出現在 **program 的任何地方**
	5. comments 建議加在 directive 的同一行，讓其他知道這行的功用<br>E.g:
		```c
		#define FREEZING_PT 32.f /* freezing point of water */
		```
<br><br>

## III. Macro Definitions

#### 一，Simple Macros

- 到目前為止所用的 macro 都是 **simple macro** (或稱為 **object-like macro**)
- 特徵就是**沒有參數**<br>E.g:
	```c
	#define identifier replacement-list
	```
- replacement-list: 
	- 由一連串的 **preprocessing tokens** 所組成，而 preprocessing tokens 與在 Ch2 中討論過的 token 很像，以下都會以 token 代指 preprocessing token
	- 有可能包含： identifiers, keywords, numeric constants, character constants, string literals, operators, and punctuation，也可為**空的**
	- *注：在 replacement-list 不要加分號，否則分號會被算成是 replacement-list 的一部分，導致程式出錯*
- E.g:
	```c
	#define STR_LEN 80
	#define TRUE 1
	#define PI 3.14159
	#define CR '\r'
	#define MEM_ERR "Error: not enough memory"
	```
- 優點：
	1. 使 program 更易讀
	2. 使 program 更容易修改
	3. 避免**數值打錯與版面不同**。例如一下子打 3.14 一下子打 3.1415
- 其他用法：
	1. 更改 C 的語法結構<BR>E.g:
		1. 將 { 換成 begin ， } 換成 end
			```c
			#define BEGIN {
			#define END }
			```
		2. 將 LOOP 代指為無限迴圈
			```c
			#define LOOP for(;;)
			```
		- *注：這樣會讓 program 變得不容易理解*
	2. 重新命名型別 (在 Ch5 時就有用過)<br>E.g:
		```c
		#define BOO`L int
		```
		- *注：也可以用 Type definitions 
	3. 控制 conditional compilation<br>E.g:
		```c
		#define DEBUG
		```

#### 二，Parameterized Macros

- form:
	```c
	#define identifier( x1, x2, ..., xn) replacement-list
	```
	- identifier 與 ( 之間**不能有空格**，否則會被判斷成 simple macro
- 當 preprocessor 遇到 parameter 的時候，會將它暫時儲存下來，接著帶入進 replacement-list<br>E.g:
	1. macros:
		```c
		#define MAX(x,y) ((x) > (y) ? (x) : (y))
		#define IS_EVEN(n) ((n) % 2 == 0)
		```
		- 注：每一個變數建議**都要括起來**，反則如果之後輸入的參數是 expression，就會導致錯誤
	2. program:
		```c
		i = MAX(j+k, m-n);
		if (IS_EVEN(i) i++;
		```
	3. 前置處理器會將它變成
		```c
		i = ((j+k) > (m-n) ? (x) : (y));
		if ((i) % 2 == 0) i++;
		```
- replacement-list 也可以是空的<br>E.g:
	```c
	#define getchar() getc(stdin)
	```
- 用 macro **取代 function**
	- 優點
		1. program 會跑得稍微快一點：因為少了需要傳遞的引數，macro 只是單純的代換，所以會跑得比較快一點
		2. macro 的參數限制較少，因為只是代換過去而已
	- 缺點：
		1. compiled code 可能會變很長，因為不能分段做
		2. 不會檢查引數的型別
		3. 沒有辦法用指標指向型別 (在 ch17 會看到用指標指向 function)
		4. macro 可能會計算他的引數多於一次<br>E.g:
			1. macro:
				```c
				n = MAX(i++, j);
				```
			2. 編譯後會變成
				```c
				n = ((i++) > (j) ? (i++) : (j))
				```
				- 注：所以建議**不要在 macro 用 side effect**
- 用法：除了可以模仿 function，也可以作為**一部分的 code ，來省去一部分的 statement**<br>E.g:
	- 假設要寫
		```c
		printf("%d\n", i)
		```
	- macro:
		```c
		#define PRINT_INT(n) printf("%d\n", n)
		```
	- preprocessor:<br>將
		```c
		PRINT_INT(i/j);
		```
		轉成
		```c
		printf("%d\n", i/j);
		```
<br>

#### 三，The \# Operator

- \# operator **只能夠被用在 replacement-list** 中
- 用途：將**引數轉換為 string literal**<br>E.g:
	- macro:
		```c
		#define PRINT_INT(n) printf(#n " = %d\n", n)
		```
	- program:
		```c
		PRINT_INT(i/j);
		```
		preprocessor 會將它轉譯成
		```c
		printf("i/j" " = %d\n", n);
		```
		在 Ch13 中說過這個就等價於
		```c
		printf("i/j = %d\n", n)
		```
<br>

#### 四，The \#\# Operator

- 與 \# 相同，只能用在 replacement-list
- 用途：將**兩個 token 合併成一個 token**<br>E.g:
	- macro:
		```c
		#define MK_ID(n) i##n
		```
	- 如果使用 `MK_ID(1)` 前置處理器會先將 1 帶入 n ，接著再將 i 與 1 黏在一起變成
		```c
		i1
		```
		將其用在宣告就會變成
		```c
		int MK_ID(1), MK_ID(2), MK_ID(3);
		```
		經前置處理器處理過後變成
		```c
		int i1, i2, i3;
		```
- 也可以用於建造一個對**型別泛用的 function**<br>E.g:
	```c
	#define DENERIC_MAX(type)        \
	type type##_max(type x, type y)  \
	{                                \
	  return x > y ? x : y;          \
	}                                \
	```
	- 注：這個 macro 的 **replacement-list 為一個 function**
	- 用上去就會**創造出對應的 function**
	- 也因為用上去就會創造出對應的 function，所以要在 **global 區域使用**<br>E.g: 實際使用
		1. 原本的 program
			```c
			#include <stdio.h>
			
			// 1. 定義 Macro
			#define GENERIC_MAX(type)       \
			type type##_MAX(type x, type y) \
			{                               \
			    return x > y ? x : y;       \
			}
			
			// 2. 使用 Macro (在 Global 區域)
			GENERIC_MAX(int)    // 產生 int 版本
			GENERIC_MAX(float)  // 產生 float 版本
			
			int main() {
			    // 3. 呼叫產生出來的 Function
			    int i = int_MAX(10, 5);
			    float f = float_MAX(3.14, 2.5);
			    
			    return 0;
			}
			```
		2. 經前置處理器處理過後
			```c
			// 1. 定義印章 (Macro 定義被拿掉了)
			
			// 2. 使用印章的地方，變成了完整的 Function Code！
			int int_MAX(int x, int y) 
			{                               
			    return x > y ? x : y;       
			}
			
			float float_MAX(float x, float y) 
			{                               
			    return x > y ? x : y;       
			}
			
			int main() {
			    // 3. 呼叫產生出來的 Function
			    int i = int_MAX(10, 5);      // 呼叫上面的 int 版本
			    float f = float_MAX(3.14, 2.5); // 呼叫上面的 float 版本
			    
			    return 0;
			}
			```
<br>

#### 五，General Properties of Macros

- simple 和 parameterized macros 的通用規則
	1. 在 replacement list 可以包含其他的 macro<br>E.g:
		```c
		#define PI     3.14159265358
		#define TWO_PI (2*PI)
		```
	2. preprocessor 只會替換**整個 token 都與 identifier 相同的 macro**，所以被包在 identifiers, character constants, 和 string literals 都不會被替換<br>E.g:
		```c
		#define SIZE 256
		
		int BUFFER_SIZE;
		
		if (BUFFER_SIZE)
		  puts("Error: SIZE exceeded");
		```
		儘管 BUFFER_SIZE 與 Error: SIZE exceeded 都有包含到 SIZE，但他們都不會被替換
	3. macro definition 在**整個 file 內都有效**
	4. macro 可以被 `#undef` directive 取消定義
- `#undef` form
	```c
	#undef identifier
	```
- 作用：在**之後的 identifier** 才會被取消，不會影響到之前的 macro
<br><br>

#### 七，Creating Longer Macros

- 可以運用 **comma operator** 來組合其他的 exprssion<br>E.g:
	- macro
		```c
		#define ECHO(s) (gets(s), puts(s))
		```
	- program
		```c
		ECHO(str);
		// becomes (gets(str), puts(str));
		```
- 也可以**運用 {} 來寫出 compound statement** 並與 macro 做搭配<br>E.g:
	```c
	#define ECHO(s) { gets(s); puts(s);}
	```
	- 但這個方法會在**分號**上遇到問題
	- program:
		```c
		if (echo_flag)
		  ECHO(str);
		else
		  gets(str);
		```
	前置處理器會將它處理成
	```c
	if (echo_flag)
	  {gets(s); puts(s);};  // 最後多了一個分號
	else 
	  gets(str)
	```
- 所以要用 compound statement **加上 do 迴圈**<br>E.g:
	1. macro
		```c
		#define ECHO(s)     \
		        do {        \
		          gets(s);  \
		          puts(s);  \
		        } while (0);
		```
	2. program
		```c
		ECHO(str);
		  // becomes do { gets(str); puts(str); } while (0) ;
		```
<br>

#### 八，Predefined Macros

- Predefined macros 就是 C 內建的 macro<br>Table:

	| Name    | Description                       |
	| ------- | --------------------------------- |
	| \_LINE_ | 被編譯時的行數                           |
	| \_FILE_ | 被編譯時的檔名                           |
	| \_DATE_ | 被編譯時的日期 (格式為 Mmm dd yyy)          |
	| \_TIME_ | 被編譯時的時間 (格式為 hh:mm:ss)            |
	| \_STDC_ | 如果被編譯時是遵守 c 的標準 (C89 或 C99) 就會是 1 |
- 用法：
	1. 幫助判斷程式的版本與時間<br>E.g:
		```c
		printf("Wachy Windows (c) 2010 Wacky Software, Inc. \n");
		printf("Compiled on %s at %s\n", _DATE_, _TIME_);
		```
		執行後的結果：
		```
		Wacky Windows (c) 2010 Wacky Software, Inc.
		Compiled on Dec 23 2010 at 22:18:48
		```
	2. 用來判斷程式是在第幾行的時候就遇到問題<br>E.g: 檢查分母是否為零
		- macro
			```c
			#define CHECK_ZERO(divisor)  \
			  if (divisor == 0)  \
			    printf("*** Attempt to divide by zero on line %d "  \
			           "of file %s ***\n", _LINE_, _FILE_)
			```
		- program
			```c
			CHECK_ZERO(j);
			k = i / j;
			```
		- 如果 j 為 0 就會變成
			```
			*** Attempt to divide vy aero on line 9 of file foo.c ***
			```
<br><Br>