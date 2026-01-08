# C program: a modern approach Ch.7 note

## Program overview


| 題號  | 功能         | 觀念                     | 連結               |
| --- | ---------- | ---------------------- | ---------------- |
| 範例一 | 計算一連串數字的總和 | 用 long int 防止 overflow | [view](./sum2.c) |

### I. Integer Types
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