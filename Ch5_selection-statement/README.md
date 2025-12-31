# C program: a modern approach Ch.5 note
<br>

## I. statement 種類

1. return statement (Ch2.2)
2. expression statement (Ch4.5)
3. Selection statement:<br>可以進行邏輯判斷並挑選的 statement。例如 if 和 switch statement
4. Iteration statement (loop):<br>可以不斷重複執行的 statement。例如 while, do, for statements
5. Jump statement:<br>可以無條件的跳轉到 program 的某一個地方的 statement。例如 break, continue, goto statement
6. compound statement:<br>就複合執行以上的 statement

<br><br>

---
## II. Logical expressions

- 用以**判斷 ture or false**。
- 當**答案為 ture 時會回傳 1**，當**答案為 false 時會回傳 0**。

#### 一，Relational Operators

- 用以判斷**大小關係**
- 符號及其意義:

	| Symblol | Meaning                  |
	| :-----: | :----------------------- |
	|    <    | less than                |
	|    >    | greater than             |
	|   <=    | less tnan or equal to    |
	|   <=    | greater than or equal to |
- 為 **left associative**
- 雖然可以連續使用，但要特別**注意他的 outcome, precedence, 與 associarive**<br>E.g:
	```
	i < j < k  等價於 (i < j) < k  (left associative)
	但 i < j 會先回傳 0 or 1，所以會變成 k 與 0 or 1 比大小
	
	如果要寫出數學意義上的 i < j < k 的話，要寫
	i < j && j < k
	```

<br>

#### 二，Equality Operators

- 用在判斷**是否相等**
- 符號及其意義:

	| Symbol | Meaning      |
	| :----: | ------------ |
	|   ==   | equal to     |
	|   !=   | not equal to |

>[!warning] 注意 
>等於是用兩個 =，一個 = 是 assignment

- 他的 **precedence 小於 relational operators**，且一樣是 **left associative**<br>E.g:
	```
	i < j == j < k  等價於  (i < j) == (j < k)
	只有當 i < j 且 j < k 皆成立或皆不成立時才會是對的
	```
- 也可以利用它會回傳 0 or 1 的特性去寫，但會使 program 很難讀，所以**不建議這樣做**。<br>E.g:
	```
	(i >= j) + (i == j) 
	看它回傳 0 or 1 or 2 就可以知道他是大於，小於，或等於。但這樣很難看懂
	```

<br>

#### 三，Logical Operators

- 用以**判斷 expression 的關係**
- 符號及其意義：

	| Symbol | Meaning                              |
	| :----: | ------------------------------------ |
	|   !    | logical negation (反面敘述，也就是 非 Q 則非 P) |
	|   &&   | logical and                          |
	|  \|\|  | logical or                           |
- 在 logical operator 內只要**非 0 就是 ture**，**只有 0 才是 false**<br>E.g:
	1. !expr:  當 expr 是 0 的時候會回傳 1 (! 會回傳反面的答案)
	2. expr1 && expr2: 當 expr1 和 expr2 皆為非 0 才會是 ture
	3. expr1 || expr2: 當 expr1 或 expr2 其中一個為非 0 時就會是 ture
- **先進行左側的 expression 再進行右側的 expression**。如果單看左側的就可以回答 ture or false ，就**不會再進行右側的 expression**，所以要小心 side effect 不一定會被執行<br>E.g:
	```
	1.
	(i != 0) && (j / i > 0)
	如果 i != 0 就不會考量 j / i 是否大於 0
	
	2.
	i > 0 && ++i > 0
	如果 i <= 0 則 side effect 不會發生。如果要讓 side effect 一定發生則要用
	++i > 0 && i > 0
	```
- **`!` 的 precedence 與 unary plus and minus operator 相同。而 `&&` 和 `||` 則是小於 relational and equality operators**
- **`!` 是 right associative 而 `&&` 和 `||` 是 left associative**

<br><br>

---
## III. The if Statement

<br>

#### 一，If Statement
- 用途：藉由 expression 來判斷後再執行 statement。可以想成如果 ... (expression 為真) 則 ... (執行 statement)
- expression 不用以 ; 結尾 (因為是 expression 而不是 statement)
- form:
	```if_statement
	if ( expression ) statement
	*括號為必要的
	```
- 當 **expression 為非零 (也就是 true) 時會執行該 statement**<br>E.g:
	```
	1.
	if (0 <= i && i < n) ...
	用以判斷 i 是否落在 0 到 n 之間
	
	1. 
	if (i < 0 || i >= n) ...
	用以判斷 i 是否落在 0 到 n 之外
	```

#### 二，Compound Statements

- 如果想要執行複數個 Statements 時就要用 `{ }`
- 在裡面的 statement 結尾依然要是 `;`
- form:
	```
	{ statements }
	```
- E.g:
	```
	if (line_num == MAX_LINES) {
	  line_num = 0;
	  page_num++;
	 }
	```

<br>

#### 三， The else Clause

- form
	```
	if ( expression ) statement1 else statement2
	```
- 每一個 statement 都要以 ; 結尾，但 expression 不用
- 可以想成如果(if) ...(expression 為真) 則 ...(執行 statement1) 否則(else) ...(執行 statement2)<br>E.g:
	```
	if (i > j)
	  max = i;
	else 
	  max = j;
	  
	如果 i > j 則 max = i 否則 max = j
	```
- 排版：
	1. expression 與 statement 都放在同一行 (statement 很短時可以用)<br>E.g:
		```
		if (i > j) max = i;
		else max = j; 
		```
	2. 在 statement 上縮排，且將每一組的 if else 對齊<br>E.g:
		```
		if (i > j)
		  if (i > k)
		    max = i;
		  else 
		    max = k;
		else
		  if (j > k)
		    max = j;
		  else
		   max = k;
		```
		也可以增加 `{ }` 使他們更易讀，且也可減低自己的錯誤機率<br>E.g:
		```
		if (i > j){
		  if (i > k)
		    max = i;
		  else 
		    max = k;
		} else {
		  if (j > k)
		    max = j;
		  else
		    max = k;
		}
		```
		有一些人也會在每個 if 的 statement  上都加 `{ }`<br>E.g:
		```
		if (i > j) {
		  if (i > k) {
		    max = i;
		  } else {
		    max = k;
		  }
		} else {
		  if (j > k) {
		    max = j;
		  } else {
		    max = k;
		  }
		}
		```

#### 四，Cascaded if Statements

- 也就是一連串的 if statements，用於測試一連串的條件，並執行 statement
- form:
	```
	if ( expression )
	  statement
	else if ( expression )
	  statement
	else if ( expression )
	  statement
	  .
	  .
	  .
	else ( expression )
	  statement
	```

<br>

#### 五，範例一：Calculating a Broker’s Commission

- program:
	```broker.c
	// Calculate a broker's commision
	
	#include <stdio.h>
	
	int main(void)
	{
	  float commission, value;
	
	  printf("Enter value of trade: ");
	  scanf("%f", &value);
	
	  if (value < 2500)
	    commission = 30 + value * 0.017;
	  else if (value < 6250)
	    commission = 56 + value * 0.0066;
	  else if (value < 20000)
	    commission = 76 + value + 0.0034;
	  else if (value < 50000)
	    commission = 100 + value * 0.0022;
	  else if (value < 500000)
	    commission = 155 + value * 0.0011;
	  else
    commission = 255 + value * 0.0009;
	
	  printf("Commission: %.2f\n",commission);
	
	  return 0;
	}
	```

>[!tip] 小技巧
>在寫連續的判斷的時候可以想著現在在的狀況是前一個 if 被否定之後的情況，這樣就不會寫出多餘的 expression 了