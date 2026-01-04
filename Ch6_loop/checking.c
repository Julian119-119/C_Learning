// Balance a checkbook

#include <stdio.h>

int main(void)
{
  int cmd;
  float balance = 0.00f, credit, debit;

  printf("*** ACME checkbook-balancing program ***\n");
  printf("Commands: 0=clear, 1=credit, 2=debit, 3=balance, 4=exit\n");
  printf("\n");



  for (;;) {
    printf("Enter command: ");
    scanf("%d", &cmd);
    if (cmd > 4 || cmd < 0) {
      printf("Irregular command, please re-enter command\n");
      continue;
    }
    else switch (cmd) {
      case 0:  balance = 0;
               credit = 0;
               break;
      case 1:  printf("Enter amount of credit: ");
               scanf("%f", &credit);
               balance += credit;
               break;
      case 2:  printf("Enter amount of debit: ");
               scanf("%f", &debit);
               balance -= debit;
               break;
      case 3:  printf("Current balance: $%.2f\n", balance);
               break;
      case 4:  goto exit;
    }
  }

      exit: return 0;
}
