# C program: a modern approach Ch.10 note

## Program overview


| 題號      | 功能          | 觀念                          | 連結                       |
| ------- | ----------- | --------------------------- | ------------------------ |
| example | stack 結構的模板 | 學習 stack 的觀念，並利用全域變數在 C 重現。 | [view](./simulate_stack) |
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
