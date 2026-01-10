# # C program: a modern approach Ch.8 note

## I. One-Dimensional Arrays

#### 一，Intro

- array: 一種包含了數個數字的 data structure，裡面的數字就稱為 elements (元素)
- 宣告陣列<br>E.g: 內含 10 個 int type 的 element 的 array
	```c
	int a[10];
	```
- 也可以運用 definition 宣告他的 element 數<br>E.g:
	```c
	#define N 10
	...
	int a[N];
	```
<br>

#### 二， Array Subscripting

- element 的名字是從 a[0] 開始數，一路數到 a[n-1]，這個命名方式就稱為 subscripting 或 indexing
- 每一個 a[i] 皆為 lvalue，所以可以像一般變數一樣運用<br>E.g:
	```c
	a[0] = 1;
	printf("%d\n", a[5]);
	++a[i];
	```
- 每一個的 element 的運作原理都是和他的所屬的型別一樣，例如前面宣告了 a[i] 皆是 `int` 那他們的運作方式就和 `int` 一模一樣