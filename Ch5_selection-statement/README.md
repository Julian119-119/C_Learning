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

#### 六， The "Dangling else" Problem

- 因為有多個 if statement 所以會導致 else 不知道是屬於哪個 if 
- 如果沒有特別用 `{ }` 的話 else 就會屬於最近的 if<br>E.g:
```
if (y != 0)
  if (x !=0)
    result = x / y;
else
  printf ("Error: y is equal to 0\n");
  
因為 else 是屬於最近的 if 所以他的意思應該是

if (y != 0)
  if (x !=0)
    result = x / y;
  else
    printf ("Error: y is equal to 0\n");
    
如果要照原本的意思的話就是要用 {}

if (y != 0) {
  if (x != 0)
    result = x / y
}  else
     printf("Error: y is equal to 0\n")
```

<br>

#### 七，Conditional  Expressions

- 特殊的 expression，意思與 if statement 很像，但他是 expression ，所以用法與 if statement 不一樣
- form:
	```
	expr1 ? expr2 : expr3
	```
- 讀作：如果 expr1 為真 (value 為 nonzero)，則用 expr2 否則就用 expr3
- 因為需要三個 operand 所以也被稱為 ternary operator
- 雖然它可以簡化 program ，但在許多時候會使 program 更難讀，所以盡量避免比較好，但也有例外，例如在 `printf` 與 `return` 內<br>E.g:
	```
	1.
	if (i > j)
	  return i;
	else 
	  return j;
	
	改成
	
	return i > j ? i : j;
	
	2.
	if (i > j)
	  printf("%d\n", i);
	else
	  printf('%d\n', j);
	  
	改成
	
	printf("%d\n",i > j ? i : j);
	```

<br>

#### 八，Boolean Values in C99

- Boolean value (布林值)，**只有 true or false 的一種值**，當 value = 1 時就是 true ， value = 0 時就是 false
- 在 C99 中，可以用 `_Bool` 來宣告。
- 雖然 boolean value 只有兩種值，但也可以指派它為其他 integer，只是當數字為非零時就只會儲存為 1<br>E.g:
	```
	_Bool flag;
	flag = 5;    
	// flag 被指派為 1
	```
- 可以利用**只要 value 為非零即為真**的特性來搭配 if statement 使用<br>E.g:
	```
	if (flag)
	 ...
	// 測試是否 flag 為 1
	```
- 在 C99 內**可以使用 <stdbool.h>** 的 header 來做更好的運用，以下為運用 <stdbool.h> 的狀況
	1. 可以用 `bool` 來宣告 boolean value
	2. 可以直接用 ture 與 flase 來做 assignment<br>E.g:
		```
		bool flag;        // 與 _Bool flag; 相同
		flag = false;
		...
		flag = true;
		```

<br><br>

---
## IV. The switch Statement
<br>

#### 一，switch statement
- 用以比對 variable 的值是在哪一個 case
- 優點：比用 cascaded if statement 還要易讀，且執行速度較快
- form:
	```
	switch ( expression ) {
	  case constant-expression : statements
	  ...
	  case constant-expression : statements
	  default : statements
	}
	```
	- Controlling expression: <br>在 `expression` 的部份放上你要比對的 integer expression。只能放 integer number 與 character (因為 character 被視為 integer)，不能放 floating-point 與 strings
	- **記得 switch statement 有 {}**
	- Case labels:<br>也就是 `case constatnt-expression` 的部份，但可放的東西以下的限制
		1. 可為整數
		2. 可為 expression，但計算出來的答案一定要是 interger，且不可用 n + 1 這類有代號的算是 (即便 n 是一個代表數字的 macro)
		3. 可為 characters
		4. 不可為 floating-point
		5. 最後一個 `default case` 為如果上面的狀況都不符合
	- Statements: 當它屬於那個 case 後要做什麼
	- E.g:
		```
		if (grade == 4)
		  printf("Excellent");
		else if (grade == 3)
		  printf("Good");
		else if (grade == 2)
		  printf("Average");
		else if (grade == 1)
		  printf("Poor");
		else if (grade == 0)
		  printf("Failing");
		else
		  printf("Illegal grade");
		
		等價於
		
		switch (grade) {
		  case 4: printf("Excellent");
		          break;
		  case 3: printf("Good");
		          break;
		  case 2: printf("Average");
		          break;
		  case 1: printf("Poor");
		          break;
		  case 0: printf("Failing");
		          break;
		  default: printf("Illegal grade");
		           break;
		}
		```
- 在 program 內
	1. 不可放置同樣一個 case 兩次
	2. case 順序對 program 不重要（但會影響到易讀性）
	3. `default case` 不一定要出現
	4. 可以共用 statement<br>E.g:
		```
		switch (grade) {
		  case 4:
		  case 3:
		  case 2:
		  case 1:  printf("Passing");
		           break;
		  case 0:  printf("Failing");
		           break;
		  default: printf("Illegal grade");
		           break;
		}
		
		也可以為了空間節省寫成
		
		switch (grade) {
		  case 4: case 3: case 2: case 1:
		           printf("Passing");
		           break;
		  case 0: printf("Failing");
		          break;
		  default: printf("Illegal grade")
		           break;
		}
		```

- break  的用意：<br>因為 switch statement 其實就是將下一行要執行的 statement 跳轉到某一個 case ，所以要用 `break` 來中斷 statement，不然就會一直執行下去
<br>

#### 二，範例二： Printing a Date in Legal Form

- program:
	```date.c
	// Prints a date in legal form
	
	#include <stdio.h>
	
	int main(void)
	{
	    int month, day, year;
	
	    printf("Enter date (mm/dd/yy): ");
	    scanf("%d /%d /%d",&month, &day, &year);
	
	    printf("Dated this %d", day);
	    switch (day) {
	      case 1: case 21: case 31:
	        printf("st");
	        break;
	      case 2: case 22:
	        printf("nd");
	        break;
	      case 3: case 23:
	        printf("rd");
	        break;
	      default: printf("th");
	               break;
	    }
	    printf(" day of ");
	
	    switch (month) {
	      case 1:  printf("January");   break;
	      case 2:  printf("February");  break;
	      case 3:  printf("March");     break;
	      case 4:  printf("April");     break;
	      case 5:  printf("May");       break;
	      case 6:  printf("June");      break;
	      case 7:  printf("July");      break;
	      case 8:  printf("August");    break;
	      case 9:  printf("September"); break;
	      case 10: printf("October");   break;
	      case 11: printf("November");  break;
	      case 12: printf("December");  break;
	    }
	    printf(", 20%d.\n", year);
	
	    return 0;
	}
	
	```
- 重點：
	1. 利用 `printf` 只要不打 `\n` 就不會換行的特性，就可以寫出在一行內用到多的 satement 的文字了
	2. 注意每一個 `printf` 該空格的地方，我很容易忘記這個
	3. 最後一行的 `printf` 記得要用 `\n` ，忘過很多次了

<br><br>

---
# Exercise:

#### Ex.1: operator 的 precedence 與 associativity
我的答案:
```
(a) 
Ans: 1
Reason: k = i * j == 6 等價於 k = ((i * j) == 6)

(b) 
Ans: 1
Reason: k > i < j 等價於 (k > i) < j，且 1 < j

(c)
Ans: 1
Reason: i < j == j < k 等價於 (i < j) == (j < k)

(d)
Ans: 0
Reason: i % j + i < k 等價於 ((i % j) + i) < k
```

<br>

#### Ex.2: The precedence of logical and relational operator 
我的答案：
```
(a)
Ans: 0
Reason: !i < j 等價於 (!i) < j

(b)
Ans: 1
Reason: !!i + !j 等價於 (!(!i)) + (!j)

(c)
Ans: 1
Reason: i && j || k 等價於 (i && j) || k

(d)
Ans: 1
Reason: i < j || k 等價於 (i < j) || k
```

<br>

#### Ex.3: logical operator 的 short-circuit
我的答案：
```
(a)
Ans: 1345
Reason: i < j || ++j < k 等價於 (i < j) || ((++j) < j)，且因為光是 i < j 就知道 or 成立，所以不會執行 ++j < k

(b)
Ans: 0789
Reason: i - 7 && j++ < k 等價於 (i - 7) && ((j++) < k)，且 i - 7 為假，所以不會執行 j++ < k

(c)
Ans: 1889
Reason: (i = j) || (j = k)，光是執行 i = j 就知道 or 為真，所以不會執行 (j = k)

(d)
Ans:  1221
Reason: ++i || ++j && ++k 等價於 ((++i) || (++j)) && (++k)
```

###### 易錯
>[!warning]
>precedence 代表的只是分組順序，不代表實際運算順序。在實際運算時還是會因為 short-circuit 而沒有用到 increment 與 decrement

<br>

#### Ex.4: conditional operator 的運用
我的答案：
```
(i > j) ? 1 : ((i == j) ? 0 : -1)
```

>[!tip] 小技巧
>在寫 selection statement 或 conditional expression 的時候，想如果...則...否則**執行下一個 statement 或 expression**。

<br>

#### Ex.5: relational operator 的 associativity
我的答案
```
Ans: yes; 會寫出 "n is between 1 and 10"
Reason: 因為 n >= 1 <= 10 等價於 (n >= 1) <= 10，然後得出 0 <= 10 為真
```

<br>

#### Ex.6: relational operator 的寫法
我的答案
```
Ans: yes; 沒有 print "n is between 1 and 10"
Reason: 如果要判斷是否在 1 到 10 之間，應該要寫 10 >= n && n >= 1，寫 1-10 會變成 n == -9
```

<br>

#### Ex.7: conditional operator 的判讀
我的答案
```
Ans: 17; 17
Reason: 17 >= 0，而 -17 < 0
```

<br>

#### Ex.8: 簡化 if statement
我的答案
```
teenager = (age >= 13 && age <= 19);
```

>[!tip] 重點
>講 logical operator 放在 assignment 右側就是判斷真或假

<br>

#### Ex.9: 判斷 statement 是否相同
我的答案：
```
Ans: yes
Reason: 只是兩個切入的角度不同而已
```

<br>

#### Ex.10: switch 的結果判定
我的答案：

```
Ans: onetwo
Reason: 因為沒有 break ，所以會繼續執行下一行的 printf("two")
```

<br>

#### Ex.11: 判斷 Areacode
我的答案
```program
#include <stdio.h>

int main(void)
{
    int area_code;

    printf("Enter a area code: ");
    scanf("%d", &area_code);

    switch (area_code) {
      case 229: printf("Albany\n");
                break;
      case 404: case 472: case 678: case 770:
                printf("Atlanta\n");
                break;
      case 478: printf("Macon\n");
                break;
      case 706: case 762:
                printf("Columbus\n");
                break;
      case 912: printf("Savannah\n");
                break;
      default:  printf("Area code not recognized\n");
                break;
    }
	
    return 0;
}
```
<br><br>

---
# Programming project:
#### Proj.1: 判斷數字有幾位數（4 位數以下）

program:

```c
#include <stdio.h>

int main(void)
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    printf("The number %d has ", num);
    if (num < 10)
      printf("1");
    else if (num <100)
      printf("2");
    else if (num < 1000)
      printf("3");
    else
      printf("4");
    printf(" digits\n");

    return 0;
}
```

output:

```
Enter a number: 123
The number 123 has 3 digits
```

<br>

#### Proj.2: 24 進位轉 12 進位

program:

```c
#include <stdio.h>

int main(void)
{
    int hr, min;

    printf("Enter a 24-hour time: ");
    scanf("%d :%d", &hr, &min);

    printf("Equivalent 12-hour time: ");
    if (hr <= 12)
      printf("%d:%.2d AM\n", hr, min);
    else
      printf("%d:%.2d PM\n", hr - 12, min);

    return 0;
}
```

output:
```
Enter a 24-hour time: 12:35
Equivalent 12-hour time: 12:35 AM
```

- 備註：雖然這樣打在當使用者輸入 15:3 之類的數字會變成 3:03 PM，但會這樣設計是因為：
	1. 如果是 30 或 40 這種數字，使用者直接輸入該數字，而不會只打 3
	2. 如果不在 `printf("%d:%.2d AM\n", hr, min);` 與 `printf("%d:%.2d PM\n", hr - 12, min);` 這兩行的分鐘上用 `%.2d` 的話，輸入整點時分鐘就會少一個零，例如：12.0

<br>

#### Proj.4: 風速轉換

program:
```c
#include <stdio.h>

int main(void)
{
    float speed;

    printf("Enter a wind speed (in knots) ");
    scanf("%f", &speed);

    printf("corresponding description is ");
    if (speed < 1.00f)
      printf("Calm\n");
    else if (speed < 3.00f)
      printf("Light air\n");
    else if (speed < 27.00f)
      printf("Breeze\n");
    else if (speed < 47.00f)
      printf("Gale\n");
    else if (speed < 63.00f)
      printf("Storm\n");
    else
      printf("Hurricane\n");

    return 0;
}
```

output:
```
Enter a wind speed (in knots) 29
corresponding description is Gale
```

<br>

#### Proj.10: 成績轉換

program:
```
#include <stdio.h>

int main(void)
{
    int num, tens;

    printf("Enter numerical grade: ");
    scanf("%d", &num);

    tens = num / 10;

    printf("Letter grade: ");
    switch (tens) {
      case 10: case 9:
        printf("A\n");
        break;
      case 8:
        printf("B\n");
        break;
      case 7:
        printf("C\n");
        break;
      case 6:
        printf("D\n");
        break;
      default:
        printf("F\n");
    }

    return 0;
}
```

output:
```
Enter numerical grade: 100
Letter grade: A
```

- 注：雖然題目中有提示說可以將它拆成兩個數字，但如果用 `scanf("%1d%1d", &tens, &ones)` 當成績為 100 的時候就會變成 F，所以我是用另一個方法：將十位數先宣告為整數，在除以十，這樣就可以利用整數值會消去掉小數的特性去呈現出 100 分的狀況

<br>

#### Proj.11: 將阿拉伯數字轉換成英文

program:
```c
#include <stdio.h>

int main(void) {

    int num, tens, ones;

    printf("Enter a two-digit number: ");
    scanf("%d", &num);

    ones = num % 10;
    tens = num / 10;

    printf("You entered the number ");
    if (num >= 11 && num <= 19) {
      switch (num) {
        case 11:
          printf("eleven");
          break;
        case 12:
          printf("twelve");
          break;
        case 13:
          printf("thirteen");
          break;
        case 14:
          printf("fourteen");
          break;
        case 15:
          printf("fifteen");
          break;
        case 16:
          printf("sixteen");
          break;
        case 17:
          printf("seventeen");
          break;
        case 18:
          printf("eignteen");
          break;
        case 19:
          printf("nineteen");
          break;
      }
    }
    else {
      switch (tens) {
        case 2:
          printf("twenty");
          break;
        case 3:
          printf("thirty");
          break;
        case 4:
          printf("forty");
          break;
        case 5:
          printf("fifty");
          break;
        case 6:
          printf("sixty");
          break;
        case 7:
          printf("seventy");
          break;
        case 8:
          printf("eighty");
          break;
        case 9:
          printf("ninety");
          break;
      }
      if (ones == 0)
        printf("\n");
      else {
        printf("-");
        switch (ones) {
          case 1:
            printf("one");
            break;
          case 2:
            printf("two");
            break;
          case 3:
            printf("three");
            break;
          case 4:
            printf("four");
            break;
          case 5:
            printf("five");
            break;
          case 6:
            printf("six");
            break;
          case 7:
            printf("seven");
            break;
          case 8:
            printf("eight");
            break;
          case 9:
            printf("nine");
        }
      }
    }
    printf("\n");

    return 0;
}
```

output:
```
Enter a two-digit number: 74
You entered the number seventy-four
```
