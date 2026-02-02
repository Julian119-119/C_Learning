# Note

- *注：本章所講的 structure, unions 和 enumerations 皆為型別的種類*

## I. Structure Variables

#### 一，Intro

- 目前學過的 data structure 只有陣列，而 structure 也屬於 data structure 的一種
- structure 中的元素稱為 **members**
- structure 與陣列的不同之處
	1. members **不必然有著相同的型別**
	2. 要呼叫 members 必須要用**名稱**而非位址
<Br>

#### 二，Declaring Structure Variables

- 假設我們需要兩個變數 (part1 與 part2)，且每個變數皆需要有 number, name, 與 on_hand 這三個數值，就可以宣告成
	```c
	struct {
	  int number;
	  char name[NAME_LEN+1];
	  int on_hand;
	} part1, part2;
	```
	- **變數名稱填在最後面**
	- 在記憶體中會儲存成<br>![](./Ch16_attachment/c-programming_a-modern-approach_ch16_1.png)
- 且每一個 member 內部所需要的變數名稱不會與其他的 structure **內部**的變數名稱衝突<Br>E.g:
	```c
	struct {
	  int number;
	  char name[NAME_LEN+1];
	  int on_hand;
	} part1, part2;
	
	struct {
	  int name[NAME_LEN+1];
	  int number;
	  char sex;
	} emplouee1, employee2;
	```
	雖然兩個 structure 中都有 number 與 name 但不會影響彼此
<Br>

#### 三，Initializing Structure Variables

- 要初始化 sturcture 的話因為有一連串的內部變數，所以需要用 **{}** 來初始化<Br>E.g:
	```c
	struct {
	  int number;
	  char name[NAME_LEN+1];
	  int on_hand;
	} part1 = {528, "Disk drive", 10},
	  part2 = {914, "Printer cable", 5};
	```
	 記憶體示意圖<br>![](./Ch16_attachment/c-programming_a-modern-approach_ch16_2.png)
- 在初始化的規則基本上都與陣列類似，例如：沒有被初始化到的值皆為 0
<Br>

#### 四，Designated Initializers

- 在 structure 也有與陣列相同的 designated initializers - E.g:
	```c
	{528, "Disk drive", 10}
	```
	等價於
	```c
	{.number = 528, .name = "Disk drive", .on_hand = 10}
	```
	- 其中的 . + member 名稱就是 **designator**
	- 因為是以 member 的名稱來作區別的，所以**順序調換並不會有任何的影響**。也就是說上面的初始化等價於
		```c
		{.on_hand = 10, .number = 528, .name = "Disk drive"}
		```
		- *注：在不用 designator 的狀況順序是有差的*
- 與陣列的 designator 相同，並不是所有的東西都需要用進 list 中<br>E.g:
	```c
	{.number = 528, "Disk drive", .on_hand = 10}
	```
<Br>

#### 五，Operations on Structues

- 要取用 member ，必須要用 **structure 名稱** + **.** + **member 的名稱**<br>E.g:
	```c
	printf("Part number: %d\n", part1.number);
	printf("Part name: %s\n", part1.name);
	printf("Quantity on hand: %d\n", part1.on_hand);
	```
- member 因為是 Dlvalue ，所以就照之前的變數去用即可<br>E.g:
	1. 
		```c
		part1.number = 258;
		// changes part1's part number
		part1.on_hand++;
		// increments part1's quaantity on hand
		```
	2. 
		```c
		scanf("%d\n", &part1.on_hand);
		```
		- *注：. 也算式一個 operator，但也因為 . 的 precedence 高於 & ，所以會照著預期的形式來走*
- 也可以**對 structure 使用 assignment**<br>E.g:
	```c
	part2 = part1;
	```
	- 意思就是將 part1 裡面的資訊都複製給 part2
	- 因為陣列不可被用 = 複製 (在此指的是**複製整條陣列，單一元素可以**)，所以可以利用 structure 的特性來讓他們可以被複製<br>E.g:
		```c
		struct {int a[10]; } a1, a2;
		
		a1 = a2;
		// 因為 a1 與 a2 都是 structure 所以合法
		```
- 只有擁有 compatible type 可以被使用 assignment 來複製
- 而要有 compatible 的狀態就必須要**同時被宣告**
- 缺點：未來**無法被新增新的 structure**，就算重新宣告一次也會因為 compatible 的限制而**無法被複製**
<br><br>

## II. Structure Types

#### 一，Declaring a Structure Tag

- **structure tag**: 用來辨認 structure 種類的名稱<br>E.g:
	```c
	struct part {
	  int number;
	  char name[NAME_LEN+1];
	  int on_hand;
	};
	```
	-  其中的 part 就是 structure tag
	- 記得 } 之後要加**分號**
- 使用了 structure tag 之後，就可以**用來宣告變數**<br>E.g:
	```c
	struct part part1, part2;
	```
- 就算使用了 structure tag ，也還是可以**同時宣告變數**<br>E.g:
	```c
	struct part {
	  int number;
	  char name[NAME_LEN+1];
	  int on_hand;
	} part1, part2;
	```
- 就算是分開用 structure tag，也是有 compatible 的特性<br>E.g:
	```c
	struct part part1 = {528, "Disk drive", 10};
	struct part part2;
	
	part2 = part1;
	// legal; both parts have the same type
	```
<Br>

#### 二，Defining a Structure Type

- 也可以使用 typedef 來作為替代<br>E.g:
	```c
	typedef struct {
	  int number;
	  char name[NAME_LEN+1];
	  int on_hand;
	} Part;
	```
	- 注意：structure tage 在用 typedef 的時候是必須在**最後面**的
- 宣告：
	```c
	Part part1, part2
	```
	- 這裡**不可以有 struct**
<br>

#### 三，Structures as Arguments and Return Values

- 用了 structures tag 之後就可以將 strcture 用做引數<br>E.g:  part 為 structures tag
	1. 將 structure 做為引數
		- 定義 function
			```c
			void print_part(struct part p)
			{
			  printf("Part number: %d\n", p.number);
			  printf("Part name: %s\n", p.name);
			  printf("Quantity on hand: %d\n", p.on_hand);
			}
			```
		- 呼叫 function
			```c
			print_part(part1);
			```
	2. 回傳 structures
		- 定義 function
			```c
			sturct part build_part(int number, const char *name,
			                       int on_hand)
			{
			  struct part p;
			  
			  p.number = number;
			  strcpy(p.name, name);
			  p.on_hand = on_hand;
			  return p;
			}
			```
		- 呼叫 function
			```c
			part1 = build_part(528, "Disk drive", 10);
			```
- 也可以**在 function 中初始化**<br>E.g:
	```c
	void f(struct part part1)
	{
	  struct part part2 = part1;
	}
	```
	- 裡面的 part2 為 local variable