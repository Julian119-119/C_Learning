# C program: a modern approach Ch.7 note

## Program overview


| 題號  | 功能         | 觀念                     | 連結               |
| --- | ---------- | ---------------------- | ---------------- |
| 範例一 | 計算一連串數字的總和 | 用 long int 防止 overflow | [view](./sum2.c) |
<br><br>

---
# Note
## I. Integer Types
#### 一，Integer Constants

- Octal and Hexadecimal numbers:
	- Octal (base 8, 8 進位): 與 2 進位的概念一樣，就是只有用數字 0 到 7 ，例如：237 換成 Decimal (10 進位) 就是 $2 \times 8^2 + 3 \times 8^1 + 7 \times 8^0$
	- Hexadecimal (base 16, 16進位): 數字從 0 到 9 ，9 以後的數字就用 A 到 F，例如：1AF 換算成 10 進位就是 $1 \times 16^2 + 10 \times 16^1 + 15 \times 16^0$
- 用幾進位都只是一種表達式，最後電腦都會將其換成 Binary 的方式來儲存
- 在 C 內的用法
	1. Decimal: 就一般的打法
	2. Octal: **開頭用 0** ，且數字只有 0 到 7<br>E.g: 017, 037, 077777
		1. Hexadecimal: **開頭用 0x**，數字的部份包含 0 到 9 與 A 到 F，字母大小寫皆可<br>E.g: 0xf, 0xff, 0xFf, 0xFF, 0XFF
<br>

#### 二，Intro
- integer 的分類
	- 分類方法
		- 以是否有紀錄負號來分：
			1. signed int (預設)
			2. unsigned int
		- 使用的位元數多寡：
			1. int (預設)
			2. long int
			3. short int
	- signed integer 與 unsigned integer:
		1. signed integer (預設):
			- **可儲存負數**。會使用最左邊的 bit 來儲存正負號，如果是正的就會是 0，負的就會是 1。所以它可用的 bit 會比 unsigned integer 再更少
			- 最大的 16 bit integer 為O1111111111111111 =  $2^{15} - 1$
			- 最大的 32 bit integer 為1111111111111111111111111111111 = $2^{31} - 1$
		2. unsigned integer:
			- 不可儲存負數，所以可儲存的數字大於 signed integer
			- 最大的 16 bit integer 為 1111111111111111 = $2^{16} - 1$
			- 最大的 32 bit integer 為 11111111111111111111111111111111 = $2^{32} - 1$
			- 指派 constant 為 unsigned 的話，在字尾加上 U<br>E.g: 15U, 0377U (octal), 0x7fffU (hexadecimal)
	- long, short, integer:
		- 基本上就是指定電腦要用較多或較少的位元以防止數字溢出
		- short, ing, and int 只有規定說 int 用的位元數不能小於 short int，而 long int 不能小於 int，所以用的位元數有可能是相等的
		- 在不同的架構的電腦上會有不同大小值的限制
		- 電腦嘗試的順序為：int, unsigned, long int, unsigned long int
		- 指派數字為 long int 的時候要在字尾加上 L (為了與 1 混淆，L 基本都用大寫)
- 宣告時 ：
	1. 可將上兩種不同的分類方式一次宣告給 variable
	2. 在宣告時如果是預設的，那不打也沒差，例如 long signed int 等價於 long int
	3. 如果有用前述的分類法宣告的話就可以不打 `int`，例如：unsigned short int 等價於 unsigned short。所以 int 並不是必要的

<br>


#### 三，Integer Type in C99

- 在 C99 內有額外兩種的 type 為 
	1. `long long int` 被稱為 standard signed integer types
	2. `unsigned long long int` 被稱為 standard signed integer type
- 兩者都是在 64-bit 的電腦上才可以用
- 因為用的是 64-bit ，所以上下限很高
- 要指派數字為 long long integer 的話，在字尾加上 (LL)。unsigned 的話一樣在字尾加 U (在 LL 前或後皆可)

<br>

#### 四，Integer Overflow 

- 當數字太大，bit 數不夠的話，就稱為 overflow (溢出)
	- 發生在 signed integer ，其結果為 undefined behavior
	- 發生在 unsigned integer, 結果雖然有定義，但一旦 overflow，就會回歸 0 重新計算<br>E.g: 在 16-bit 的狀況下，能夠儲存到 $2^{16} = 65535$ (unsigned integer)，加 1 時就會變成 0，再加 1 就會變成 1
<br>

#### 五，Reading and Writing Integers

- 當數字 overflow 時，除了更改 declaration 以外，也要更改 `printf` `scanf`
- `%d` 要改為
	1. `%u`: decimal notation 
	2. `%o`: octal notation
	3. `%x`: hexadecimal<br>E.g:
		```c
		printf("%x", u); // writes u in base 16
		scanf("%o", &u); // writes u in base 8
		```
- 在 placehold 要增加
	1. `h`: short integer
	2. `l`: long integer
	3. `ll`: long long integer<br>E.g:
		```c
		short s;
		long long ll;
		
		printf("%lld", ll);
		printf("%hd", s);
		```
<br>

#### 六，範例一：Summing a Series of Numbers (Revisited)

- program:
```c
// Sums a series of numbers (using long variables)

#include <stdio.h>

int main(void)
{
   long i, sum = 0;

    printf("This program sums a series of integers\n");

    printf("Enter integers (0 to terminate): ");
    scanf("%ld", &i);

    while (i != 0) {
      sum += i;
      scanf("%ld", &i);
    }
    printf("The sum is: %ld\n", sum);

    return 0;
}
```

- 學習重點：
	- 在寫 program 的時候要思考一下有沒有可能會有 overflow 的情況
<br><br>

## II. Floating Types

#### 一，Intro

- floating-point 照精度由下往上排為以下三種：
	1. `float`: Single-precision floating-point
	2. `double`: Double-precision floating-point (預設)
	3. `long double`: Extended-precision floating-poing
	- float 是給不太重要的數字，而 double 則是大部分數字都夠用，
- C 並沒有提供 float, double 與 long double 各自的精度準確來說有多少，因為各自的電腦可能都不一樣。但大部分的電腦都用 The IEEE Floating-Point Standard，所以可以依照著這個標準來看最大最小值
- 在 C99 內也有新的分類分為 real floating types 與 complex types (`float _Comples` `double _Comples` `long double _Comples` 。而 float, double, long double 皆在 real floating types 內
- 在 Ch3 的時候就有大略看到，floating-point 本身就有許多的表示法<br>E.g: 以下皆為 57.0
	```
	57.0 57. 57.0e0 57E0 5.7e1 5.7e+1 .57e2 570.e-1
	
	(e 或 E 為 exponent，也就是 10 的幾次方，例如 5.7e+1 就是 5.7 * 10 的 1 次)
	```
- 因為預設為 `double` 所以指派 float 或 long double 就要額外在字尾加字母
	- float: 加 F (or f) ，例如：57.0f
	- long double: 加 L (or l)，例如：57.0L
<br>

#### 二，Reading and Writing Floating-Point Numbers

- 在 Ch3 內就看過了 `%e`, `%f`, and `%g`, 所以接下來的重點為 double 和 long double
- 要**讀取** double 的話就在 placehold 前加上 `l`。注意，在 `printf` 上是**沒有用處的**<br>E.g:
	```c
	double d;
	
	scanf("%lf", &d);
	```
- 要讀取或顯示 long double 在 placeholde 前加上 `L`<br>E.g:
	```c
	long double ld;
	
	scanf("%Lf", &ld);
	printf("%Lf", ld);
	```
<br><br>

## III. Character Types

#### 一，Intro

- `char` 為 character type
- 每一個 char 的值可能會因為不同電腦而所不同，因為電腦內採用的 character sets(= character encoding) 可能不一樣
	- 補：現今最有名的 character sets 為 ASCII，資料的話可能就要自己去查了
- 用途：指派單一的 character<br>E.g:
	```c
	char ch;
	
	ch = 'a';  // lower-case a
	ch = 'A';  // upper-case A
	ch = '0';  // zero
	ch = ' ';  // space
	```
<br>

#### 二，Operations on Characters

- 因為 character 其實就是由編碼而來的，所以 C 對待 character 與 integer 其實差不多。例如：在 ASCII 內的 codes 是從 0000000 到 1111111，而 97 就是對應到 `a`, 32 就是對應到 ' ' 等
- 當 character 被用於計算時，C 就會簡單的用整數值來作計算。也就是 `char` 在某種程度上是可以和 integer 互換的<br>E.g:
	```c
	char ch;
	int i;
	
	i = 'a';       // i is now 97
	ch = '65';    // ch is now 'A'
	ch = ch + 1;  // ch is now 'B'
	ch++;         // ch is now 'C'
	```
- 除了計算，不等式當然也行<br>E.g: 以下是會將小寫的字母換成大寫的部份 program
	```c
	if ('a' <= ch && ch <= 'z)
	  ch = ch - 'a' + 'A'
	```
- 在寫 program 的時候，可以將 character 想成連續的編碼就行
- 但在寫的時候也有可能產生 complier 無法抓出來的錯誤<br>E.g:
	```c
	'a' * 'b' / 'c'
	```
	這個可能會有不同的結果，因為如之前所說，每台電腦用的 character set 可能不相同
<br>

#### 三，Signed and Unsigned Characters

- 因為 `char` 被視為是 integer 所以也有 signed 與 unsigned
- 因為大多數時候都不太重要，所以不指定時是由 complier 來決定的。但也可以自己在 program 內宣告<br>E.g:
	```c
	signed char sch;
	unsigned char uch;
	```
	- tip: 如果在重要的時刻，不要由 complier 自己決定，一定要自己宣告它為 signed 或 unsigned
- 在 C99 的 \_Bool type 被視為是 unsigned integer type 
<br>

#### 四，Escape Sequence

###### 1. The table of escape sequence 

- 用途：顯示出那些無法在 program 內顯示，或在鍵盤上打不出來的字
- 以下為常用的 escape sequence 的表。(在 Ch3 內的只是比較大略的表)

	| Name            | Escape Sequence |
	| --------------- | --------------- |
	| Alert(bell)     |      \\a         |
	| Backspace       |        \\b      |
	| Form feed       | \\f  |
	| New line        | \\n  |
	| Carriage return | \\r  |
	| Horizontal tab  | \\t  |
	| Vertical tab    | \\v  |
	| Backslash       | \\\\ |
	| Question mark   | \\?  |
	| Single quote    | \\'  |
	| Double quote    | \\"  |
	- `\a` `\b` `\f` `\r` `\t` 和 `\v` 為 ASCII 內常見的 control characters
	- `\n` 為 ASCII line-feed character
	- `\\` `\'` `\"` `\?` 因為 `\` 是跳脫符號

###### 2. numeric escape

- 因為以上的表無法對應到所有字元，可以對應所有字元的只有 numeric escapes
- 找尋 numeric escape 的方法
	1. 在 Appendix E 內或 google 找出它所代表的 octal number 或 hexadecima number
	2. 在 program 內依據不同種的數字加上不同符號，且數字**一定都要是 unsigned**
		1. octal excape sequence: 在數字前面加上 `\`。與 octal constants 不同的是，它的開頭不一定要是 0
		2. hexadecimal escape sequence: 在數字前面加上 `\x`。`x` 一定要是小寫，但 hex digits (像是 b) 大小寫皆可
- 要用 numeric escape 時一定要用 single quotes，像是 `\33` 或 `\x1b`
- 因為 escape sequence 可能會有點難讀，所以可以用在 `#define` 內讓它好讀一點<br>E.g:
	```c
	#define ESC '\33'  // ASCII escape character
	```
<br>

#### 五，Character-Handling Functions

- `toupper` library function：將小寫字母換成大寫字母
- 如果要用 `toupper` 要加上 <ctype.h> 的標頭檔<br>E.g:
	```c
	#include <stdio.h>
	#include <ctype.h>
	```
- `toupper` 的運作方式：它會先檢查是否為小寫，如果是的話就將其換成大寫，不是就維持原樣<br>E.g:
	```c
	if ('a' <= ch && ch <= 'z')
	  ch = ch - 'a' + 'A'
	```
	等價於
	```c
	ch = toupper(ch);  // converts ch to upper case
	```
- `toupper` 可以用在 statement 內，用於比較<br>E.g:
	```c
	if (toupper(ch) == 'A') ...
	```
	如果 ch 是 a (不論大小寫)，則 ...
<br>

#### 六，Reading and Writing Characters using `scanf` and `printf`

- characters 用的 conversion specification 為 `%c`<br>E.g:
	```c
	char ch;
	
	scanf("%c", &ch);  // reads a single character
	printf("%c", ch);  // writes a single character
	```
- 由於 `%c` 不會跳過空白鍵，所以如果有空白的話就會一起被讀進去，如果要跳過的話就要像其他的 character 一樣在前面加空白<br>E.g:
	```c
	scanf (" %c", &ch);  // skips white space, then reads ch
	```
- 因為 `%c` 不會跳過空白，所以很適合用來偵測最後一個 input<br>E.g:
	```c
	do {
	  scanf ("%c", &ch);
	} while (ch != '\n');
	```
	用以偵測換行符
<br>

#### 七，Reading and Writing Characters using `getchar` and `putchar`

- 在讀取與顯示單一的 characters 時，可以用 `getchar` 與 `putchar` 來替代 `scanf` 與 `printf`
- `putchar` 用法： `putchar(variable);` <br>E.g:
	```c
	putchar(ch);
	```
- `getchar`：
	- 它會先讀取一個 character ，然後再 return。所以為了要儲存這個 character，就必須要用 assignmend<br>E.g:
		```c
		ch = getchar();  // reads a character and stores it in ch
		```
	- 它會回傳的值為 `int` 不是 `char`，所以在宣告時要用於儲存的 variable 通常會宣告為 int
	- `getchar` 也不會跳過空白鍵
	- 因為是用 assignment，所以它也可被視為 expression，而這就代表它可以被用在 loop 內<br>E.g:
		```c
		do {
		  scanf("%c", &ch);
		} while (ch != '\n')
		```
		等價於
		```c
		do {
		  ch = getchar();
		} while (ch != '\n')
		```
		也等價於
		```c
		while ((ch = getchar()) != '\n');
		```
		不過我是覺得這樣而比較難讀拉
	- 上面的例子中也可以不用 assignmen，因為 `getchar()` 本身就會 return 一個 `char` 了，所以可以直接比較，以下為兩個類似的 idiom:
		```c
		while (getchar() != '\n') ;      // skips rest of line
		while((ch = getchar()) == ' ') ; // skips blanks
		```
- 用 `getchar` 與 `putchar` 的優勢
	1. 讀取速度較 `printf` 與 `scanf` 快，因為後者被設計出來讀很多東西
	2. 他們也常被用於 macros 為了額外的速度 (macro 在 ch14.3)
- **注意**，因為 scanf 有窺視但不讀取的特性，所以可能會導致後面的 `getchar` 直接讀到前面遺留的 characte<br>E.g:
	```c
	printf("Enter an integer: ");
	scanf("%d", &i);
	printf("Enter a command: ");
	command = getchar();
	```
	後面的 `getchar()` 可能會讀到前面 `scanf` 所遺留下來的 character
<br>

#### 八，範例二：Determining the Length of a Message

- program:
	- version 1
		```c length.c
		// Determines the length of a message
		
		#include <stdio.h>
		
		int main(void)
		{
		    int len = 0;
		    char ch;
		
		    printf("Enter a message: ");
		    ch = getchar();
		    while (ch != '\n') {
		      len++;
		      ch = getchar();
		    }
		    printf("Your message was 27 character(s) long.\n");
		
		    return 0;
		}
		```
	- version 2 (縮短此 program)
		```c length2.c
		// Determines the lengthe of a message
		
		#include <stdio.h>
		
		int main(void)
		{
		    int leng;
		    char ch;
		
		    printf("Enter a message: ");
		    while (getchar() != '\n') {
		      leng++;
		    }
		    printf("Your message was %d character(s) long.\n", leng);
		
		    return 0;
		}
		```
- output:
	```
	Julian119@mx:~/常用/程式/C學習
	$ ./length2 
	Enter a message: Determining the Length of a Message
	Your message was 35 character(s) long.
	```
- 寫 program 時的心得
	- 在寫這個 program 的時候覺得與 ch6 中的 numdigit.c 很像，就只是要偵測的東西由數字換成了 character
	- 但在寫的時候也一直在想那這樣可不可以直接將 `getchar()` 放進 while statement 內，還是說與 `scanf` 一樣一定要立刻接在 `printf` 後面才可以輸入數字，所以我是寫完了第一個 program 才知道可以這樣做的
- 學到的東西
	- 在 `printf` 後可以將 `getchar` 放在 while 的 expression 內
	- 在使用者輸入完之後，並且按下 Enter 時，電腦讀到的就是 `\n` 所以不一定要精確的打 `\n` 也可以被 getchar() 抓出來
<br><br>

## IV. Type Conversion

#### 一，intro

- implicit 與 explicit conversions 簡介
	- implicit conversions: 因為電腦的要求比 C 更嚴格，所以會有一些在電腦內自己的換算<br>E.g:
		1. 在 C 之中的 integer 和 floating-point 可以混用，但電腦不行，所以電腦會將其換成 floating-point 再運算
		2. 不同 bit 數的數字不能夠一起算，所以它會將 bit 數全部調整為較高的數值
	- explicit conversions: 就一般的計算
- 會使用 implicit conversion 的情況：
	1. 在 arithmetic 或 logical expression 內的 operand 並不是相同的類型的時候，此時會執行 usual arithmetic conversions
	2. 當在 assignment 右側的 expression 與左側的種類不合的時候
	3. 在 function 內的 argument 與 parameter 不合的時候
	4. 當在 `return` 內的 expression 不符合 function 所需的種類的時候

#### 二，The Usual Arithmetic Conversions

- 在 arithmetic 或 logical expression 內的 operand 並不是相同的類型的時候，此時會執行 usual arithmetic conversions
- 原則就是將最窄的 operand 換成更大的 (例如 integer 換成 floating-point)
	- 這個方式也被稱為 promotion
	- 最常用的 promotion 為 integral promotions，也就是將 `char` 換成 `int`
- 以下為換算的規則，會依序換成目前有的 type 中最上面的
	1. 兩者皆為 floatin type:
		```mermaid
		graph BT;
		  node1["float"];
		  node2["double"];
		  node3["long double"];
		  node1 --> node2;
		  node2 --> node3;
		```
	2. 兩者皆不是 floating-point
		```mermaid
		graph BT
		  node1["int"];
		  node2["unsigned int"];
		  node3["long int"];
		  node4["unsigned long int"];
		  node1 --> node2;
		  node2 --> node3;
		  node3 --> node4;
		```
		- 例外：如果一個為 long int 另一個為 unsigned int，則它會換成 long unsigned int
- **注意**如果將 unsigned int 與 signed int 相加，兩個都會變成 unsigned integer ，此時如果有數字是負數，接下來可能會導致該數被加上 unsigned int 的最大值，產生錯誤的結果
- 以下是展示 usual arithmetic conversions 的例子
	```c
	char c;
	short int s;
	int i;
	unsigned int u;
	long int l;
	unsigned long int ul;
	float f;
	double d;
	long double ld;
	
	i = i + c;    // c 會被換成 int
	i = i + s;    // s 會被換成 int
	u = u + i;    // i 會被換成 unsigned int
	l = l + u;    // u 會被換成 long int
	ul = ul + l;  // l 會被換成 unsigned long int
	f = f + ul;   // ul 會被換成 float
	d = d + f;    // f 會被換成 double
	ld = ld + d;  // d 會被換成 long double
	```
<br>

#### 三，Conversion During Assignment

- 在 assignment 時如果左右的 type 不相同就會換成 lvalue 的 type，如果左邊的 type 較寬就不會有問題<br>E.g:
	```c
	char c;
	int i;
	float f;
	double d;
	
	i = c;    // c 會被換成 int
	f = i;    // i 會被換成 float
	d = f;    // f 會被換成 double
	```
- 但如果 Lvalue 的 type 反而比較窄，就會導致不好的結果，例如
	1. 左邊為 integer ，右邊為 floating-point。會砍掉小數點
	2. 如果是完全不同的樣態，那可能就會產生無意義的結果<br>E.g:
		```c
		char c;
		int i;
		float f;
		
		c = 1000;     // WRONG
		i = 1.0e20;   // WRONG
		f = 1.0e100;  //WRONG
		```
- 所以也是因為這個原因才會在 floating-point 的數字後方加一個 f，使它不會變成 double
<br>

#### 四，Implicit Conversions in C99

- 因為在 C99 內又多了許多複雜的 type  (例如 long long int, \_Booltype)，所以才多了其他的規則
- integer conversion rank: (從高到低)
	1. long long int, unsigned long long int
	2. long int, unsigned long int
	3. int, unsigned int
	4. short int, unsigned short int
	5. char, signed char, unsigned char
	6. \_Bool
- 規則
	- 其中之一為 floating-point：照之前的規則換成 floating-point
	- 皆不是 floating-point:
		1. 兩者皆為 signed 或 unsigned ，則轉換成更高的 rank 的
		2. unsigned operand 的 rank 高於 signed operand 的 rank，換成 unsigned
		3. signed operand 包含到所有的 unsigned operand 的部份，換成 signed operand
		4. 否則將 signed operand 換成對應到的 unsigned operand
<br>

#### 五，Casting

- 作用：將 expression 的結果換成某一個 type
- form:
	```c
	( type-name ) expression
	```
- E.g:
	1. 
		```c
		i = (int) f;  // f is converted to int
		```
	2. 
		```c
		float f, frac_part;
		
		frac_part = f - (int) f
		```
	3. 
		```c
		float quotient;
		int dividend, divisor;
		
		quotient = (float) dividend / divisor;
		```
		divisor 前不需要加上 `(float)` 因為當前面為 floating-point，後面的 divisor 就會一起被換成 floating-point
- 他的 precedence 與 associativity 與 unary operator 一樣
- 用途：**防止溢出**<br>E.g:
	```c
	long i;
	int j = 1000;
	
	i = j * j;        // 可能會溢出
	i = (long) j * j  // 溢出的機率會低很多
	```
	注意：因為 cast operator 本身就是 unary operator 所以如果你是先計算相乘的結果，再用 cast operator 就會沒有任何意義
	```c
	i = (long) (j * j)  // WRONG
	```
<br><br>

## V. Type Definitions

#### 一，Intro
- `typedef` 用於定義 type，屬於 directive 的一種<br>E.g:
	```c
	#define Bool int
	```
	等價於
	```c
	typedef int Bool;
	```
- 定義的字不一定要開頭大寫
- 在 program 後方的效用基本與 \#define 相同，只是比較容易讓人辨別這是 type 的 definition
<br>

#### 二，Advantages of Type Definitions

1. 讓人更容易讀懂 program<br>E.g:
	```c
	typedef float Dollars;
	
	Dollars cash_in, cash_out;
	```
	比
	```c
	float cash_in, cash_out;
	```
	容易懂
2. 讓 program 更容易更改而不用動到 declaration，例如將上述例子換成 double 就只需要到 difective 就好
<br>

#### 四，The `sizeof` Operator

- 作用：測量該型別或物件的大小
- form:
	```c
	sizeof ( type-name )
	```
- 例如 `sizeof(char)` 永遠都是 1 。而在 32-bit 的機器上 `sizeof(int)` 正常為 4
- () 不一定需要，但要注意 `sizeof` 為 unary operator 所以要測量 i + j 的大小時就一定要加括號
<br><br>

---
# Exercise

## Ex.1: 不同進位的換算

我的答案：
- (a) $7 \times 8^1 + 7 \times 8^0 = 63$
- (b) $7 \times 16^1 + 7 \times 16^0 = 119$
- (c) $10 \times 16^2 + 11 \times 16^1 + 12 \times 16^0 = 2748$
<br>

## Ex.2: 判斷數字的合理性

我的答案: (d)<br>Reason: 在數字上不可用下底線
<br>

#### Ex.3: 判斷合理的型別
我的答案：(c)<br>Reason：沒有 long double
<br>

#### Ex.4: 判斷 statement 的合法性
我的答案：(c)<br>Reason: 因為在 `printf` 上如果要顯示 variable 的話應該要用 `%c`
<br>

#### Ex.5: 判斷各個進位的打法是否合理
我的答案： (b)<br>Reason: 因為 hexadecimal 要是 0x 或 0X 開頭
<br>

#### **Ex.6: 判斷最小可容納的位元數**
我的答案： 
1. (a) `char`
2. (b) `short`
3. (c) `short1
4. (d) `long`
Reason:
- 各個型別在 C 當中保證的最小值
	1. `char`: 8-bit
	2. `short`: 16-bit
	3. `int`: 16-bit
	4. `long`: 32-bit
- 因為要「保證」可以容納的下，所以是用 unsigned 的形式去算最大值
- 所以各個選項的值為 
	1. 31: `char`
	2. 365: `short`
	3. 1440: `short`
	4. 86400: `long`
<br>