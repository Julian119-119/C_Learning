// compute the dimensional weight of a 12 x 10 x 8 box

#include <stdio.h>

int main(void)
{
    int height, length, width, volume, weight;

    height = 12;
    length = 10;
    width = 8;
    volume = height * length * width;
    weight = (volume + 165) / 166;

    printf("Dimension: %dx%dx%d\n", height, length, width);
    printf("Volume: %d\n", volume);
    printf("Dimensional weight (pounds): %d\n", weight);

    return 0;
}
