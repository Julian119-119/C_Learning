// This is another way to "initialize" and "print variable"

#include <stdio.h>

int main(void)
{
    int height = 8, length = 12, width = 10;

    printf("Dimension = %dx%dx%d\n", height, length, width);
    printf("Volume = %d\n", height * length * width);
    printf("Weight = %d\n", (height * length * width + 165) / 166);

    return 0;
}
