# C program: a modern approach Ch.9 note

## Program overview


| 題號  | 功能         | 觀念                     | 連結                    |
| --- | ---------- | ---------------------- | --------------------- |
| 範例一 | 計算數字的平均    | 學習定義與呼叫有回傳值的 function  | [view](./average.c)   |
| 範例二 | 將數字遞減並列印出來 | 學習定義與呼叫沒有回傳值的 function | [view](./countdown.c) |
| 範例三 | 列印出一句話     | 學習定義與呼叫沒有參數的 function  | [view](./pun2.c)      |
| 範例四 | 測試數字是否為質數  | 將方程式結合布林值，綜和以上所學       | [view](./prime.c)     |
<br><Br>

---
## Note
### I. Defining and Calling Functions
#### 一，Function definitions

- form:
	```c
	return-type function-name ( parameters)
	{
	  declarations
	  statements
	}
	```
	- return-type 的規定
		1. 不能回傳陣列
		2. 如果**不用回傳的話就打 void** 
		3. 不能是空的
	- parameters 的規定
		1. 如果要打多個參數的話，每個都要以 , 隔開
		2. 每個參數都要在**前面加上型別** (不可偷懶)
		3. 如果**不用回傳的話就打 void** 
	- declaratins
		1. 在 function 所宣告的變數是不可以被其他的 function 所引用的
	- body 的部份可以是空的 (通常是還在寫的過程當中會這樣)<br>E.g:
		```c
		void printf_pun(void)
		{
		}
		```
- 排版：也可以將 return-type 移到上一行，這在**型別太長時常用**<br>E.g:
	```c
	double
	average(double a, double b)
	{
	  return (a + b) / 2;
	}
	```
<br>

#### 二，Function Calls

- form:
	```c
	function-name( arguments )
	```
- 在呼叫的 function 的時候可能會包含一系列的引數
- 就算沒有包含引數，也要打上 ()<Br>E.g:
	```c
	print_pun();
	```
- 如果是沒有回傳值的 function ，就一定是單獨成 statement<br>E.g:
	```c
	print_count(i);  // 後面記得加 ;
	```
- 如果是有回傳值的  function ，基本上就可以當數字用<Br>E.g:
	```c
	avg = average(x, y);
	if (average(x, y) > 0)
	  pprintf("Average is positive\n")
	printf("The average si %g\n", average(x, y));
	```
- 如果不再意它回傳的值，想要直接丟棄的話，在 function-name 前面加上 `(void)`<br>E.g:
	```c
	(void) printf("Hi, Mon!\n");
	```
<br>

#### 三，範例一：Computing Averages

###### 1. 定義 function

```c
double average(double a, double b)
{
  return (a + b) / 2
}
```

- 這段 program 的作用是**定義 average 這個 function**
- 一開始的 `double` 是定義要回傳的值的種類
- `a` 與 `b` 為 parameters (參數)，代表當 average 被呼叫的時候所提供的數字
- `double a`就代表 a 是 `double`
- `return (a + b) / 2` 就代表要回傳這個結果

###### 2. 呼叫 function

- 用 average(x, y)
- 後面的 x, y 稱為引數 (argument)，用於**提供 function 計算時所需的數字**，也就是對應到剛剛的 `double a` 與 `double b`
- **任何的 expression 都可以當作引數**，例如 aveage(X/2, Y/3) 也是可以的
- 呼叫完後就會執行剛剛所定義的 function
- 可以放置在任何需要回傳這個 function 的 return 上的地方<br>E.g:
	```c
	printf("Average: %g\n", average(x, y));
	avg = average(x, y)
	```

###### 3. program
```c average.c
// Computes pairwise averages of three numbers

#include <stdio.h>

double average(double a, double b)
{
  return (a + b) / 2;
}

int main (void)
{
  double x, y, z;

  printf("Enter three numbers: ");
  scanf("%lf %lf %lf", &x, &y, &z);

  printf("Average of %g and %g: %g\n", x, y, average(x, y));
  printf("Average of %g and %g: %g\n", y, z, average(y, z));
  printf("Average of %g and %g: %g\n", x, z, average(x, z));

  return 0;
}
```

output:
```
Enter three numbers: 3.5 9.6 10.2
Average of 3.5 and 9.6: 6.55
Average of 9.6 and 10.2: 9.9
Average of 3.5 and 10.2: 6.85
```
<br>

#### 四，範例二：Printing a Countdown

- 如果不需要回傳值，就在規定回傳值類型的地方加上 `void` (void 的意思就是沒有)<br>E.g:
	```c
	void printf_count(int n)
	{
	  printf("T minus %d and counting\n", n);
	}
	```
- 因為它沒有回傳值，所以在呼叫的時候一定是獨立一個 statement<br>E.g:
	```c
	// Prints a countdown
	
	#include <stdio.h>
	
	void printf_count(int n)
	{
	  printf("T minus %d and counting\n", n);
	}
	
	int main(void)
	{
	  for (int i = 10; i > 0; i--)
	    printf_count(i);
	
	  return 0;
	}
	```
<br>

#### 五，範例三，沒有參數的 function

- 同二，沒有參數的話就在原本要填參數的地方填 `void`<br>E.g:
	```c
	void print_pun(void)
	{
	  printf("To C, or not to C: that is the question.\n")
	}
	```
- 如果要呼叫沒有參數的 function 的話就直接打空的 ()<br>E.g:
	```c
	print_pun()
	```
- program:
	```c pun2.c
	// Prints a bad pun
	
	#include <stdio.h>
	
	void print_pun(void)
	{
	  printf("To c, or not to C: that is the question.\n");
	}
	
	int main(void)
	{
	  print_pun();
	  return 0;
	}
	```
<br>

#### 六，範例四：Testing Whether a Number Is Prime

- program:
	```c
	// Test whether a number is prime
	
	#include <stdbool.h>
	#include <stdio.h>
	
	bool is_prime(long n)
	{
	  int divisor;
	
	  if (n <= 1)
	    return false;
	  for (divisor = 2; divisor * divisor <= n; divisor++)
	    if (!(n % divisor))
	      return false;
	 return true;
	}
	
	int main(void)
	{
	  long n;
	
	  printf("Enter a number: ");
	  scanf("%ld", &n);
	
	  if (is_prime(n))
	    printf("%ld is a prime\n",n );
	  else
	    printf("%ld is not a prime\n", n);
	
	  return 0;
	}
	```
- output:
	```
	$ ./prime 
	Enter a number: 18
	18 is not a prime
	
	$ ./prime 
	Enter a number: 19
	19 is a prime
	```
<br><br>

---
### II. Function Declarations

- 作用：就算 program 是先呼叫再定義 function，也能夠保證可以用此 function
- 可以將他想成：先告訴編譯器接下來會有什麼 function ，要儲存成什麼類型。所以這一行也被稱為 function 的 prototype (原型)
- form:
	```c
	return-type function-name ( parameters )
	```
- parameters 的變數不一定需要一個名稱，只要有型別就行<br>E.g:
	```c
	double average(double, double);
	```
- 位置：理所當然是在 function 之前<br>E.g:
	```c
	#include <stdio.h>
	
	double average(double a, double b);    
	// Function Declaration
	
	int main (void)
	{
	  double x, y, z;
	
	  printf("Enter three numbers: ");
	  scanf("%lf %lf %lf", &x, &y, &z);
	
	  printf("Average of %g and %g: %g\n", x, y, average(x, y));
	  printf("Average of %g and %g: %g\n", y, z, average(y, z));
	  printf("Average of %g and %g: %g\n", x, z, average(x, z));
	
	  return 0;
	}
	
	double average(double a, double b)    
	{
	  return (a + b) / 2;
	}
	// definition
	```
<br><br>

### III. Arguments

#### 一，Intro
- argument 是在呼叫 function 的時候用的數字，而 parameter 則是在定義 function 的時候用的
- argument 的作用是將數字**複製給 parameter**，所以在其他 function 內對 parameter 做的事情並不會影響到 argement
- 優點：可以直接在 parameter 上修改而不影響到 argument<br>E.g:
	```c
	int power(int x, int n)
	{
	  int i, result = 1;
	  
	  for (i = 1; i <= n; i++)
	    result *= x;
	  return result;
	}
	```
	等價於
	```c
	int power(int x, int n)
	{
	  int result = 1;
	 
	  while (n-- > 0)    
	   // 直接利用 decrement 的 side effect 修改 n
	    result *= result
	
	  return result;
	}
	```
- 缺點：這也導致了它無法去直接回傳值給 argument，會導致有一些 function 不好寫
<br>

#### 二，Argument Conversions

- C 是允許引數的型別與參數的不同的，但如果不同就會依據有沒有先定義或宣告而有不同結果
	1. 有在前面先定義或宣告：
		- C 會將引數的型別轉為參數的型別 (因為它知道要轉成什麼型別)
	2. 沒有先定義或宣告：
		- 使用 default argument promotion:
			1. `float` 轉成 `double`
			2. integral promotion，這會導致 `char` 與 `short` 被轉成 `int`
		- **依賴預設的行為是危險的**，當轉換的型別與參數的型別不同就會發生 undefined behavior
<br>

#### 三，Array Arguments

- array 也可以被用於引數與參數，但在 function 內**長度不確定**，就算用 `sizeof` 的寫法也會是**錯的** (原因在 Ch12 會講)<br>E.g:
	```c
	int f(int a[])
	{
	  ...
	}
	```
- 為了在 function 內要知道陣列的長度，就需要**再放一個引數，用來指出有多少元素**<br>E.g:
	```c
	int sum_array(int a[], int n)
	// n 為陣列長度
	{
	  int i, sum = 0;
	  
	  for(i = 0; i < n; i++)
	    sum += a[i];
	    
	    return sum
	}
	```
- function declaration 就會寫成
	```c
	int sum_array(int a[], int n);
	```
	或省略名字
	```c
	int sum_array(int [], int);
	```
- 一樣也可以搭配 **macro**
	```c
	#define LEN 100
	
	int main(void)
	{
	  int b[LEN], total
	  ...
	  total = sum_array(b, LEN);
	  ...
	}
	```
	記住，**不要在引數加上 \[]**
	```c
	total = sum_array(b[], LEN);
	/*** WRONG ***/
	```

- 如果只要用陣列的前幾項就好，可以利用這個特性，將長度改為你要看的前 n 項<br>E.g:
	```c
	total = sum_array(b, 50);
	// 加總前 50 項 
	// (即使後面還有其他項，function 也不會知道)
	```
	但還是**不能超過元素的個數**
- 雖然在一般數值上參數是不會影響到引數的，但可以影響到引數**陣列內的元素**<br>E.g:
	```C
	void store_zeros(int a[], int n)
	{
	  int i;
	  
	  for (i = 0; i < n; i++)
	    a[i] = 0;
	}
	```
	The call
	```c
	store_zeros(b, 100);
	// b 陣列內的前 100 個元素都會被設定為 0
	```
- 在宣告與定義高維的陣列的時候，**只能省略第一個維度的長度**，其他的都要**明確定義**
<br>

#### 四，Variable-Length Array Parameters

- 要將變數當作陣列參數的長度時，就一樣填兩個引數，變數和參數。但**變數一定要在前面**，不然編譯器會不知道那個變數是什麼<br>E.g:
```c
int sum_array(int n, int a[])
// n 和 a[n] 的順序不能調換
{
...
}
```
- VLA Parameter 的 prototype<br>E.g:
	```c
	int sum_array(int n, int a[n]);
	```
	或
	```c
	int sum_array(int n, int a[*]);
	// * 代表前一個參數為他的長度 
	```
	或
	```c
	int sum_array(int, int [*]);
	```
- 長度也可以用 **expression**
	```c
	int concatenate(int m, int n, int a[m], int b[n], int c[m+n])
	{
	  ...
	}
	```
- 以上的東西當然也可以用於高維的陣列<br>E.g:
	```c
	int sum_two_dimensional_array(int n, int m, int a[n][m])
	{
	  int i, j, sum = 0;
	  
	  for (i = 0; i < n; i++)
	    for (j = 0; j < m; j++)
	      sum += a[i][j];
	  return sum;
	}
	```
	prototype
	```c
	int sum_two_dimensional_array(int n, int m, int a[n][m]);
	// 或
	int sum_two_dimensional_array(int n, int m, int a[*][*]);
	```
<br>

#### 五，Using `static` in Array Parameter Declarations

- `static` 用於指出陣列中某一維的長度
- 算是給予編譯器的提示
- E.g:
	```c
	int sum_array(int a[static 3], int n)
	{
	  ...
	}
	```
- 但就只能用在第一個維度，其他維度皆不可用
<br>

#### 六，Compound literal

- 用途：在將陣列用作引數的同時宣告與初始化它<br>E.g:
	```c
	int b[] = {3, 0, 3, 4, 1};
	total = sum_array(b, 5);
	```
	等價於
	```c
	total = sum_array((int []){3, 0, 3, 4, 1}, 5)
	```
- 如果不介意陣列的長度的話，則
	```c
	(int [4]{1, 2, 3, 4})
	```
	等價於
	```c
	(int []){1, 2, 3, 4}
	```
- 與陣列初始化的時候一樣，可以用 designated initializers 也可以用 list的方式，沒被設定到的數字一樣就是 0
- 也當然**可以用 expression**<br>E.g:
	```c
	total = sum_array((int []){2 * i, i + j, j * k}, 3)
	```
- 也可以結合 `const`，來做出不會改變的陣列<br>E.g:
	```c
	(const int []){5, 4}
	```
<br><Br>

---