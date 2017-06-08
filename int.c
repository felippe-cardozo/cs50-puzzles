#include <cs50.h>
#include <stdio.h>

int main (void)
{
        printf("x is ");
        int x = get_int();
        printf("y is ");
        int y = get_int();
        printf("sum of x and y is %i\n", x + y);
}
