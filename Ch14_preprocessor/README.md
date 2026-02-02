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
	| \_\_LINE\_\_ | 被編譯時的行數                           |
	| \_\_FILE\_\_ | 被編譯時的檔名                           |
	| \_\_DATE_\_ | 被編譯時的日期 (格式為 Mmm dd yyy)          |
	| \_\_TIME\_\_ | 被編譯時的時間 (格式為 hh:mm:ss)            |
	| \_\_STDC\_\_ | 如果被編譯時是遵守 c 的標準 (C89 或 C99) 就會是 1 |
- 用法：
	1. 幫助判斷程式的**版本與時間**<br>E.g:
		```c
		printf("Wachy Windows (c) 2010 Wacky Software, Inc. \n");
		printf("Compiled on %s at %s\n", __DATE__, __TIME__);
		```
		執行後的結果：
		```
		Wacky Windows (c) 2010 Wacky Software, Inc.
		Compiled on Dec 23 2010 at 22:18:48
		```
	2. 用來判斷程式是在**第幾行**的時候就遇到問題<br>E.g: 檢查分母是否為零
		- macro
			```c
			#define CHECK_ZERO(divisor)  \
			  if (divisor == 0)  \
			    printf("*** Attempt to divide by zero on line %d "  \
			           "of file %s ***\n", __LINE__, __FILE__)
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

#### 九，Addition Predefined Macros in C99

- C99 額外提供的 predefined macros


	| Name                        | Description                                                                            |
	| --------------------------- | -------------------------------------------------------------------------------------- |
	| \_\_STDC\_\_HOSTED\_\_            | 1 if this is a hosted implementation; 0 if it is freestanding                          |
	| \_\_STDC_\_VERSION\_\_              | version of C standard supported                                                        |
	| \_\_STDC\_IEC\_559\_\_          | 1 if IEC 60559 floating-point arithmetic is supported                                  |
	| \_\_STDC\_IEC\_559\_COMPLEX\_\_ | 1 if IEC 60559 complex arithmetic is supported                                         |
	| \_\_STDC\_ISO\_10646\_\_        | yyyymmL if wchar_t values match the ISO 10646 standard of the specified year and month |
- `__STDC__HOSTED__`
	- implementation of c: 也就是執行 c 所需的環境，由編譯器再加上其他的軟體所組成
		1. hosted implementation: 任何遵守 C99 的規定的 program 都是
		2. greestanding implementation: 不使用其他的軟體 (連 <stdio.h> 都不能用)，最基本的程式
- `__STDC__VERSION_`
	- 用來檢查 c 的版本
	- 輸出的格式為 long integer constant ，例如 c99 的代碼就是 199409L
- `__STDC_IEC_559__`
	- 如果編譯器用的浮點計算是依據 IEC 60559 就會回傳 1
- `__STDC_IEC_559_COMPLEX__`
	- 如果在計算複雜的算術時是依據 IEC 60559 就會回傳 1
- `__STDC_ISO_10646__`
	- 檢查 `wchar_t` 是否使用 ISO/IEC 10646 標準
<br>

#### 十，Empty Macro Arguments

- 如果在使用 macro 的時候給予**空的引數**，後面的 replacement list 在那個引數就會**直接空掉**<Br>E.g:
	- macro
		```c
		#define ADD(x, y) (x + y)
		```
	- program
		```c
		i = ADD(, k)
		```
		經過 preprocessor 處理後會變成
		```c
		i = (+k)
		```
		就是 i 會純粹的變空這樣
- 如果是在 replacement list 遇到 **\# operator** ，就會變成**空的字串 ("")**<br>E.g:
	```c
	#define MK_STR(x) #x
	...
	char empty_str[] = MK_STR();
	```
	經過 preprocessor 後會變成
	```c
	char empty_str[] = "";
	```
- 如果在 replacement list 遇到 **\#\# operato** ，則會變成 placemarker token，也就是相當於**直接消失**<br>E.g:
	```c
	#define JOIN(x, y, z) x##y##z
	...
	int JOIN(a, b, c), JOIN(a, b, ), JOIN(a, , c), JOIN(, , c);
	```
	經過 preprocessor 後會變成
	```c
	int abc, ab, ac, c;
	```
<br>

#### 十一，Macros with a Variable Number of Arguments

- 在 C99 中可以讓 macro 接受**不知道有幾個**的引數<br>E.g:
	- macro
		```c
		#define TEST(condition, ...) ((condition) ?  \
		  printf("Passed test: %s\n", #condition)    \
		  printf(__VA_ARGS__))
		```
- **... (ellipsis)** 用來**吸收額外的參數** (**逗號也會被吸收進去**)
- `__VA_ARGX__` 用來**呼叫**剛剛 ... 所**吸收到的參數**<br>E.g: 將上面的 macro 拿來使用
	```c
	TEST(voltage <= max_voltage,
	     "Voltage %d exceeds %d\n", voltage, max_voltage);
	```
	condition 就是第一個參數 (voltage <= max_voltage)<br>... 會將整個 "Voltage %d exceeds %d\n", voltage, max_voltage 都吸收進去，並用 `__VA_ARGS__` 代指他們<br>所以經過 preprocessor 處理過後會變成
	```c
	((voltage <= max_voltage) ?
	  printf("Passed test: %s\n", "voltage <= max_voltage)
	  printf("voltage%d exceeds %d\n", voltage, max_voltage));
	```
<br>

#### 十二，The `__func__` Identifier

- 主要用途：**debug**
- 用法與 string variable 很像
- 效用等價於
	```c
	static const char __func__[] = "function-name"
	```
	- function_name: 函數的名稱
	- 也就是用 `__func__` 代指**當前的 function**
- 實際用法的範例
	1. macro:
		```c
		#define FUNCTION_CALLED() printf("%s called\n", __func__)
		#define FUNCTION_RETURNS() printf("%s returns\n", __func__)
		```
	2. program
		```c
		void f(void)
		{
		  FUNCTION_CALLED();  // displays "f called"
		  ...
		  FUNCTION_RETURNS();  // displays "f returns"
		}
		```
<br><Br>

## IV. Conditional Compilation

#### 一，The `#if` and `#endif` Directives

- 用途：加入**條件測試**來決定要不要讓編譯器知道這幾行
- form:
	- 用 `#if` 與 `#endif` 來將 expression 包住
	- 
		```c
		#if constant-expression
		...
		#endif
		```
	- 如果 constant-expression 為真，就會將中間的 statement 顯示給編譯器
- E.g: 在 debug 中 
	- macro
		```c
		#define DEBUG 1
		// 與之前的條件判斷一樣
		// 只要不為 0 就是 ture
		```
	- program
		```c
		#if DEBUG
		printf("Value of i: %d\n", i);
		printf("Value of j: %d\n", j);
		#endif
		```
- 也一樣可以加上 ! 來檢測是否為假<br>E.g:
	```c
	#if !DEBUG
	```
<Br>

#### 二，The `defined` Operator

- 如果 identifier **已經被定義**過成 macro 了就會是 1 ，否則就是 0<br>E.g:
	```c
	#if defined(DEBUG)
	...
	#endif
	```
	也可以省略 () 變成
	```c
	#if defined DEBUG
	```
	也就是說只要 DEBUG 有被定義過就行，**不一定要給值**<br>E.g: 之前定義 macro 時
	```c
	#define DEBUG
	```
<Br>

#### 三，The `#ifdef` and `#ifndef` Directives

1. `#ifdef`
	- 用途：測試 identifier 是否**已經**被定義成 macro 了
	- form: 與 `#if` 類似
		```c
		#ifdef identifier
		Lines to be included if identigier is defined as a macro
		#endif
		```
	- 與 `#if` + `defined` 功用相同，也就是說
		```c
		#if def identifier
		```
		等價於
		```c
		#if defined(identifier)
		```
2. `ifndef`
	- 用途：`ifdef` 的相反，用來測試是不是**沒有**被定義成 macro
	- form:
		```c
		#ifndef identifier
		```
	- 也就是說
		```c
		#ifndef identifier
		```
		等價於
		```c
		#if !defined(identifier)
		```
<br><Br>

## V. Miscellaneous Directives

#### 一，The `#error` Directive

- form:
	```c
	#error message
	```
- 當遇到 `#error` 時會進出 message 的訊息
- E.g:
	1. 與 `#if` 搭配
		```c
		#if INT_MAX < 100000
		#error int type is too small
		#endif
		```
	2. 與 `#else` 搭配
		```c
		#if defined(WIN32)
		...
		#elif defined(MAC_OS)
		...
		#elif defined(LINUX)
		...
		#else
		#error No operating system specified
		#endif
		```
<br>

#### 二，The `#line` Directive

- 用途：**替換程式所數出來的行數**
- form:
	1. 
		```c
		#line n
		```
	2. 
		```c
		#line n "file"
		```
- E.g:
	```c
	#line 10 "bar.c"
	```
	如果這一行的程式是在 foo.c 中的第五行的話，當它被程式偵測到有錯誤時，會偵測成在 bar.c 中的第 10 行
<br>

#### 三，The `#pragma` Directive

- 寫給編譯器用的話，後面的 token ，並不是給 program 所運行的\
- 通常是有特殊需求才會用的
- form:
	```c
	#pragma tokens
	```
- E.g:
	```C
	#pragma data(heap_size => 1000, stack_size => 2000)
	```