#include <cs50.h>
#include <stdio.h>
#include <string.h>
int water_consumption(int minutes);

int main (void)
{
        int minutes = get_int();
        printf("%i\n", water_consumption(minutes));
}

int water_consumption(int minutes)
{
        return 12 * minutes;
}
