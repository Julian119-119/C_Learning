# C program: a modern approach Ch.15 note

## I. Source Files

- 一個 program 可以被分成許多的 **source file**
- 而每一個 source file 皆是以 **.c** 作為副檔名
- 將一個 program 分成多個 source file 的好處
	1. 排列好每一個的 program 的架構
	2. 每一個 source file 可以獨自被編譯，這樣就可以節省時間
	3. 讓每一個 function 更容易被重複使用
<br><br>

## II. Header files

#### 一， Intro

- `#include` 可以將 file 的內容全部包括進來 (包含 prototype, macro, variable 等)，裡面的函式會被原封不動的塞進來
- 但不能直接使用 source file (原因後面會說)
- 被包含進來的 file 就稱之為 **header files** (或是 include files)
- 而 header file 的副檔名為 **.h**
<br>

#### 二，The `#include` Directive

- form
	1. 給 c 自己的 library 用
		```c
		#include <filename>
		```
		- 它會去**系統的目錄**去尋找 (例如 \/usr\/include)
	2. 給其他的 header file 用
		```c
		#include "filename"
		```
		- 預設會從**當前的工作目錄**去尋找
		- 如果要用其他的目錄的話就要在 command line 用 -I path 這個參數
- 也可以在 filename 上包含**檔案的位置**<br>E.g:
	```c
	#include "/cprogx/utils.h"
	```
	- 但建議不要在 filename 上用絕對位置，因為絕對位置很有可能會**因為不同裝置而換**
	- 建議使用**相對位置**<br>E.g
		```c
		#include "..\include\utils.h"
		```
- 第三種的 form ，用 macro 來將檔案替換
	```c
	#include tokens
	```
	- 也就是這個 token 會先被前面的 macro 用成**其他的檔案**
	- 接著才會執行 include<br>E.g:
		```c
		#if defined(IA32)
		  #define CPU_FILE "ia32.h"
		#elif defined(IA64)
		  #define CPU_FILE "ia64.h"
		#elif defined(AMD64)
		  #define CPU_FILE "amd64.h"
		#endif
		
		#include CPU_FILE
		```
		1. 會先執行前面的 macro 代換，也就是將 CPU_FILE 代換成 "ia32.h", "ia64.h" 或 "and64.h" 
		2. 接著才會執行 `#include`
<br>

#### 三，Sharing Macro Definitions and Type Definitions

- 要在多個 source files 中共用 macro 或 type definition 的話，就需要將它們寫在**同一個 header file 中**，並使用 `#include` 來引用
- E.g: 將以下的 definitions 寫在 boolean.h
	```c
	#define BOOL int
	#define TRUE 1
	#define FALSE 0
	```
	- 接著只要在其他的 soure files 中使用 `#include boolean.h` 就可以用這些 macro 了
<br>

#### 四，Sharing Function Prototypes

- C99 中禁止在編譯器**沒有看到 declaration 或 definition 時就呼叫 function**，所以如果在使用其他檔案中的 function 時，一定要先確保**編譯器先看過它**
- 解決方法：
	- 如果在要呼叫 function 的檔案做宣告，會**很難維護**
	- 所以要**在 header file 內做出 prototype**
- E.g: 假設我們要使用 ch10 中的 stack
	1. 不能直接用 `#include "stack.c"` ，必須要**寫出一個 header file**
	2. header file 內只需要做出**宣告**即可<br>**stack.h**:
		```c
		void make_empty(void);
		int is_empty(void);
		int is_full(void);
		void push(int i);
		int pop(void);
		```
	3. 為了要讓編譯器可以驗證型別，所以在**原本的 source file 與要引用的 file 都必須要用 `#include <stack.h>`**
<br>

#### 五，Sharing Variable Declarations

- 在共用 function 的時候，我們將**宣告寫在了 header file 中，定義留在了 source file**，而 variable 的作法也一樣
- 以往的宣告都會直接一起定義<br>E.g:
	```c
	int i;
	```
- **不定義只宣告**的話要加上 **`extern`**<br>E.g:
	```c
	extern int i;
	```
	- 此時的 i 並沒有被分配空間，只是讓編譯器知道它存在而已
	- 因此如果是陣列的話就無須給長度，直接用 `extern a[]` 就可
- 與 function 一樣，這個是在 header file 中所使用的
- 要使用時，只須要在**一個 source file** 中定義即可，也就是在一個檔案中使用，**不可以在 header file 中定義**，會變成每個檔案都搶著定義
	```c
	int i;
	```
	- 此時記憶體就會有位置給 i 來儲存數值，並可初始化了
<br>

#### 六，Nested Includes

- 也就是在 header files 中加入其他的 header files
- E.g: 在 stack.h 中的
	```c
	int is_empty(void);
	int is_full(void);
	```
	因為這兩個只會回傳 0 或 1 ，所以也可以用 `Bool`  來宣告，但因為 `Bool` 是位於 <stdbool.h> 這個 header files ，所以就必須變成
	```c
	#include <Stdbool.h>
	
	Bool is_empty(void);
	Bool is_full(void);
	```
<Br>

#### 七，Protecting Header Files

- 如果使用 nested header file 很有可能會出現同一個 header file 被**重複使用**的問題
- 如果只是 macro definitions, function prototypes, 或者是  variable declaration 那麼編譯器不會報錯
- 但如果是 type definitions 就會報錯
- 解決方法：使用**條件編譯**
	- 注：雖然只有在 type definitions 中才會報錯，但如果每遇到一個 prototype 都要重複定義會減低效率，所以**建議每個都要加**
	- E.g: 在 <boolean.h>
	```c
	#ifndef BOOLEAN_H
	#define BOOLEAN_H
	
	#define TRUE1
	#define FALSE 0
	
	#endif
	```
<br>

#### 八，`#error` Directives in Header Files

- 使用 `#error` 的話可以在沒有**包括到需要的 header files 時給予提示**<Br>E.g:
	```c
	#ifndef __STDC__
	#error This header requires a Standard C compiler
	#endif
	```

## III. Building a Multiple-File Program

- 這邊主要是講 makefile 的，為了敢進度，我只有略讀
- 筆記等未來讀完 ch17 後再來補