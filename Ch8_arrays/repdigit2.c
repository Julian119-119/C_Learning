// check numbers for repeated digits

#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    bool digit_seen[10] = {false};
    int digit;
    long n;

    printf("Enter a number: ");
    scanf("%ld", &n);

    while (n != 0) {
      digit = n % 10;
      n /= 10;
      if  (digit_seen[digit] == false)
        digit_seen[digit] = true;
      else
        break;
    }

    if (n == 0)
      printf("No repeated digit\n");
    else
      printf("Repeated digit\n");

    return 0;
}
