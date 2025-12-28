//This is my answer for programming project 8 in c programming: a modern approach Ch2

#include <stdio.h>

int main(void)
{
    float loan, interest_rate, monthly_payment,
       monthly_interest_rate, remaining_balance_1year, remaining_balance_2year, remaining_balance_3year; 

    printf("Enter amount of loan: ");
    scanf("%f", &loan);
    printf("Enter interest rate: ");
    scanf("%f", &interest_rate);
    printf("Enter monthly payment: ");
    scanf("%f", &monthly_payment);

    monthly_interest_rate = interest_rate / 12;
    remaining_balance_1year = loan * (1 + monthly_interest_rate / 100) - monthly_payment;
    remaining_balance_2year = remaining_balance_1year * (1 + monthly_interest_rate / 100) - monthly_payment;
    remaining_balance_3year = remaining_balance_2year * (1 + monthly_interest_rate / 100) - monthly_payment;

    printf("Balance remaining after first payment: %.2f\n", remaining_balance_1year);
    printf("Balance remaining after second payment: %.2f\n", remaining_balance_2year);
    printf("Balance remaining after third payment: %.2f\n", remaining_balance_3year);

    return 0;
}
