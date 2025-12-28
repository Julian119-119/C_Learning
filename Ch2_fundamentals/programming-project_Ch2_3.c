//This is my answer for programing project 3 in c programming a mordern approach ch2

#include <stdio.h>
#define FRACTION_NUMBER 4.0f/3.0f
int main(void)
{
    int r;
    printf("Enter the radius of the sphere: ");
    scanf("%d", &r);
    printf("%.2fπ\n",FRACTION_NUMBER * r *r *r);

    return 0;
}
