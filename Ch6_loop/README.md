# C program: a modern approach Ch.6 note
## Program overview


| 題號                   | 功能                               | 觀念                                          | 連結                                      |
| -------------------- | -------------------------------- | ------------------------------------------- | --------------------------------------- |
| 範例一                  | 顯示 1 到輸入的數字的平方 (while statement) | 用 while statement 由小排序到大                    | [view](./square.c)                      |
| 範例二                  | 加總一連串輸入的數字                       | 用 while statement 加總數字                      | [view](./sum.c)                         |
| 範例三                  | 計算整數的位數                          | 判斷用 do 還是 while statement                   | [view](./numdiogits.c)                  |
| 範例四                  | 顯示 1 到輸入的數字的平方 (for statement)   | 將 while 改成 for statement                    | [view](./square2.c)                     |
| 範例四v2                | 同上                               | 同一個 program 有不同種打法                          | [view](square3.c)                       |
| 範例五                  | 計算收支的平衡                          | 綜和利用 for if switch break continue statement | [view](./checking.c)                    |
| project  2 version 1 | 找尋最大公因數                          | 利用 for statement 與暴力破解法直接找出最大公因數            | [view](./programming-project_Ch6_2v1.c) |
| project 2 version 2  | 同上                               | 將 version 1 的 program 修改到更易讀                | [view](./programming-project_Ch6_2v2.c) |
| project 2 version 3  | 同上                               | 利用歐基里得演算法求出最大公因數                            | [view](./programming-project_Ch6_2v3.c) |
| project 4            | 修改 broker.c                      | 用無限迴圈寫出可重複執行的 program                       | [view](./programming-project_Ch6_4.c)   |
| project 6            | 顯示出 1 到 n 中偶數的平方                 | 用 for statement 去寫出 loop                    | [view](./programming-project_Ch6_6.c)   |
| project 8            | 顯示出日曆                            | 綜和利用 for 和 if statement 去顯示出日曆              | [view](./programming-project_Ch6_8v1.c) |
| project 8 version 2  | 同上                               | 修改以上的 program 的邏輯                           | [view](./programming-project_Ch6_8v2.c) |
<br><br>

---
## Note
#### I. loope 介紹

- loop 的作用：反覆執行 statement。
- 當 controlling expression 為真，則執行 statement，重複執行這兩個動作
- loop body: 被重複執行的 statement
- loop 大致有以下三種：
	1. while statement
	2. do statement
	3. for statement

#### II. The while Statement

###### 一，while statement

- 用途：**先測試 expression ，再執行 loop body**，也就是可能執行 0 次。當 expression 為真時，就執行 loop body，**直到測試到 expression 為假時**
- form:
	```c
	while ( expression ) statement
	```
	- **在 loop body 與 () 之間沒有任何東西**
	- E.g:
		```c
		while (i < n)  // controlling expression
		  i = i * 2    // loop body
		```
- 一樣可以用 `{ }` 來執行 compound statement<br>E.g:
	```c
	i = 10
	while (i > 0) {
	  printf("T minus %d and counting\n", i)
	  i --;
	}
	```

<br>

###### 二，Infinite Loops

- 可以藉由在 expression 寫出恆成立的算式，來寫出無限的迴圈
- 它會一直執行直到有包含可以轉移出去的 statement （例如裡面有包含 `break` `goto` `return`）<br>E.g:
	```c
	while (1) ...
	```

<br>

###### 三，範例一： Printing a Table of Squares

- program:
	```c square.c
	#include <stdio.h>
	
	int main(void)
	{
	    int i, n;
	
		printf("This program prints a table of squares.\n");
	    printf("Enter number of entries in table: ");
	    scanf("%d", &n);
	
	    i = 1;
	    while (i <= n) {
	      printf("%10d%10d\n", i, i * i );
	      i++;
	    }
	
	    return 0;
	}
	```
- output:
	```
	This program prints a table of squares.
	Enter number of entries in table: 8
	         1         1
	         2         4
	         3         9
	         4        16
	         5        25
	         6        36
	         7        49
	         8        64
	```
	- 由小排到大：先指派 i 為 1，再判斷 i <= n，如果成立就顯示 i i\*i，然後再加一，重複執行

###### 四，範例二： Summing a Series of Numbers

- program:
	```c sum.c
	#include <stdio.h>
	
	int main(void)
	{
	    int n, sum = 0;
	
	    printf("This program sums a series of intgers.\n");
	    printf("Enter integers (0 to terminate) : ");
	
	    scanf("%d", &n);
	    while (n != 0) {
	      sum += n;
	      scanf("%d", &n);
	    }
	    printf("The sum is: %d\n", sum);
	
	    return 0;
	}
	```
- output:
	```
	This program sums a series of intgers.
	Enter integers (0 to terminate) : 8 24 5 3 79 85 0
	The sum is: 204
	```
	- 重點：
		1. 在 `printf` 後的下一個 statement 一定要是 `scanf` 才可以輸入值。不可以直接接 `while`，否則就不能輸入值
		2. 不一定要用兩個 variable 相加，也可以直接用一個 variable 再搭配 compound assignmen 來累計計算就可

<br><br>

---
#### III. The do Statement

###### 一，do statement

- 意思：與 while statement 很像，只是差在他是**先執行 statement 再判斷 expression**，所以至少會執行一次
- form:
	```c
	do statement while ( expression )
	```
	- 建議在用 do statement 的時候**一律在 loop body 加上 {}**，以防止將後面的 while 認成 while statement
- E.g:
	```c
	i = 10;
	do {
	  printf("T minus %d and counting\n", i);
	  --i;
	} while (i > 0);
	```

<br>

###### 範例三： Calculating the Number of Digits in an Integer

- program
	```c numdigits.c
	#include <stdio.h>
	
	int main(void)
	{
	    int num, times = 0;
	
	    printf("Enter a nonnegative integer: ");
	    scanf("%d", &num);
	
	    do {
	      num /= 10;
	      ++times;
	    } while (num != 0);
	
	    printf("The number has %d ", times);
	    if (times != 1)
	      printf("digits");
	    else
	      printf("digit");
	    printf(".\n");
	
	    return 0;
	} 
	```
	- 判斷要用 do statement 還是 while statement： 看它是不是要**至少執行一次**
	- 我自己增加了一個 if statement 來判斷是否在 digit 上加 s

<br><br>

#### IV. The for Statement

###### 一，for statement

- 用途：在要**遞增或遞減的計數**的時候很好用，但也有除此之外的許多用途
- form:
	```c
	for ( expr1 ; expr2 ; expr3 ) statement
	```
	等價於將 expr1 放在 while statment 之外執行
	```c
	expr1;
	while ( expr2 ) {
	  statement
	  expr3;
	}
	```
	- 先執行 expr1 ，再判斷 expr2 是否為真，是的話就執行 statement 再執行 expr3 接著回到 expr2
	- expr1 為 initialization step，只有執行一次
	- expr2 控制 loop temination，用來檢測是否為真
	- expr3 為執行完 statement 後所執行的 expression
	- E.g:
		```c
		for (i = 10; i > 0; i--)
		  printf("Tminus %d and counting\n", i);
		```
		- 先執行 `i = 10` ，因為 `i > 0` 為真所以執行 `printf("Tminus %d and counting\n", i);` 接著再執行 `i--` ，再回到判斷 `i > 0`，直到 `i > 0` 為假

<br>

###### 二，Idioms

- 在計數時常用的語法：
	1. 從 0 到 n - 1
		```c
		for (i = 0; i < n; i++) ...
		```
	2. 從 1 到 n
		```c
		for (i = 1; i <= n; i++) ...
		```
	3. 從 n - 1 到 0
		```c
		for (i = n - 1; i >= 0; i--) ...
		```
	4. 從 n 到 1
		```c
		for (i = n; i > 0; i--) ...
		```
- 以下為計數時常犯的錯
	- **在 expr2 中的大小於用錯方向**，當要往上數時要在 expr2 中用 < 或 <=，反之則是 > 或 >=
	- **在 expr2 中不要用 \==**，因為用 \== 的話在還沒到臨界點時就會直接判定為假而停下來
	- "Off-by-one" errors，就是要用 i <= n 的時候用 i < n，導致結果差一

<br>

###### 三，Ommitting Expressions in a for Statement

- expression 都是可選擇的要或不掉的<br>E.g:
	1. 
		```c
		i = 10;
		for (;i > 0; --i)
		  printf("T minus %d and counting\n", i);
		```
	2. 
		```c
		for (i = 10; i > 0;)
		  printf("T minus %d and counting\n", i);
		```
	3. 
		```c
		for (; i > 0;)
		  printf("T minus %d and counting\n", i--);
		```
		等價於
		```c
		while (i > 0)
		  printf("T minus %d and counting\n", i--);
		```
	4. 也可以全部的 expression 都不打，就變成 infinite loop
		```c
		for (;;)
		  printf("T minus %d and counting\n", i--);
		```
		- **注意：**
			1. 就算 expr1 與 expr3 可以不打，**但 ; 一定要打**
			2. 如果 expr1 和 expr3 都不打的話，用 while statement 就好

<br>

###### 四， for Statements in C99

- 在 C99 內， **expr1 可以被 declaration 取代**，但該 variable **只能夠在這個 loop 內使用**
- 就算原本就有同樣的 variable，它也會創建一個只有該 loop 可用的 variable，原本的 variable ，會繼續存在
- 在裡面單獨宣告 variable 可以使 program 更容易閱讀
- E.g:
	1. variable 只能夠用在 loop 內 
		```c
		for (int i = 0; i) {
		  ...
		  printf("%d", i); // 正確的 
		  ...
		}
		printf("%d", i);  // 錯誤， i 只能用在 loop 內
		```
	2. 也可以同時宣告兩個以上的 variable ，只要這兩個是屬於同一種 variable
		```c
		for (int i = 0, j = 0; i < n; i++)
		```

<br>

###### 五，The Comma Operator

- 用途：將多個 expression 合成成一個 expression，可以用在只能放一個 expression 的部份
- form:
	```c
	expr1, expr2
	```
	- expr1 會先被運算，然後丟棄，接著再算 expr2
	- 通常 expr1 都會有 side effect，不然用 expr1 就沒有任何意義
	- E.g:
		```c
		int i = 1, j = 5
		++i, i + j
		```
		++i 先被計算，再算 i + j，所以這個 expression 的值為 7，而 i 的值當然為 2
- conna operator 的 precedence 是全部 operator 中最低的
- E.g:
	```
	for (sum = 0, i = 1; i <= N; i++)
	  sum += 1
	```

<br>

###### 六，範例四：Printing a Table of Squares (Revisited)

- program1:
	```c square2.c
	// Prints a table of squares using a for statement
	
	#include <stdio.h>
	
	int main(void)
	{
	    int i, n;
	
	    printf("This program prints a table of squares.\n");
	    printf("Enter number of entries in table: ");
	    scanf("%d", &n);
	
	    for (i = 1; i <= n; i++)
	      printf("%10d%10d\n", i, i * i);
	
	    return 0;
	}
	```
	- 記住 ( expr1; expr2; expr3) 與 statement 之間沒有 `;` 。我剛剛不小心多用了 ; 導致結果是錯的，但卻沒有報錯
- output:
	```
	This program prints a table of squares.
	Enter number of entries in table: 5
	         1         1
	         2         4
	         3         9
	         4        16
	         5        25
	```
- program2:
	```c square3.c
	// Prints a table of squares uing an odd method
	
	#include <stdio.h>
	
	int main(void)
	{
	  int i, n, odd, square;
	
	  printf("This program prints a table of squares.\n");
	  printf("Enter number of entries in table: ");
	  scanf("%d", &n);
	
	  i = 1;
	  odd = 3;
	  for (square = 1; i <= n; odd += 2) {
	    printf("%10d%10d\n", i, square);
	    ++i;
	    square += odd;
	  }
	
	  return 0;
	}
	```
	- 總而言之，program 不只有一種打法
- output:
	```
	This program prints a table of squares.
	Enter number of entries in table: 4
	         1         1
	         2         4
	         3         9
	         4        16
	```

<br><br>

#### V. Exiting from a Loop

###### 一，The break Statement

- 在 switch statement 的時候就有遇過，是用來中斷 statement 的
- 只能夠跳脫最內層的結構，而不會中斷整個程式
- E.g:
	1. 測試 n 是否為質數。跳出單一個 statement
		```c
		for (d = 2; d < n; d++)
		  if (n % d == 0)
		    break;
		if (d < n)
		  printf("%d is divisible by %d\n", n, d);
		else
		  printf("%d is prime\n", n);
		```
		- 當 n 可以被 d 整除時，就會跳出 if statement
	2. 在中間就結束 compound statement
		```c
		for (;;) {
		  printf("Enter a number (exter 0 to stop): ");
		  scanf("%d", &n);
		  if (n == 0)
		    break;
		  printf("%d cubed is %d\n", n, n * n * n);
		}
		```

<br>

###### 二，The continue Statement

- continue 只能夠被用在 loop 中
- continue 不會結束 loop ，而是直接結束這一輪，進到下一輪
- 如果是在 while statement 會進到下一輪條件測試，如果在 for statement 會先進行 expr3，再進到條件測試
- E.g: 
	```c
	n = 0;
	sum = 0;
	while (n < 10) {
	  scanf("%d", &i);
	  if (i == 0)
	    continue;
	  sum += i;
	  n++;
	  // continue 會跳到這裡，也就是 loop 的末端
	}
	```
	- 用途：讓使用者輸入一串數字，只加總其中的**非零數字**，直到成功加滿 10 個為止。如果使用者輸入 0，就跳過它，不計入次數，也不累加
	- 如果 i == 0 的話就會直接進到下一輪的 test

<br>

#### 三， The goto Statement

- 也是屬於 Jump statement
- 是用來跳到在 function 內任何的 statement 
- 但 `goto` 因為可以跳來跳去的特性使得它會讓 program 變得更難讀
- 是用 lable 來標注要跳到哪裡<br>lable 的 form:
	```c
	identifier : statement
	```
- 以及用 goto statement 來寫說此時要跳到 lable<br>goto statement 的 form:
	```c
	goto identifier ;
	```
- E.g:
	```c
	for (d = 2; d < n; d++)
	  if (n % d == 0)
	    goto done;
	
	done:
	if (d < n)
	  printf("%d is divisible by %d\n", n, d)
	else 
	  printf("%d is prime\n", n)
	```
- 雖然因為 `break`, `continue`, `return` 以及 `exit` 使得較少有地方會用到 `goto`，但如果要跳脫出多層的結構的話，`goto` 就會是好用的<br>E.g: 跳脫出 while 與 switch statement
	```c
	while (...) {
	  switch (...) {
	  ...
	  goto loop_done;
	  ...
	  }
	}
	loop_done: ...
	```

<br>

#### 四，範例五：Balancing a Checkbook

- [[C_Programming-A_Modern_Approach_ocr_Ch6.pdf#page=16|題目]]
- program:
	```c
	// Balance a checkbook
	
	#include <stdio.h>
	
	int main(void)
	{
	  int cmd;
	  float balance = 0.00f, credit, debit;
	
	  printf("*** ACME checkbook-balancing program ***\n");
	  printf("Commands: 0=clear, 1=credit, 2=debit, 3=balance, 4=exit\n");
	  printf("\n");
	
	
	
	  for (;;) {
	    printf("Enter command: ");
	    scanf("%d", &cmd);
	    if (cmd > 4 || cmd < 0) {
	      printf("Irregular command, please re-enter command\n");
	      continue;
	    }
	    else switch (cmd) {
	      case 0:  balance = 0;
	               credit = 0;
	               break;
	      case 1:  printf("Enter amount of credit: ");
	               scanf("%f", &credit);
	               balance += credit;
	               break;
	      case 2:  printf("Enter amount of debit: ");
	               scanf("%f", &debit);
	               balance -= debit;
	               break;
	      case 3:  printf("Current balance: $%.2f\n", balance);
	               break;
	      case 4:  goto exit;
	    }
	  }
	
	      exit: return 0;
	}
	```
- output:
	```
	Enter command: 6
	Irregular command, please re-enter command
	Enter command: 645465465Irregular command, please re-enter command
	Irregular command, please re-enter command
	Enter command: 1
	Enter amount of credit: 6481.21  
	Enter command: 1
	Enter amount of credit: 3546.88
	Enter command: 2
	Enter amount of debit: 6519873.1
	Enter command: 1
	Enter amount of credit: 68431976.5146
	Enter command: 3
	Current balance: $61922132.00
	Enter command: 4
	```

- 我自己增加了一個如果輸入的指令不在 0 到 4 之間的時候就顯示 「Irregular command, please re-enter command」的 if statement
- program 用途：計算總收支。當輸入 1 的時候就會請你輸入 credit，2 的時候就輸入 debit，3 的時候就顯示 balance，4 就離開，0 的話是清空目前的所有紀錄
- 寫 program 的想法:
	1. 在宣告的部份基本上我是先保留位置的，等到後面有要再寫上去
	2. 因為只有 balance 不是被輸入的，所以只有它用 initialize
	3. 因為要不斷的請使用者輸入 command，所以必須要用無限的 loop
	4. 在每一次的 loop 開端就要輸入 command
	5. 輸入完後再判斷 command 是否合規
	6. 如果不合規就先執行 `printf` 再用 `continue` 重新執行 loop
	7. 否則開始判斷輸入的 command 要採取什麼行動。也因如此才用 switch statement
	8. 在 command 為 4 的時候就用 `goto` 去跳脫 switch 與 for statement (因為有兩層，所以只能用 `goto`)

<br><br>

#### VI. The Null Statement

- 就是空的 statement<br>E.g:
	```c
	i = 0; ; j = 1;
	```
	這邊有三個 statement，而在兩個 ; 之間的就是 Null statement
- 用途：用在 loop body 為空的時候<br>E.g:
	```c
	for (d = 2; d < n; d++)
	  if (n % d == 0)
	    break;
	```
	如果將 if statement 合併在 for statement 就會變成
	```c
	for (d = 2; d < n && n % d != 0; d++);
	  // empty loop body
	```
	也就是說，如果 d < n && n % d != 0不成立就停止 loop，否則就繼續執行 d++ 與判斷式 (但沒有執行額外的 statement)

<br><br>

---
## Exercises

### Ex.1: while statement 的解讀
我的答案：
```
Ans: 1 2 4 8 16 32 64 128
Reason: 照著 while statement 的邏輯下去讀而已
```
<br>

### Ex.2: do statement 的解讀
我的答案：
```
Ans: 9384 938 93 9
Reason: 照著 do statement 的邏輯下去讀
```

<br>

### Ex.3: for satement 的解讀
我的答案：
```
Ans:5 4 3 2
Reason: 在判斷 i > 0, j > 0 的時候其實是判斷 j > 0，因為中間沒有 && 或 ||，所以導致了 i > 0 這的 expression 的結果被直接丟棄
```

<br>

### Ex.4: 判斷 for statement 的語意是否相同
我的答案：
```
Ans: (b)
Reason: 因為 i++ 是在 expr2 的位置，所以在執行 loop body 的時候會用 1 而不是 0
```
<br>

### Ex.5: 判斷 for, while, do statement 的意思
我的答案：
```
Ans: (c)
Reason: 因為 while 與 for statement 都是可能會執行 0 次的 loop body，但 do statement 是至少會執行一次
```
<br>

### Ex.6: 將 while statement 換成 for statement 
我的答案：
```c
for (i = 1; i <= 128; i *= 2)
  printf("%d", i);
```
<br>

### Ex.7: do statement 換成 for statement
我的答案：
1. program:
	```c
	for (i = 9384; i > 0; i /= 10)
	  printf("%d ", i);
	```
2. Reason:<br>雖然一般狀況下的 do statement 不能直接換過去 do statement，因為 do 會先至少執行一次。可是這一題恰好在一開始時就是為真，所以可以換過去
<br>

### Ex.8: for statement 的解讀--2
我的答案：
```
Ans:10 5 3 2 1
Reason: 因為 i 為 integer，所以會直接把小數部份捨去
```
<br>

### Ex.9: 將 for statement 換成 while statement
我的答案：
```c
i = 10;
while (i >= 1) {
  printf("%d ", i++);
  i /= 2;
}
```
<br>

### Ex.10: continue 換成 goto
我的答案：
```
Ans: 
	for (;;) {
	  ...
	  statement
	  goto : identifier
	  ...
	  identifier: ;
	}  

Reason: 將 identifier 放在 } 前，且 statement 的部份放 null statement 就可以了
```
<br>

### Ex.11:
我的答案：
```
Ans: 20
Reason: 照著 program 的順序讀下去，當 i % 2 為真（也就是非零的時候），就會進行下一輪的 loop ，但如果為假（也就是為 0），才會加到 sum 內
```
<br>

### Ex.12: 修改 for statement
我的答案：
```c
for (d = 2; (d * d) <= n; d++)
  if (n & d == 0)
    break;
```
<br>

### Ex.13: 修改 for statement--2
我的答案：
```c
for (n = 0; m > 0; m /= 2, n++) ;
```
<br>

### Ex.14: if statement 中的 null statement
我的答案：
- program:
	```c
	if (n != 0 && n % 2 == 0)
	  printf("n is even\n");
	```
- Reason:<br>因為 0 / 2 也是餘 0，且他在 if 後面多打了一個 ; ，導致產生了 null statement
<br><br>

---
## Programming Projects
### Proj.2: 找尋最大公因數

##### 一，program 的 version 解釋
1. version 1 為我最一開始在還沒看 Hint 時寫的 program，我是用暴力破解法去寫的
2. version 2 為我將 for 改成了 while statement，因為覺得在這裡用 while statement 會讓 program 更易讀
3. version 3 為我看了 Hint 後用歐基里得演算法去寫的
##### 二，program:
###### version 1
```c programming-project_Ch6_2v1.c
// This is my version 2 program for programming project 2 
// in C Programming: a modern approach Ch6
#include <stdio.h>

int main(void)
{
  int num1, num2, gcd;

  printf("Enter two integers: ");
  scanf("%d %d", &num1, &num2);

  if (num1 <= num2)
    gcd = num1;
  else
    gcd = num2;
  for (; num1 % gcd != 0 || num2 % gcd !=0; gcd--) ;

  printf("Greatest common divisor: %d\n", gcd);

  return 0;
}
```
###### version 2
```c
// This is my version 2 program for programming project 2 
// in C Programming: a modern approach Ch6

#include <stdio.h>

int main(void)
{
  int num1, num2, gcd;

  printf("Enter two integers: ");
  scanf("%d %d", &num1, &num2);

  if (num1 <= num2)
    gcd = num1;
  else
    gcd = num2;
  while (num1 % gcd != 0 || num2 % gcd != 0) {
    i--;
  }
  printf("Greatest common divisor: %d\n", gcd);

  return 0;
}
```
###### version 3
```c
// This is my version 3 program for programming project 2 
// in C Programming: a modern approach Ch6

#include <stdio.h>

int main(void)
{
  int m, n, remainder;

  printf("Enter two integers: ");
  scanf("%d %d", &m, &n);

  while (n != 0) {
    remainder = m % n;
    m = n;
    n = remainder;
  }

  printf("Greatest common divisor: %d\n", m);

  return 0;
}
```
##### 三，output
```
Enter two integers: 1000000007 999999937
Greatest common divisor: 1
```
##### 三，學習重點
1. 與 version 1 相比，在處理像 1000000007 與 999999937 這兩個大數字的時候，用演算法的速度確實和暴力破解法差很多
2. 雖然說用了歐基里得演算法，但我自己覺得在寫的時候很像自己只是照著 Hint 去寫，對於他的原理還不是很了解，但我覺得這還是一個好的嘗試，讓自己卻學習優化自己的 program

##### 四，補充資料
- [輾轉相除法 (維基百科)](https://zh.wikipedia.org/zh-tw/%E8%BC%BE%E8%BD%89%E7%9B%B8%E9%99%A4%E6%B3%95)
- [歐基里得演算法 (Jason Chen's Blog)](https://jason-chen-1992.weebly.com/home/-euclidean-algorithm)
<br>

### Proj.4: 修改 broker.c

##### 一，program
```c
// Calculates a broker's commision version 2
// This is my program for programming project 4 in 
// C Programming: a modern approach

#include <stdio.h>
#define percent 0.01f

int main(void)
{
    float commission, value;

    printf("0=exit\n");

    for (;;) {
      printf("Enter value of trade: ");
      scanf("%f", &value);
      if (value == 0.00f)
        break;
      else if (value < 2500.00f)
        commission = 30.00f + 1.7f * percent * value;
      else if (value < 6250.00f)
        commission = 56.00f + 0.66f * percent * value;
      else if (value < 20000.00f)
        commission = 76.00f + 0.34f * percent * value;
      else if (value < 50000.00f)
        commission = 100.00f + 0.22f * percent * value;
      else if (value < 500000.00f)
        commission = 155.00f + 0.11f * percent * value;
      else
        commission = 255.00f + 0.22f * percent * value;
      printf("Commission: $%.2f\n", commission);
      printf("\n");
      }

    return 0;
}
```
##### 二，output
```
0=exit
Enter value of trade: 350000
Commission: $540.00

Enter value of trade: 2468416
Commission: $5685.52

Enter value of trade: 8746
Commission: $105.74

Enter value of trade: 32135
Commission: $170.70

Enter value of trade: 13484
Commission: $121.85

Enter value of trade: 0
```
##### 三，學習重點
1. for statement 的位置要放對。我一開始的時候將 for 放在 `printf("Enter value of trade: ");` 與 `scanf("%f", &value);` 之後，導致輸入完第一次的 value 後 program 就瘋狂跳出 if statement 的結果，不讓我輸入新值
<br>

### Proj.6: 顯示出 1 到 n 中偶數的平方

##### 一，program
```c
// This is my program for programming project 6 in C Programming: a modern approach
// This is used to prompts the user to enter a number n,
// then prints all even squares between 1 and n

#include <stdio.h>

int main(void)
{
    int n, i;

    printf("Enter a number n: ");
    scanf("%d", &n);

    for (i = 2; i * i <= n; i += 2)
      printf("%d\n", i * i);

    return 0;
}
```
##### 二，output
```
Enter a number n: 245
4
16
36
64
100
144
196
```
<br>

### Proj.8: 顯示出日曆
##### 一，program

###### 版本介紹

1. version 1: 這是我自己一開始寫的 program
2. version 2: 我後來問了 AI 後它覺得用 `num_day--` 會導致程式像是空轉了一圈，邏輯上會有點不順。所以我將其改成了在顯示出日期後再判斷要不要換行
###### version 1
```c
// This is my program for programming project 8 in 
// C Program: a modern approach
// It is used to prints a one-month calendar

#include <stdio.h>

int main(void)
{
    int num_day, month_day, day_of_week;

    printf("Enter number of days in month: ");
    scanf("%d", &month_day);
    printf("Enter starting day of the week (1=Sun, 7=Sat): ");
    scanf("%d", &day_of_week);

    for (int i = 1; i != day_of_week; i++)
      printf("   ");
    for (num_day = 1; num_day <= month_day; num_day++, day_of_week++) {
      if (day_of_week != 8)
        printf("%2d ", num_day);
      else {
        printf("\n");
        day_of_week = 0;
        num_day--;
      }
    }
    printf("\n");

    return 0;
}
```
###### version 2
```c
// This is my program for programming project 8 in 
// C Program: a modern approach
// It is used to prints a one-month calendar

#include <stdio.h>

int main(void)
{
    int num_day, month_day, day_of_week;

    printf("Enter number of days in month: ");
    scanf("%d", &month_day);
    printf("Enter starting day of the week (1=Sun, 7=Sat): ");
    scanf("%d", &day_of_week);

    for (int i = 1; i != day_of_week; i++)
      printf("   ");
    for (num_day = 1; num_day <= month_day; num_day++, day_of_week++) {
      printf("%2d ", num_day);
      if (day_of_week == 7) {
        printf("\n");
        day_of_week = 0;
      }
    }
    printf("\n");

    return 0;
}
```
##### 二，output 
```
Enter number of days in month: 31
Enter starting day of the week (1=Sun, 7=Sat): 4
          1  2  3  4 
 5  6  7  8  9 10 11 
12 13 14 15 16 17 18 
19 20 21 22 23 24 25 
26 27 28 29 30 31 
```

##### 三，學到的東西

1. 這個 program 在寫的時候卡了一段時間，最後的時候我決定先寫出列出空格後的  for statement，因為這是我覺得我自己會寫的地方
2. 寫完空格後的 for statement 後，在列空格的地方我選擇了一樣用 for statement，並且加入了 i 作為計數的 variable，藉由這樣來控制要執行幾次的 loop
