#  C program: a modern approach Ch.4 note
<br>

## I. Arithmetic operators

#### 一， 基本概述
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
	4. 如果是除一個負數或被除數為負數的話，其結果會是先算負號提出來的算式，再加上一個負號（例如： -9 / 7 的結果為 -2，-9 % 7 的結果為 -2）。只有在 C99 是有被明確定義的，C89 則不是

<br>

>[!tip] Implementation-Defined Behavior
>implementation-defined behavior 是指將有不同定義的行為，交給 complier 去實做，例如在 C89 的 -9 / 7 可能會向上取整，也可能會向下取整。但這樣可能會造成 program 的不穩定，且後續難以維護與移植，所以不要依賴 implementation-defined behavior，即使現在結果可能是好的，但未來會造成更大的影響

<br>

#### 二， Operator Precedence and Associativity

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

#### 三， 範例一： Computing a UPC Check Digit

- program:![[C-program_2_record_20251223#upc.c|program]]
- output: 
	```
	Enter the first (single) digit: 8
	Enter first group of five digits: 14423
	Enter second group of five digits: 18792
	Check digit: 3
	```

<br><br>

---
## II. Assignment operator

#### 一，Simple assignment

- 用於將 expression 計算出來的值儲存進 variable 中<br>E.g:
	```
	i = 5;            // i 為 5
	j = i;            // j 為 5
	k = 10 * i + j;   // k 為 55
	```
- assignment 皆為 **right associative**，且 **precedence 低於 additive**
- 在 C 中，**assignment 為 operator**，所以 
	1. **assignment 會受到 declaration 的影響**。如果你宣告它為 integer，但他的 expression卻是floating-point，那就會被無條件捨去到整數。
	2. **assignment 可以被連續使用**，但要**小心 operator precedence**，否則會造成意料之外的結果<br>E.g
		```
		1.
		i = j = k = 0;  等價於  i = (j = (k = 0))  
		(因為是 right associative)
		
		2.
		int i;
		float f;
		
		f = i = 33.3f; 
		其結果會是 i 先被指派為 33，然後 f 為 33.0 (不是 33.3f)
		```
	- 雖然也可以將 assignment 放在右側的 expression 中，但**不建議這樣做**，因為這樣做可能會造成奇怪的結果 (會在後面提到)<br>E.g:
		```
		i = 1;
		k = 1 + (j = i);
		print("%d %d %d\n", i, j, k);
		// 結果會是 1 1 2
		```

<br>

>[!tip] Side Effects
>一般的 `+` `-` `*` `/` 皆不會改變 variable 內儲存的值，但 assignment 會。這種用了會改變其 variable 內儲存數值的效果稱為 side effects

<br>

#### 二，Lvalues

- **在 = 的左側，用以儲存 expression 的 object (left-value)**。在 assignment 中是一定要有的存在
- **Lvalue 必定要是一個 variable**，不可為 expression
- 但 = 右側是可以自由的去放 expression，這也就是為何沒有 Rvalue 的原因，因為 Rvalue 就是 expression
<br>
#### 三，Compound assignment

- 簡化過後的指令，**用以改變 variable 內的數值**，有以下 5 種
	1. `v += e`: 將 v 加上 e 後，將其結果儲存進 v
	2. `v -= e`: 將 v 減掉 e 後，將其結果儲存進 v
	3. `v *= e`: 將 v 乘上 e 後，將其結果儲存進 v
	4. `v /= e`: 將 v 除上 e 後，將其結果儲存進 v
	5. `v %= e`: 將 v 除上 e 後的餘數儲存進 v
- 在使用時要**特別注意 operator precedence**。他的 precedence 與 = 一樣，都是小於一般計算符號的，在計算的時候 compound assignment 會比他們還晚算<br>E.g
	```
	i *= j + k  會等價於 i = i * (j + k)  而不是 i = i * j + k
	```
- 與 = 相同，為 right associative

<br><br>

---
## III. Increment and Decrement Operators

- 用以將**儲存數值增加 1 (++) 或減少 1 (--)**，有分 prefix 與 postfix 兩種
	1. prefix: 在使用的當下立即改變其值，所以在指令內計算時會用到最新的數值
		- 符號： `++i` 與 `--i` 
	2. postfix: 先使用舊數值去計算，在執行完該 statement 後再改變其數值
		- 符號: `i++` 與 `i--`
	- E.g:
		```
		i = 1;
		printf("i is %d\n", --i);  /* prints "i is 0" */
		printf("i is %d\n", i);    /* prints "i is 0" */
		
		i = 1;
		printf("i is %d\n", i--);  /* prints "i is 1" */
		printf("i is %d\n", i);    /* prints "i is 0" */
		```
- 用太多 increment 與 decrement 時會造成程式碼很難讀<br>E.g:
	```
	i = 1;
	j = 2;
	k = ++i + j++;
	
	等價於
	
	i = 1;
	j = 2;
	i = i + 1;
	k = i + j;
	j = j + 1;
	```

<br><br>

---
## IV. expression evaluation

- 目前學到的 precedence 與 associativity

	|  Precedence   |                                         Name                                          |                 Symebol(s)                 |   Associativity   |
	| :-----------: | :-----------------------------------------------------------------------------------: | :----------------------------------------: | :---------------: |
	|   <br><br>1   |                increment <br>(postfix)<br><br>decrement <br>(postfix)                 |            `++`<br><br><br>`--`            |   <br><br>left    |
	| <br><br><br>2 | increment <br>(prefix)<br><br>decrement <br>(prefix)<br><br>unary plus<br>unary minus | `++`<br><br><br>`--`<br><br><br>`+`<br>`-` | <br><br><br>right |
	|       3       |                                    multiplicative                                     |                `*` `/` `%`                 |       left        |
	|       4       |                                       additive                                        |                  `+` `-`                   |       left        |
	|       5       |                                      assignment                                       |        `=` `*=` `/=` `%=` `+=` `-=`        |       right       |
- 綜合使用目前學到的 operator，去判斷先後順序<br>E.g:
	```
	題目：
	a = b += c++ - d + --e / -f
	
	1.第一級 precedence
	a = b += (c++) - d + --e / -f
	
	2.第二級 precedence
	a = b += (c++) - d + (--e) / (-f)
	
	3.第三級 precedence
	a = b += (c++) - d + ((--e) / (-f))
	
	4.第四級 precedence
	a = b += (((c++) - d) + ((--e) / (-f)))
	
	1. 第五級 precedence
	a = (b += (((c++) - d) + ((--e) / (-f))))
	由此就可將它分解成一連串的 subexpression
	```

<br>

#### 一，Order of subexpression Evaluation

1. assignment operator
	- 雖然從 operator precedence 與 associativity 可以得出一連串的 subexpreesion，但 **C 並沒有規定 subexpression 之間的先後順序**。<br>E.g:
		```
		a = 5;
		c = (b = a + 2) - (a = 1);
		兩個括號之間並沒有規定誰會先算，所以會有以下兩種情況
		
		1. 如果 (b = a + 2) 先算，答案就會是 6
		2. 如果 (a = 1) 先算，答案就會是 2
		```
	- 為了避免這種情況，最好**避免將 assignment operators 放在 subexpression 內**，用分開的 statement 去寫出來<br>E.g: 
		```
		將上述算式改為
		a = 5;
		b = a + 2;
		a = 1;
		c = b - a;
		```
2. increment 與 decrement
	- **increment 與 decrement (postfix) 數值改變的時間沒有被規定**，只有規定在 ; 前就一定會改變，所以就會造成其結果有多種可能<br>E.g:
		```
		i = 2;
		j = i * i++;
		
		1. 第二個 operand 先被取出 (fetch)，其結果會是 6
		2. 第一個 operand 先被取出 (fetch)，其結果會是 2
		* fetch a variable 的意思是從記憶體內 variable 的數值中「取出」
		```

<br>

>[!tip] Undefined Behavior
>undefined behavior 是指**在 C 內沒有被定義的行為**，而它會導致不可預測的後果。由此定義， `c = (b = a + 2) - (a = 1)` 與 `j = i * i ++`，皆為 undefined bahavior。與 implementation-defined bahavior的差異為，至少 implementation 是有被定義的，只是會隨著不同編譯器而改變，但 undefined 是沒有被定義的。

<br><br>

---
## V. Expression Statement

- **任何一個 expression 只要在句尾加上 ; 就可以變成 statement**。例如: `++i;`，雖他的結果值會直接捨棄（因為沒有 assignment），但 i 還是會因為 side effect 而被儲存下來。