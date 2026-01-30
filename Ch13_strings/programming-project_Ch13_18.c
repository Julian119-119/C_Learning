// This my program for programming project 18
// in C Programming: a modern approach
// This program is uesed to acceopt a date form
// the user in the form mm/dd/yyy and then displays
// it in the form month dd, yyy

#include <stdio.h>

void enter_and_read_date(int* num_month, int* day, int* year);
const char* trans_num_to_name_month(int num_month);
void print_outcome(const char name_month[], int day, int year);

int main(void) {
  int num_month, day, year;
  const char *name_month;

  enter_and_read_date(&num_month, &day, &year);
  name_month = trans_num_to_name_month(num_month);

  print_outcome(name_month, day, year);
}

void enter_and_read_date(int* num_month, int* day, int* year) {
  printf("Enter a date (mm/dd/yyyy): ");
  scanf("%d /%d /%d", num_month, day, year);
}

const char* trans_num_to_name_month(int num_month) {
  const char* name_month_code[12] = {"January",
                                     "February",
                                     "March",
                                     "April",
                                     "May",
                                     "June",
                                     "July",
                                     "August",
                                     "September",
                                     "October",
                                     "November",
                                     "December"};

  return name_month_code[num_month - 1];
}

void print_outcome(const char name_month[], int day, int year) {
  printf("You entered the date %s %d, %d\n", name_month, day, year);
}