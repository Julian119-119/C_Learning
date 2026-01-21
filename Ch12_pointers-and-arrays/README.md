# C program: a modern approach Ch.12 note

## Program overview


| 題號  | 功能             | 觀念                  | 連結                   |
| --- | -------------- | ------------------- | -------------------- |
| 範例一 | 將數字照輸入的順序倒著印回去 | 將陣列的指標用於 for loop 中 | [view](./reverse2.c) |
<br><Br>

---
## Note
### I. Pointer Arithmetic

#### 一，Intro

- 在 Ch11 中有講過的內容
	1. 指標用在陣列上<br>E.g:
		```c
		int a[10], *p;
		p = &a[0];
		```
		示意圖<br>![](./Ch12_attachment/c-programming_a-modern-approach_ch12_1.png)
	2. 將數值存入就會變成
		```c
		*p = 5;
		```
		示意圖：<br>![](./Ch12_attachment/c-programming_a-modern-approach_ch12_2.png)
- 除了之前提過的部份，也可以對於 p 執行 pointer arithmetic (or address arithmetic) ，用以**讀取陣列中的其他元素**
- C 所支持的 pointer arithmetic:
	1. Adding an integer to a pointer 
	2. Subtracting an integer from a pointer 
	3. Subtracting one pointer from another
- 以下為接下來會用的變數的宣告
	```c
	int a[10], *p, *q, i;
	```
<br>

#### 二，Adding an Integer to a Pointer

- 如果 p 指向 a\[i]，則 p + j 則會指向 a\[i + j]<br>E.g:
	1. 
		```c
		p = &a[2];
		```
		![](./Ch12_attachment/c-programming_a-modern-approach_ch12_3.png)
	2. 
		```c
		q = p + 3;
		```
		![](./Ch12_attachment/c-programming_a-modern-approach_ch12_4.png)
	3. 
		```c
		p += 6;
		```
		![](./Ch12_attachment/c-programming_a-modern-approach_ch12_5.png)
<br>

#### 三，Subtracting an Integer from a Pointer

- 如果 p 指向 a\[i]，則 p - j 就會指向 a\[i - j]<br>E.g:
	1. 
		```c
		p = &a[8];
		```
		![](./Ch12_attachment/c-programming_a-modern-approach_ch12_6.png)
	2. 
		```c
		q = p - 3;
		```
		![](./Ch12_attachment/c-programming_a-modern-approach_ch12_7.png)
	3. 
		```c
		p -= 6;
		```
		![](./Ch12_attachment/c-programming_a-modern-approach_ch12_8.png)
<br>

#### 四，Subtracting One Pointer from Another

- 如果 p 是指向 a\[i] 而 q 是指向 a\[j]，則 p - q 就是指向 i - j<br>E.g:
	1. 
		```c
		p = &a[5];
		q = &a[1];
		
		i = p - q;
		// i is 4
		i = q - p;
		// i is -4;
		```
		![](./Ch12_attachment/c-programming_a-modern-approach_ch12_9.png)
<br>

#### 五，Comparing Pointers

- 也可以將 relational operators (<, <=, >, >=) 與 equality operators (== ,!=) 用在比較指標上<bR>E.g:
	```c
	p = &[5];
	q = &[1];
	```
	`p <= q` 會是 0 ，而 `p >= q` 會是 1
<br>

#### 六，Pointers to Compound Literals

- 在 C99 內，指標也可以作用於 Compound literals 上<br>E.g:
	```d
	int *p = (int []){3, 0, 3, 4, 1}'
	```
	此時 p 會**指向第一個元素 (也就是 a\[0])**，所以上述例子等價於
	```c
	int a[] = {3, 0, 3, 4, 1};
	int *p = &a[0];
	```
<br><Br>

### II. Using Pointers for Array Processing

#### 一，Intro

- Pointer arithmetic 使我們可以利用 increment 來使用陣列內的元素<br>E.g: 加總陣列內的元素
	```c
	#define N 10
	...
	int a[N], sum, *p;
	...
	sum = 0;
	for (p = &a[0]; p < &a[N]; p++)
	  sum += *p;
	```
	- 雖然 a\[N] 並不存在，但在這裡是合法的，因為 for statement 不會企圖去存取 a\[N] (因為是 < 而不是 <=)
	- 示意圖：
		1. 第一次迴圈：<br>![](./Ch12_attachment/c-programming_a-modern-approach_ch12_10.png)
		2. 第二次迴圈<br>![](./Ch12_attachment/c-programming_a-modern-approach_ch12_11.png)
		3. 第三次迴圈<br>![](./Ch12_attachment/c-programming_a-modern-approach_ch12_12.png)
<br>

#### 二，Combining the \* and \++ Operators

- E.g:
	```c
	a[i++] = j;
	```
	等價於
	```c
	*p++ = j
	```
	因為 ++ 的優先度較 \* 高，所以編譯器會將它解讀為
	```c
	*(p++) = j
	```
	會先執行 p++ (因為是 profix 的，所以 ++ 不會立刻執行，用 \* 的時候還是 p)，再執行 \*
- 其他的搭配：

	| Expression         | Meaning                                                          |
	| ------------------ | ---------------------------------------------------------------- |
	| \*p++ or \*(p++)   | Value of expression is \*p before increment; increment p later   |
	| (\*p)++            | Value of expression is \*p before increment; increment \*p later |
	| \*++p or \*(++p)   | Increment p first; value of expression is \*p after increment    |
	| ++(\*p) or ++(\*p) | Increment \*p first; value of expression is \*p after increment  |
	- 其中最常用的為 \*p++，常用於 loop 中<Br>E.g:
		```c
		for (p = &a[0]; p < a[N]; p++)
		  sum += *p
		```
		等價於
		```c
		p = &a[0];
		while (p < a[N])
		  sum += *p++;
		```
<br><br>

### III. Using an Array Name as a Pointer

#### 一，Intro

- 陣列的名字可以直接當作**第一個元素的指標**，**不需要額外宣告**<br>E.g:
	```c
	int a[10];
	*a = 7;       // stores 7 in a[0]
	*(a+1) = 12;  // stores 12 in a[1]
	```
	- a + i 就代表 \&a\[i]，而 \*(a+i) 就代表 a\[i]
- 注意，如果重複宣告陣列名字的話，它就會變成一般的指標<br>E.g:
	```c
	int a[10];
	int *a;
	*a = 0;  
	// WRONG
	// 因為此時的 a 為一般的指標，
	// 而你沒有將這個指標指向其他的物件
	```
- 但陣列名字指標**不可被更新數值**<br>E.g:
	```c
	while (*a != 0)
	  a++;             // WRONG
	```
- 這個特性可以直接應用於迴圈當中，使迴圈容易被寫出來<br>E.g:
	```c
	for (p = &a[0]; p < &a[N]; p++)
	  sum += *p
	```
	等價於
	```c
	for (p = a; p < a + N; p++)
	  sum += *p
	```
<br>

#### 二，範例一：Reversing a Series of Numbers (Revisited)

- 學習重點：
	1. 將原本陣列的迴圈修改為用指標來寫
	2. `scanf` 因為在輸入數字的時候本來就要有指標 (因為有 `&`)，所以輸入的變數換成指標變數的時候，就不需要加上 `&`，直接寫 p
- program:
	```c
	// Reverses a series of numbers
	
	#include <stdio.h>
	#define N 10
	
	int main(void)
	
	{
	    int a[N];
	
	    printf("Enter 10 numbers: ");
	    for (int *p = a; p < a + N; p++)
	      scanf("%d", p);
	
	    printf("In reverse order: ");
	    for (int *p = a + (N - 1); p >= a; p--)
	      printf("%d ", *p);
	    printf("\n");
	
	    return 0;
	}
	```
- output:
	```
	Enter 10 numbers: 1 2 3 4 5 6 7 8 9 10
	In reverse order: 10 9 8 7 6 5 4 3 2 1 
	```
<br>

#### 三，Array Arguments (Revisited)

- 當我們將陣列作為引數時，用的便是將陣列名稱作為引數的技巧，所以在 ch9 的時候說陣列並**不會被複製**，因為用的是**指標**<Br>E.g:
	```c
	int find_largest(int a[], int n) {
	  int i, max;
	  
	  max = a[0];
	  for (i = 1; i < n; i++)
	    if (a[i] > max)
	      max = a[i];
	  return max;
	}
	```
	當我們呼叫 function 之後
	```c
	largest = find_largest(b, N);
	```
	就會產生一個指標，將 b 陣列的第一個元素指向 a。陣列本身並沒有被複製
- 這個技巧也導致了陣列的元素會被 function 所影響，而一般的元素不會（因為一般的變數都是被複製過去的）
- 如果要保護陣列內的元素不被影響，可加上 const<br>E.g:
	```c
	int find_largest(const int a[], n) {
	...
	}
	```
<br>

#### 四，Using a Pointer as an Array Name

- 可以將指標作為陣列的下標來使用<br>E.g:
	```c
	#define N 10
	...
	int a[N], i, sum = 0, *p = a;
	...
	for (i = 0; i < N; i++)
	  sum += p[i]
	```
	c 對待 p\[i] 會等於 \*(p+i)
<br>

### IV. Pointers and Multidimensional Arrays

#### 一， Processing the Elements of a Multidimensional Array

- 在 Ch8 中有提到 c 儲存二維陣列的時候是用 row-major order，也就代表對於 c 而言，多維陣列會長的像以下這樣<br>![](./Ch12_attachment/c-programming_a-modern-approach_ch12_13.png)
- 所以可以利用這個特性，先**宣告一個指標在指向陣列中 row 0 與 col 0 的位子再遞增**就可以利用全部的元素了<br>E.g:
	```c
	int a[NUM_ROWS][NUM_COLS];
	int row, col;
	
	...
	
	for (row = o; row < NUM_ROWS; row++)
	  for (col = 0; col < NUM_COLS; col++)
	    a[row][col] = 0;
	```
	等價於
	```c
	int *p
	
	...
	
	for (p = &a[0][0]; p < &a[NUM_ROWS][NUM_COLS]; p++)
	  *p = 0;
	```
	- 但這樣換過去其實會讓易讀性降低
<br>