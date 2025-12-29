/* This is my answer for programming project 5 in C programming: a modern approach */

#include <stdio.h>

int main(void)
{
    int a_11, a_12, a_13, a_14, a_21, a_22, a_23, a_24;
    int a_31, a_32, a_33, a_34, a_41, a_42, a_43, a_44;
    int row_sum1, row_sum2, row_sum3, row_sum4;
    int column_sum1, column_sum2, column_sum3, column_sum4;
    int diagonal_sum1, diagonal_sum2;

    printf("Enter the numbers from 1 to 16 in any order\n");
    scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
       &a_11, &a_12, &a_13, &a_14, &a_21, &a_22, &a_23, &a_24, &a_31, &a_32, &a_33, &a_34, &a_41, &a_42, &a_43, &a_44);

    row_sum1 = a_11 + a_12 + a_13 + a_14;
    row_sum2 = a_21 + a_22 + a_23 + a_24;
    row_sum3 = a_31 + a_32 + a_33 + a_34;
    row_sum4 = a_41 + a_42 + a_43 + a_44;
    column_sum1 = a_11 + a_21 + a_31 + a_41;
    column_sum2 = a_12 + a_22 + a_32 + a_42;
    column_sum3 = a_13 + a_23 + a_33 + a_43;
    column_sum4 = a_14 + a_24 + a_34 + a_44;
    diagonal_sum1 = a_11 + a_22 + a_33 + a_44;
    diagonal_sum2 = a_14 + a_23 + a_32 + a_41;

    printf("\n%2d %2d %2d %2d\n%2d %2d %2d %2d\n%2d %2d %2d %2d\n%2d %2d %2d %2d\n",
        a_11, a_12, a_13, a_14, a_21, a_22, a_23, a_24, a_31, a_32, a_33, a_34, a_41, a_42, a_43, a_44);
    printf("Row sums: %2d %2d %2d %2d\n", row_sum1, row_sum2, row_sum3, row_sum4);
    printf("Column sums: %2d %2d %2d %2d\n", column_sum1, column_sum2, column_sum3, column_sum4);
    printf("Diagonal sums: %2d %2d\n", diagonal_sum1, diagonal_sum2);

    return 0;
}

