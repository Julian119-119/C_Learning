// Maintains a parts database (array version)

#include <stdio.h>
#include <stdlib.h>

#include "readline.h"

#define NAME_LEN 25
#define MAX_PARTS 100

struct part {
  int number;
  char name[NAME_LEN + 1];
  int on_hand;
  struct part* next;
};

struct part* inventory = NULL;  // points to first part

// number of parts currently stored
int num_parts = 0;

struct part* find_part(int number);
void insert(void);
void search(void);
void update(void);
void print(void);

// main: Prompts the user to enter an operation code,
//       then calls a function to perform the requested
//       action. Repeats until the user enters the
//       command 'q'. Prints an error message if the user
//       enter an illegal code.
int main(void) {
  char code;

  for (;;) {
    printf(
        "operation code: "
        "i (insert), s (search), u (update), p (print), q (quit)\n");
    printf("Enter operation code: ");
    scanf(" %c", &code);
    // skips to end of line
    while (getchar() != '\n');
    switch (code) {
      case 'i':
        insert();
        break;
      case 's':
        search();
        break;
      case 'u':
        update();
        break;
      case 'p':
        print();
        break;
      case 'q':
        return 0;
      default:
        printf("Illegal code\n");
    }
    printf("\n");
  }
}

// find_part: Looks up a part number in the inventory
//            array. Returns the array index if the part
//            number is found; otherwise, returns -1.
struct part* find_part(int number) {
  struct part* p;

  for (p = inventory; p != NULL && p->number < number; p = p->next);
  // 修正點：少了 NULL 的話，就會變成 p 指向 NULL
  if (p != NULL && p->number == number)
    return p;
  else
    return NULL;
}

// insert: Prompts the user for information about a new
//         part and then inserts the part into the
//         database. Prints an error message and returns
//         prematurely if the part already exists or the
//         database if full.
void insert(void) {
  int part_number;
  struct part *cur, *prev, *new_part;

  // 輸入檢查
  if (num_parts == MAX_PARTS) {
    printf("Database is full; can't add more parts.\n");
    return;
  }

  printf("Enter part number: ");
  scanf("%d", &part_number);

  if (find_part(part_number) != NULL) {
    printf("Part already exists.\n");
    return;
  }

  // 分配空間
  new_part = malloc(sizeof(struct part));
  if (new_part == NULL) {
    printf("Database is full; can't add more parts.\n");
    return;
  }

  // 輸入，並填入 data
  new_part->number = part_number;
  printf("Enter part name: ");
  read_line(new_part->name, NAME_LEN);
  printf("Enter quantity on hand: ");
  scanf("%d", &new_part->on_hand);

  // 開始插入
  for (prev = NULL, cur = inventory; cur != NULL && cur->number < part_number;
       prev = cur, cur = cur->next);
  if (prev == NULL) {
    new_part->next = inventory;
    inventory = new_part;
  } else {
    new_part->next = prev->next;
    prev->next = new_part;
  }
  num_parts++;
}

// search: Prompts the user to enter a part number, then
//         looks up the part in the database. If the part
//         exists, prints the name and quantity on hand;
//         if not, prints an error message.
void search(void) {
  int number;
  struct part* p;

  printf("Enter part number: ");
  scanf("%d", &number);
  p = find_part(number);
  if (p != NULL) {
    printf("Part name: %s\n", p->name);
    printf("Quantity on hand: %d\n", p->on_hand);
  } else
    printf("Part not found.\n");
}

// update: Prompts the user to enter a part number.
//         Prints an error message if the part doesn't
//         exist; otherwise, prompts the user to enter
//         change in quantity on hand and updates the
//         database.
void update(void) {
  int number, change;
  struct part* p;

  printf("Enter part number: ");
  scanf("%d", &number);
  p = find_part(number);
  if (p != NULL) {
    printf("Enter change in quantity on hand: ");
    scanf("%d", &change);
    p->on_hand += change;
  } else
    printf("Part not found.\n");
}

// print: Prints a listing of all parts in the database,
//        showing the part number, part name, and
//        quantity on hand. Parts are printed in the
//        order in which they were entered into the
//        database.
void print(void) {
  printf("Part Number    Part Name                Quantity on Hand\n");
  for (struct part* p = inventory; p != NULL; p = p->next) {
    printf("%8d       %-25s%11d\n", p->number, p->name, p->on_hand);
  }
}
