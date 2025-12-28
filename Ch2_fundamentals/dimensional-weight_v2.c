//computes the dimensional weight of a box from input provided by the user
//learn "scanf"

#include <stdio.h>

int main(void)
{
    int height, length, width, volume, weight, dimension;

    printf("Enter height of box: ");
    scanf("%d", &height);
    printf("Enter length of box: " );
    scanf("%d", &length);
    printf("Enter width of box: ");
    scanf("%d", &width);

    volume = height * length * width;
    weight = (volume + 165) / 166;

    printf("Dimension (cubic inches): %dx%dx%d\n", height, length, width);
    printf("Volume: %d\n", volume);
    printf("Dimensional weight (pounds): %d\n",weight);

    return 0;
}
