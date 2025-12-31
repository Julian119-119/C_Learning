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
