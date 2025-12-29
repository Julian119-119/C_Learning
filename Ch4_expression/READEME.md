# C program: a modern approach Ch.4 note
<br>

## I. Arithmetic operators

#### 1. 基本概述
- 名詞解釋：
	1. operator: 即運算符號，例如 1 + 2 的 +
	2. operand: 即算式中的數字，例如 1 + 2 的 1, 2
	3. arithmetic operator: 也就是一般的加減乘除的符號，有分以下幾種

	| Unary         | Binary        | Binary            |
	|:-------------:|:-------------:|:-----------------:|
	|               | Additive      | Multiplicative    |
	| + unary plus  | + addition    | \* multiplication |
	| - unary minus | - subtraction | \/ division       |
	|               |               | % remainder       |

- unary operator: 只需要一個 operand ，也就是 -1 這樣的 expression<br>binary operator: 需要兩個 operand，也就是 1 + 2 這樣的 expression
- `%` (remainder)，用於計算餘數。例如： 5 % 2 的結果就是 1 (因為 5 除以 2 餘 1)
- 對於 `%` 與 `/` 需要特別注意的點：
	1. 如果在 `/` 的兩端都直接放 integer 的話，結果會直接**無條件捨去到整數**，因為它會直接認定你要整數值。例如 1 / 2 的結果是 0，而不是 0.5。如果要算出小數的話，就應該**將除數與被除數都換成小數**，也就是 1.00f / 2.00f
	2. `%` 需要兩端都是 integer
	3. 與一般的計算一樣， `%` 與 `/` 都是不接受分母為 0 的，否則會引發 undefined behavior
	4. 如果是除一個負數或被除數為負數的話，其結果會是先算負號提出來的算式，再加上一個負號（例如： -9 / 7 的結果為 -2，-9 % 7 的結果為 -2）

>[!tip] Implementation-Defined Behavior
>implementation-defined behavior 是指將未定義的行為，交給 complier 去實做。但這樣可能會造成 program 的不穩定，且後續難以維護與移植，所以不要依賴implementation-defined behavior，即使現在結果可能是好的，但未來會造成更大的影響

<br>

#### 2. Operator Precedence and Associativity

- Operator precedence:
	1. 用以決定誰先算，有較高 precedence 的 operator 先算 (在數學式上的表示法就是先用括號刮起來)，可想像成是垂直的上下關係。
	2. 目前 operator 的 precedence
		```
		Highest: +  -  (unary)
		         *  /    %
		Lowest:  +  -  (binary)
		```
	3. E.g:
		```
		i + j * k    等價於  i + (j * k)
		-i * -j      等價於  (-i) * (-j)
		-i + j / k   等價於  (-i) + (j / k)
		```
- associativity:<br>用以決定有相同的 precedence 的 operator 誰要先算，有分 right associative 與 left associative 兩種，從哪一側開始分組的意思就是哪一側先被括號刮起來
	- right associative: 從右側開始分組，目前 unariy 的 `-` 與 `+` 就屬於這邊
	- left associative: 從左側開始分組，目前 bainary 的 `*` `/` `+` `-` 就屬於這邊
	- E.g:
		```
		i - j - k  等價於  (i - j) - k
		i * j / k  等價於  (i * j) / k
		- + i      等價於  - (+i)
		```

<br>

#### 3. 範例一：Computing a UPC Check Digit

- program:
	```upc.c
	/* Computes a Universal Product Code check digit */
	
	#include <stdio.h>
	
	int main(void)
	{
	    int d, i1, i2, i3, i4, i5, j1, j2, j3, j4, j5,
	       first_sum, second_sum, total;
		
	    printf("Enter th first (single digit): ");
	    scanf("%1d", &d);
	    printf("Enter first group of five digits: ");
	    scanf("%1d%1d%1d%1d%1d", &i1, &i2, &i3, &i4, &i5);
	    printf("Enter second group of five digits: ");
	    scanf("%1d%1d%1d%1d%1d", &j1, &j2, &j3, &j4, &j5);
		
	    first_sum = d + i2 + i4 + j1 + j3 + j5;
	    second_sum = i1 + i3 + i5 + j2 + j4;
	    total = first_sum * 3 + second_sum;
		
	    printf("Check digit: %d\n", 9 - ((total - 1) % 10 ));
		
	    return 0;
	}
	```
- output: 
	```
	Enter the first (single) digit: 8
	Enter first group of five digits: 14423
	Enter second group of five digits: 18792
	Check digit: 3
	```
