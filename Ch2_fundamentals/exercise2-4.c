// compute the dimensional weight of a 12 x 10 x 8 box

#include <stdio.h>

int main(void)
{
    int height = 12,length = 10, width = 8, volume;

    volume = height * length * width;

    printf("Dimension: %dx%dx%d\n", height, length, width);
    printf("Volume: %d\n", volume);
    printf("Dimensional weight (pounds): %d\n", (volume + 165) / 166);

    return 0;
}
