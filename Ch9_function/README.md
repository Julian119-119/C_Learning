# C program: a modern approach Ch.9 note

## Program overview


| 題號       | 功能         | 觀念                                        | 連結                                      |
| -------- | ---------- | ----------------------------------------- | --------------------------------------- |
| 範例一      | 計算數字的平均    | 學習定義與呼叫有回傳值的 function                     | [view](./average.c)                     |
| 範例二      | 將數字遞減並列印出來 | 學習定義與呼叫沒有回傳值的 function                    | [view](./countdown.c)                   |
| 範例三      | 列印出一句話     | 學習定義與呼叫沒有參數的 function                     | [view](./pun2.c)                        |
| 範例四      | 測試數字是否為質數  | 將方程式結合布林值，綜和以上所學                          | [view](./prime.c)                       |
| 範例五      | 排序 10 個數字  | 學習 quicksort 的演算法，並且運用遞迴的 function 將其寫成程式 | [view](./qsort.c)                       |
| Proj.1v1 | 由小到大排序數字   | 學習用 selection sort 的邏輯去排序順序               | [view](./programming-project_Ch9_1v1.c) |
| Proj.1v2 | 同上         | 此為 version 1 程式的重構，用了較簡單的方法去寫             | [view](./programming-project_Ch9_1v2.c) |
| Proj.8   | 玩花旗骰遊戲     | 寫出骰子的隨機點數，並且將程式拆成三段的函數來寫                  | [view](./programming-project_Ch9_8.c)   |
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
## IV. The `return` Statement

- 作用：回傳值
- form:
	```c
	return expression;
	```
	- 通常 expression 都是單一常數或變數
	- 但也可以用更複雜的 expression<br>E.g:
		```c
		return n >= 0 ? n : 0;
		```
		\*p.s：如果忘記這個 expression 的話可以看 ch5: conditional expressions
- 如果回傳的值與要求的值不同，就會做 implicit conversion ，回傳函數要求的型別
- 如果 function 要求要回傳值，但到底了卻發現沒有 `return`，就會是 undefined behavior
- `return` 也可以出現在不需要回傳值的 function<br>form:
	```c
	return;
	// return in a void function
	```
	E.g:
	```c
	void print_int(int i)
	{
	  if (i < 0)
	    return;
	  printf("%d", i);
	}
	// 如果 i < 0，就會直接結束 function
	```
<br><br>

## V. Program Termination

#### 一，The `exit` Function

- 用途：結束 `main` function (也可以用 `return`)
- **屬於 <stdlib.h>** 這個 header 內
- 引數的意義與 `return` 中的意義一樣，都是用來標注 `main` 的執行狀況 (結束就是 0，其他的就非 0)
- E.g: (用於標示正常的結束，就回傳 0)
	```c
	exit(0);
	// normal termination
	```
- 也可以用 **"EXIT_SUCCESS" 來標示正常的結束** (與 0 意義一樣)，**"EXIT_FAILURE" 來標示非正常的結束**<br>E.g:
	```c
	exit(EXIT_SUCCESS);
	// normal termination
	exit(EXIT_FAILURE);
	// abnormal termination
	```
	- \*P.S: 這兩個是屬於 <stdlib.h> 的 macro，分別代表 0 和 1
- 這 `exit` 與 `return` 在 `main` 之中基本上是等價的，所以 `exit` 當然可以用 expression
	```c
	exit(expression)
	```
<br>

#### 二，Recursion

- 遞迴的 function： 在 function 內呼叫自己<br>E.g: 
	1. 計算 n!
		```c
		int fact(int n)
		{
		  if (n <= 1)
		    return 1;
		  else
		    return n * fact(n-1);
		}
		// n! = n * (n - 1)! 
		```
	2. 計算 $x^n$ (利用 $x^n = x \times x^{n - 1}$)
		```c
		int power(int x, int n)
		{
		  if (n == 0)
		    return 1;
		  else
		    return x * power(x, n - 1);
		}
		```
		也可以用 conditional expression 來簡化方程式
		```c
		int power(int x, int n)
		{
		  return n == 0 ? 1 : x * power(x, n - 1);
		}
		```
- 記住：一定要有一個中止條件，否則就會一直被執行下去（例如 計算階乘的 `n <= 1` 與計算 $x^n$ 的 `n == 0`）
<br>

#### 三，The Quicksort Algorithm

- divide-and-conauer: 一種演算法的設計，將大塊的問題分割成小塊的部份來解決問題
- 其中最受歡迎的就是 Quicksort，用於**由大到小或由小到大排序**，以下是其順序
	1. 從元素陣列選擇元素 e 作為基準。將其重排為元素 1,...,i - 1 小於 e，元素 i = e，而元素 i + 1,...,n 皆大於或等於 e
	2. 將元素 1,...,i - 1 用 quicksort 重排
	3. 將元素 i + 1,...,n 用 quicksort 重排
- 在 C 內，一次的 Quicksort 的實際作法
	- *\*這邊建議可以去看課本的圖例，我認為畫的很好
	- *\* 接下來會使用 `low` 與 `high` 這兩個 mark ，因為只是 mark ，所以不代表真的大小關係，他們是代表比基準點還 "小" 或 "大" 是為真還是為假*
	1. 先將最左邊的數字設定為 `low`，右邊的設定為 `high`
	2. 將 `low` 的數字先放在一旁（也就是先複製給其他的變數），做為基準點並且製造出一個洞
	3. 接下來開始做以下的迴圈：
		1. **將 `high` 從右往左移動 `high`**，去比對是否比基準點還來的大。為真，就向右移去偵測下一個數字。為假，則將該數字塞進在 `low` 的洞且這個位置就成為了新的洞，並且跳到第 4 步 (開始移動 `low`)
		2. **將 `low` 從左往右移動**，去比對是否比基準點還來的小。先比對當前位置的數值，為真，就向右移去偵測下一個數字。為假，則將該數字塞進在 `high` 的洞且這個位置就成為了新的洞，並且跳到第 3 步 (開始移動 `high`)
		3. 結束的條件：如果 `high` 與 `low` 剛好比對到了相同的位置就結束
<br>

#### 五，範例五：Quicksort

- 功能：排序 10 個數字的順序
- 這一次我一樣是先看懂一次這個 program，再嘗試自己寫一次，因為我個人認為這個演算法難，需要多花心力才能看懂它，無法直接就寫出來
- 我在自己重寫這一個程式的時候，是將它拆成 split 的部份與 quicksort 的部份來分段測試以及完成

###### 1. 課本上的 program + 我自己的註解

```c
// Sorts an array of integers using Quicksort algorithm

#include <stdio.h>

#define N 10

void quicksort(int a[], int low, int high);
int split(int a[], int low, int high);

int main(void)
{
  int a[N], i;

  printf("Enter 10 numbers to be sorted: ");
  for(i = 0; i < N; i++)
    scanf("%d", &a[i]);

  quicksort(a, 0, N - 1);

  printf("In sorted order: ");
  for (i = 0; i < N; i++)
    printf("%d ", a[i]);
  printf("\n");
}

void quicksort(int a[], int low, int high)
// 呼叫 quicksort 目的是排序
// 不是依據這個 function 在做什麼來命名
{
  int middle;

  if (low >= high) return;
  // 這是這個遞迴函數的結束條件
  // 因為在持續分堆的過程中會越來越小
  // 連帶的，每段的 high 與 low 也會越來越逼近
  // 最後小到 low 大於或等於 high 的時候就要停止
  middle = split(a, low, high);
  quicksort(a, low, middle - 1);
  quicksort(a, middle + 1, high);
}

int split(int a[], int low, int high)
// 呼叫 split 的目的是找出分割點
// 不是依據這個 function 再做什麼來命名
{
  int part_element = a[low];
  // part_element 為基準值

  for (;;) {
	// 因為每次都是先 low 再 high 再 low 到結束
	// 所以就用無限迴圈的寫法
	
    // 洞在 low 上
    while (low < high && part_element <= a[high])
      high--;
    if (low == high) break;
    a[low++] = a [high];
    // 因為是後綴的遞增，所以是先填完洞再移動 low 的位置

    // 洞在 high 上
    while (low < high && a[low] <= part_element)
      low++;
    if (low == high) break;
    a[high--] = a[low];
    // 因為是後綴的遞增，所以是先填完洞再移動到 high 的位置
  }

  a[low] = part_element;
  return low;
  // 這邊用 low 與 high 是一樣的
  // 因為兩個在這邊都已經是等於了
}
```

###### 2. 我的第一版程式（split 測試）

- 第一次測試（錯誤）
	```c
	// sort an array of integers using Quicksort algorithm
	
	#include <stdio.h>
	#define N 4
	
	void quicksort(int a[], int low, int high);
	int split(int a[], int low, int high);
	
	int main(void)
	{
	  int a[N] = {3, 2, 1, 5};
	  // 假數字，用於測試
	
	  split(a, 0, N - 1);
	
	  for (int i = 0; i < N; i++)
	    printf("%d", a[i]);
	  printf("\n");
	}
	
	int split(int a[], int low, int high)
	{
	  int base_value;
	
	  base_value = a[low];
	  for (;;) {
	    // 移動 high
	    while (low <= high && a[high] >= base_value)
	      high--;
	    if (low == high) break;
	    a[low++] = a[high];
	
	    // 移動 low
	    while (low <= high && a[low] <= base_value)
	      low++;
	    if (low == high) break;
	    a[high--] = a[low];
	  }
	
	    return 0;
	}
	```

- 修正過後
	```c
	// sort an array of integers using Quicksort algorithm
	
	#include <stdio.h>
	#define N 4
	
	void quicksort(int a[], int low, int high);
	int split(int a[], int low, int high);
	
	int main(void)
	{
	  int a[N] = {3, 2, 1, 5};
	  // 假數字，用於測試
	
	  split(a, 0, N - 1);
	
	  for (int i = 0; i < N; i++)
	    printf("%d", a[i]);
	  printf("\n");
	}
	
	int split(int a[], int low, int high)
	{
	  int base_value;
	
	  base_value = a[low];
	  for (;;) {
	    // 移動 high
	    while (low < high && a[high] >= base_value)
	    // 修正點1：如果等於的話應該就要執行 break 才對
	      high--;
	    if (low >= high) break;
	    // 修正點2：low 有可能跟 high 剛好交叉
	    a[low++] = a[high];
	
	    // 移動 low
	    while (low < high && a[low] <= base_value)
	    // 修正點3：如果等於的話應該要執行 break 才對
	      low++;
	    if (low >= high) break;
	    // 修正點4：low 有可能與 high 剛好交叉
	    a[high--] = a[low];
	  }
	
	    a[low] = base_value;
	    // 修正點5：將最後的洞填滿
	    return 0;
	}
	```

###### 3. 我的第二版測試（加上 quicksort）

- 這一次未報錯
	```c
	// sort an array of integers using Quicksort algorithm
	
	#include <stdio.h>
	#define N 7
	
	void quicksort(int a[], int low, int high);
	int split(int a[], int low, int high);
	
	int main(void)
	{
	  int a[N] = {12, 3, 6, 18, 7, 15, 10};
	  // 假數字，用於測試
	
	  quicksort(a, 0, N - 1);
	
	  for (int i = 0; i < N; i++)
	    printf("%d ", a[i]);
	  printf("\n");
	}
	
	void quicksort(int a[], int low, int high)
	{
	  int middle;
	
	  if (high <= low) return;
	  middle = split(a, low, high);
	  quicksort(a, low, middle - 1);
	  quicksort(a, middle + 1, high);
	}
	
	int split(int a[], int low, int high)
	{
	  int base_value;
	
	  base_value = a[low];
	  for (;;) {
	    // 移動 high
	    while (low < high && a[high] >= base_value)
	    // 修正點1：如果等於的話應該就要執行 break 才對
	      high--;
	    if (low >= high) break;
	    // 修正點2：low 有可能跟 high 剛好交叉
	    a[low++] = a[high];
	
	    // 移動 low
	    while (low < high && a[low] <= base_value)
	    // 修正點3：如果等於的話應該要執行 break 才對
	      low++;
	    if (low >= high) break;
	    // 修正點4：low 有可能與 high 剛好交叉
	    a[high--] = a[low];
	  }
	
	    a[low] = base_value;
	    // 修正點5：將最後的洞填滿
	    return low;
	}
	```

###### 4. 最終的程式

```c
// sort an array of integers using Quicksort algorithm

#include <stdio.h>
#define N 10

void quicksort(int a[], int low, int high);
int split(int a[], int low, int high);

int main(void)
{
  int a[N];

  printf("Enter 10 numbers to be sorted: ");
  for (int i = 0; i < N; i++)
    scanf("%d", &a[i]);

  quicksort(a, 0, N - 1);

  for (int i = 0; i < N; i++)
    printf("%d ", a[i]);
  printf("\n");
}

void quicksort(int a[], int low, int high)
{
  int middle;

  if (high <= low) return;
  middle = split(a, low, high);
  quicksort(a, low, middle - 1);
  quicksort(a, middle + 1, high);
}

int split(int a[], int low, int high)
{
  int base_value;

  base_value = a[low];
  for (;;) {
    // 移動 high
    while (low < high && a[high] >= base_value)
    // 修正點1：如果等於的話應該就要執行 break 才對
      high--;
    if (low >= high) break;
    // 修正點2：low 有可能跟 high 剛好交叉
    a[low++] = a[high];

    // 移動 low
    while (low < high && a[low] <= base_value)
    // 修正點3：如果等於的話應該要執行 break 才對
      low++;
    if (low >= high) break;
    // 修正點4：low 有可能與 high 剛好交叉
    a[high--] = a[low];
  }

    a[low] = base_value;
    // 修正點5：將最後的洞填滿
    return low;
}

```
<br><br>

## Programming project

### Proj.1: 將數字從小排到大

- 由於這一個 program 在寫的時候才剛學完 quicksort，導致我用了很複雜的寫法
- 所以在一次次的修正測試後我才選擇再寫了一個 version 2 ，用簡單的寫法再寫一次
- 也才有了這麼多版

#### 1. 第一版：測試單一一個 selection_sort

>[!bug]- 錯誤的 program
>```c
>// This is my program for programming project 1 
>// in C Programming: a modern approach
>// This program is used to sort 
>// a series of integers form low to high
>
>#include <stdio.h>
>#define N 4
>
>void selection_sort(int a[], int n);
>
>int main(void)
>{
>  int a[N] = {1, 8, 2, 7};
>  // 假數字，測試用
>
>  selection_sort(a, N);
>
>  for (int i = 0; i < N; i++)
>    printf("%d", a[i]);
>  printf("\n");
>
>  return 0;
>}
>
>void selection_sort(int a[], int n)
>{
>  int base_value = a[0];
>  int compare_num = n - 1;
>
>  while (compare_num > 0) {
>    while (a[compare_num] <= base_value)
>      compare_num--;
>    base_value = a[compare_num--];
>  }
>  a[compare_num] = a[n - 1];
>  a[n - 1] = a[compare_num];
>}
>```

>[!failure]- output
>```
>$ ./programming-project_Ch9_1 
>7827
>```

>[!success]- 修正過後的 program
>```c
>// This is my program for programming project 1 
>// in C Programming: a modern approach
>// This program is used to sort 
>// a series of integers form low to high
>
>#include <stdio.h>
>#define N 4
>
>void selection_sort(int a[], int n);
>
>int main(void)
>{
>  int a[N] = {1, 8, 2, 7};
>  // 假數字，測試用
>
>  selection_sort(a, N);
>
>  for (int i = 0; i < N; i++)
>    printf("%d", a[i]);
>  printf("\n");
>
>  return 0;
>}
>
>void selection_sort(int a[], int n)
>{
>  int base_value = a[0], hollow = 0;
>  int compare_num = n - 1;
>
>  while (compare_num > 0) {
>    while (a[compare_num] <= base_value)
>      compare_num--;
>    hollow = compare_num;
>    // 修正點：迴圈結束時 compare_num 會等於 0
>    // 所以需要新的變數來儲存洞的位置
>    base_value = a[compare_num--];
>  }
>  a[hollow] = a[n - 1];
>  a[n - 1] = base_value;
>  // 修正點：最後一格的位置要填的是最大的數字
>}
>```

>[!success]- output
>```
>$ ./programming-project_Ch9_1 
>1728
>```
<br>

#### 2. 第二版：加入遞迴

>[!bug]- 錯誤的 program
>```c
>// This is my program for programming project 1 
>// in C Programming: a modern approach
>// This program is used to sort 
>// a series of integers form low to high
>
>#include <stdio.h>
>#define N 7
>
>void selection_sort(int a[], int n);
>
>int main(void)
>{
>  int a[N] = {1, 8, 2, 7, 3, 5, 6};
>  // 假數字，測試用
>
>  selection_sort(a, N);
>
>  for (int i = 0; i < N; i++)
>    printf("%d", a[i]);
>  printf("\n");
>
>  return 0;
>}
>
>void selection_sort(int a[], int n)
>{
>  int base_value = a[0], hollow = 0;
>  int compare_num = n - 1;
>
>  while (compare_num > 0) {
>    while (a[compare_num] <= base_value)
>      compare_num--;
>    hollow = compare_num;
>    // 修正點：迴圈結束時 compare_num 會等於 0
>    // 所以需要新的變數來儲存洞的位置
>    base_value = a[compare_num--];
>  }
>  a[hollow] = a[n - 1];
>  a[n - 1] = base_value;
>  // 修正點：最後一格的位置要填的是最大的數字
>
>  if (n <= 0 ) return;
>  selection_sort(a, n - 1);
>}
>```

- output:
	```
	$ ./programming-project_Ch9_1 
	程式記憶體區段錯誤
	```

>[!success]- 修正後的 program
>```c
>// This is my program for programming project 1 
>// in C Programming: a modern approach
>// This program is used to sort 
>// a series of integers form low to high
>
>#include <stdio.h>
>#define N 7
>
>void selection_sort(int a[], int n);
>
>int main(void)
>{
>  int a[N] = {1, 8, 2, 7, 3, 5, 6};
>  // 假數字，測試用
>
>  selection_sort(a, N);
>
>  for (int i = 0; i < N; i++)
>    printf("%d ", a[i]);
>  printf("\n");
>
>  return 0;
>}
>
>void selection_sort(int a[], int no_element)
>{
>  int base_value = a[0], hollow = 0;
>  int compare_num = no_element - 1;
>
>  while (compare_num > 0) {
>    while (compare_num > 0 && a[compare_num] <= base_value)
>    // 修正點：有可能在內層就達到 0
>      compare_num--;
>    if (compare_num == 0) break;
>    // 修正點：如果 compare_num 等於 0 的話就不應該更新數值
>    hollow = compare_num;
>    // 修正點：迴圈結束時 compare_num 會等於 0
>    // 所以需要新的變數來儲存洞的位置
>    base_value = a[compare_num--];
>  }
>  a[hollow] = a[no_element - 1];
>  a[no_element - 1] = base_value;
>  // 修正點：最後一格的位置要填的是最大的數字
>
>  if (no_element <= 2) return;
>  selection_sort(a, no_element - 1);
>}
>```
- output:
	```
	$ ./programming-project_Ch9_1 
	1 2 3 5 6 7 8 
	```

<br>

#### 3. version 1: 最終板，加入數字輸入

- 增加了輸入數字的部份
- 學習重點：
	1. 要用 VLA 的話必須建立在已知元素個數的狀況，也就是**使用者要先輸入他要幾個數字**
	2. 面對完全不知道元素個數的狀況，要先做一個大的陣列，接下來輸入第一個數字，再用 getchar 來探測下一個 program

>[!success]- program
>```c
>// This is my program for programming project 1 
>// in C Programming: a modern approach
>// This program is used to sort 
>// a series of integers form low to high
>
>#include <stdio.h>
>#define MAX_LEN 100
>
>void selection_sort(long a[], int n);
>
>int main(void)
>{
>  int n = 0;
>  long a[MAX_LEN];
>  char ch;
>
>  printf("Eneter a series of integers: ");
>  do {
>    scanf("%ld", &a[n]);
>    n++;
>    ch = getchar();
>    // 先掃描下一個數字
>    if (ch == '\n') break;
>    // 測試下一個字元是否為 '\n'
>    // 是的話就結束
>  } while (n <= MAX_LEN);
>
>  selection_sort(a, n);
>
>  for (int i = 0; i < n; i++)
>    printf("%ld ", a[i]);
>  printf("\n");
>
>  return 0;
> }
>
> void selection_sort(long a[], int no_element)
> {
>  int base_value = a[0], hollow = 0;
>  int compare_num = no_element - 1;
>
>  while (compare_num > 0) {
>    while (compare_num > 0 && a[compare_num] <= base_value)
>    // 修正點：有可能在內層就達到 0
>      compare_num--;
>    if (compare_num == 0) break;
>    // 修正點：如果 compare_num 等於 0 的話就不應該更新數值
>    hollow = compare_num;
>    // 修正點：迴圈結束時 compare_num 會等於 0
>    // 所以需要新的變數來儲存洞的位置
>    base_value = a[compare_num--];
>  }
>  a[hollow] = a[no_element - 1];
>  a[no_element - 1] = base_value;
>  // 修正點：最後一格的位置要填的是最大的數字
>
>  if (no_element <= 2) return;
>  selection_sort(a, no_element - 1);
>}
>```

#### 4. version 2: 重構程式

- 由於這個 program 實在太難讀了，且我自己覺得在排序的邏輯被 quicksort 的演算法影響到太多，所以我決定重構了這個程式

>[!success]- program
>```c
>// This is my program for programming project 1 
>// in C Programming: a modern approach
>// This program is used to sort 
>// a series of integers form low to high
>
>#include <stdio.h>
>#define MAX_LEN 100
>
>void selection_sort(long a[], int n);
>
>int main(void)
>{
>  int n = 0;
>  long a[MAX_LEN];
>  char ch;
>
>  printf("Eneter a series of integers: ");
>  do {
>    scanf("%ld", &a[n]);
>    n++;
>    ch = getchar();
>    if (ch == '\n') break;
>  } while (n <= MAX_LEN);
>
>  selection_sort(a, n);
>
>  for (int i = 0; i < n; i++)
>    printf("%ld ", a[i]);
>  printf("\n");
>
>  return 0;
>}
>
>void selection_sort(long a[], int n)
>{
>  int max_index;
>  long temp_num;
>
>  max_index = 0;
>  // 先假設 a[0] 是最大的
>
>  for (int i = 1; i < n; i++)
>    if (a[i] > a[max_index])
>      max_index = i;
>  // 掃描數字，將比較大的數字紀錄到 max_index 上
>
>  temp_num = a[max_index];
>  a[max_index] = a[n - 1];
>  a[n - 1] = temp_num;
>  // 交換數字
>
>  if (n <= 2) return;
>  selection_sort(a, n - 1);
>}
>```

<br>

### Proj.8：花旗骰遊戲

- 我是採用分段寫與分段測試的方式
- 所以以下是我的各個測試版，也就是這個 program 的每一個段落

#### 1. 第一版：骰骰子

- 這個測試一次就成功了

>[!success]- program
>```c
>// This is my program for programming project 8 
>// in C Programming: a modern approach
>// This program is used to 
>// simulates the game of craps
>
>#include <stdio.h>
>#include <stdbool.h>
>#include <stdlib.h>
>#include <time.h>
>
>int rool_dice(void);
>bool play_game(void);
>
>int main(void)
>{
>  printf("%d\n", rool_dice());
>
>  return 0;
>}
>
>int rool_dice(void)
>{
>  int sum = 0;
>
>  srand((unsigned) time(NULL));
>  // 設定隨機書的開頭頁數
>
>  for (int i = 0; i < 2; i++ ) {
>    sum += ( (rand() % 6) + 1 );
>  }
>
>  return sum;
>}
>```

<br>

#### 2. 第二版：玩一次的花旗骰

- 這次的錯誤是我將 `srand((unsigned) time(NULL))` (也就是將數字依據時間洗牌)的位置放錯了
- 這行程式從頭到尾都只需要執行一次，因為如果每一次都重新洗牌的話時間都會是一樣的，導致數字永遠都從第一個開始且第一個數字都一樣 (因為是依據時間來排)，而不會輪到後面的數字


>[!bug]- 錯誤的 program
>```c
>// This is my program for programming project 8 
>// in C Programming: a modern approach
>// This program is used to simulates the game of craps
>
>#include <stdio.h>
>#include <stdbool.h>
>#include <stdlib.h>
>#include <time.h>
>
>int rool_dice(void);
>bool play_game(void);
>
>int main(void)
>{
>  if (play_game())
>    printf("You win!!!\n");
>  else
>    printf("You lose!!!\n");
>
>  return 0;
>}
>
>bool play_game(void)
>{
>  int point, num;
>
>  num = rool_dice();
>  printf("You rolled: %d\n", num);
>  if (num == 7 || num == 11)
>    return true;
>  else if (num == 2 || num == 3 || num == 12)
>    return false;
>  else {
>    point = num;
>    printf("Your point is %d\n", point);
>    for (;;) {
>      num = rool_dice();
>      printf("You rolled %d\n", num);
>      if (num == point) return true;
>      if (num == 7) return false;
>    }
>  }
>}
>
>int rool_dice(void)
>{
>  int sum = 0;
>
>  srand((unsigned) time(NULL));
>  // 設定隨機書的開頭頁數
>
>  for (int i = 0; i < 2; i++ ) {
>    sum += ( (rand() % 6) + 1 );
>  }
>
>  return sum;
>}
>```

>[!failure]- output
>Julian119@mx:~/常用/程式/C學習<br>
>$ ./programming-project_Ch9_8<br>
>You rolled: 4<br>
>Your point is 4<br>
>You rolled 4<br>
>You win!!!<br>
>\**錯誤點： point 與骰到的數字一模一樣

>[!success]- 修正後的 program
>```c
>// This is my program for programming project 8 
>// in C Programming: a modern approach
>// This program is used to simulates the game of craps
>
>#include <stdio.h>
>#include <stdbool.h>
>#include <stdlib.h>
>#include <time.h>
>
>int roll_dice(void);
>bool play_game(void);
>
>int main(void)
>{
>  srand((unsigned) time(NULL));
>  // 修正：整個程式中只需要重新洗牌亂數表一次
>  // 如果一直洗牌就會因為頁數都相同導致數字一樣
>  // (因為程式執行很快，導致時間相同，頁數也相同)
>
>  if (play_game())
>    printf("You win!!!\n");
>  else
>    printf("You lose!!!\n");
>
>  return 0;
>}
>
>bool play_game(void)
>{
>  int point, num;
>
>  num = roll_dice();
>  printf("You rolled: %d\n", num);
>  if (num == 7 || num == 11)
>    return true;
>  else if (num == 2 || num == 3 || num == 12)
>    return false;
>  else {
>    point = num;
>    printf("Your point is %d\n", point);
>    for (;;) {
>      num = roll_dice();
>      printf("You rolled %d\n", num);
>      if (num == point) return true;
>      if (num == 7) return false;
>    }
>  }
>}
>
>int roll_dice(void)
>{
>  int sum = 0;
>
>  for (int i = 0; i < 2; i++ ) {
>    sum += ( (rand() % 6) + 1 );
>  }
>
>  return sum;
>}
>```

>[!success]- 正確的 output
>You rolled: 8<br>
Your point is 8<br>
You rolled 10<br>
You rolled 8<br>
You win!!!<br>

<br>

#### 3. 最終版：玩多次的花旗骰並計數

- 這次的錯誤在由於 getchar 的特性導致換行符會被讀進去
- 所以我加上了 `while (getchar() != '\n');` 讓它一直吃掉其他數字直到換行符出現

>[!bug]- 錯誤的 program
>```c
>// This is my program for programming project 8 
>// in C Programming: a modern approach
>// This program is used to simulates the game of craps
>
>#include <stdio.h>
>#include <stdbool.h>
>#include <stdlib.h>
>#include <time.h>
>#include <ctype.h>
>
>int roll_dice(void);
>bool play_game(void);
>
>int main(void)
>{
>  int no_win = 0, no_lose = 0;
>  char answer;
>
>  srand((unsigned) time(NULL));
>  // 修正：整個程式中只需要重新洗牌亂數表一次
>  // 如果一直洗牌就會因為頁數都相同導致數字一樣
>  // (因為程式執行很快，導致時間相同，頁數也相同)
>
>  do {
>    if (play_game()) {
>      printf("You win!!!\n");
>      no_win++;
>    }
>    else {
>      printf("You lose!!!\n");
>      no_lose++;
>    }
>
>    printf("\nPlay again? ");
>    answer = getchar();
>    printf("\n");
>    if (toupper(answer) == 'N') break;
>  } while (1);
>
>  printf("Wins: %d", no_win);
>  printf("  ");
>  printf("Losses: %d\n", no_lose);
>
>  return 0;
>}
>
>bool play_game(void)
>{
>  int point, num;
>
>  num = roll_dice();
>  printf("You rolled: %d\n", num);
>  if (num == 7 || num == 11)
>    return true;
>  else if (num == 2 || num == 3 || num == 12)
>    return false;
>  else {
>    point = num;
>    printf("Your point is %d\n", point);
>    for (;;) {
>      num = roll_dice();
>      printf("You rolled %d\n", num);
>      if (num == point) return true;
>      if (num == 7) return false;
>    }
>  }
>}
>
>int roll_dice(void)
>{
>  int sum = 0;
>
>  for (int i = 0; i < 2; i++ ) {
>    sum += ( (rand() % 6) + 1 );
>  }
>
>  return sum;
>}
>```

>[!failure]- output
>$ ./programming-project_Ch9_8 <br>
>You rolled: 10<br>
>Your point is 10<br>
>You rolled 7<br>
>You lose!!!<br>
><br>
>Play again? y<br>
><br>
>You rolled: 5<br>
>Your point is 5<br>
>You rolled 5<br>
>You win!!!<br>
><br>
>Play again? <br>
>You rolled: 6<br>
>Your point is 6<br>
>You rolled 8<br>
>You rolled 10<br>
>You rolled 4<br>
>You rolled 7<br>
>You lose!!!<br>
><br>
>Play again? n<br>
><br>
>Wins: 1  Losses: 2

>[!success]- 修正後的 program
>```c
>// This is my program for programming project 8 
>// in C Programming: a modern approach
>// This program is used to simulates the game of craps
>
>#include <stdio.h>
>#include <stdbool.h>
>#include <stdlib.h>
>#include <time.h>
>#include <ctype.h>
>
>int roll_dice(void);
>bool play_game(void);
>
>int main(void)
>{
>  int no_win = 0, no_lose = 0;
>  char answer;
>
>  srand((unsigned) time(NULL));
>  // 修正：整個程式中只需要重新洗牌亂數表一次
>  // 如果一直洗牌就會因為頁數都相同導致數字一樣
>  // (因為程式執行很快，導致時間相同，頁數也相同)
>
>  do {
>    if (play_game()) {
>      printf("You win!!!\n");
>      no_win++;
>    }
>    else {
>      printf("You lose!!!\n");
>      no_lose++;
>    }
>
>    printf("\nPlay again? ");
>    answer = getchar();
>    while (getchar() != '\n');
>    // 一直吃掉剩下的數字直到換行符出現
>    printf("\n");
>    if (toupper(answer) == 'N') break;
>  } while (1);
>
>  printf("Wins: %d", no_win);
>  printf("  ");
>  printf("Losses: %d\n", no_lose);
>
>  return 0;
>}
>
>bool play_game(void)
>{
>  int point, num;
>
>  num = roll_dice();
>  printf("You rolled: %d\n", num);
>  if (num == 7 || num == 11)
>    return true;
>  else if (num == 2 || num == 3 || num == 12)
>    return false;
>  else {
>    point = num;
>    printf("Your point is %d\n", point);
>    for (;;) {
>      num = roll_dice();
>      printf("You rolled %d\n", num);
>      if (num == point) return true;
>      if (num == 7) return false;
>    }
>  }
>}
>
>int roll_dice(void)
>{
>  int sum = 0;
>
>  for (int i = 0; i < 2; i++ ) {
>    sum += ( (rand() % 6) + 1 );
>  }
>
>  return sum;
>}
>```

>[!success]- output
>You rolled: 5<br>
>Your point is 5<br>
>You rolled 6<br>
>You rolled 8<br>
>You rolled 8<br>
>You rolled 4<br>
>You rolled 5<br>
>You win!!!<br>
><br>
>Play again? y<br>
><br>
>You rolled: 10<br>
>Your point is 10<br>
>You rolled 4<br>
>You rolled 7<br>
>You lose!!!<br>
><br>
>Play again? n<br>
><br>
>Wins: 1  Losses: 1