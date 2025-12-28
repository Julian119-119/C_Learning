//This is my answer for programming project 7 in c programming: a modern approach Ch2

#include <stdio.h>

int main(void)
{
    int your_money, number_20bills, number_10bills, number_5bills, number_1bills;

    printf("Enter a U.S. dollar amount: ");
    scanf("%d", &your_money );

    number_20bills = your_money / 20;
    number_10bills = (your_money - number_20bills *20) /10;
    number_5bills = (your_money - number_20bills * 20 - number_10bills * 10) / 5;
    number_1bills = your_money - number_20bills * 20 - number_10bills * 10 - number_5bills * 5;

    printf("$20 bills: %d\n", number_20bills);
    printf("$10 bills: %d\n", number_10bills);
    printf("$5 bills: %d\n", number_5bills);
    printf("$1 bills: %d\n", number_1bills);

    return 0;
}
