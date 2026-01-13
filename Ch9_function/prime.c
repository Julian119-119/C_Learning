// Test whether a number is prime

#include <stdbool.h>
#include <stdio.h>

bool is_prime(long n)
{
  int divisor;

  if (n <= 1)
    return false;
  for (divisor = 2; divisor * divisor <= n; divisor++)
    if (!(n % divisor))
      return false;
 return true;
}

int main(void)
{
  long n;

  printf("Enter a number: ");
  scanf("%ld", &n);

  if (is_prime(n))
    printf("%ld is a prime\n",n );
  else
    printf("%ld is not a prime\n", n);

  return 0;
}
