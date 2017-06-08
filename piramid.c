#include <stdio.h>
#include <cs50.h>
void phash(int times);
void pblank(int times);
void newline(void);
void pline(int blank_times, int hash_times);
void piramid(int height);

int main (void)
{
        int height = get_int();
        piramid(height);

}

void phash(int times)
{
        int i;
        for (i = 0; i < times; ++i) {
                printf("#");
                
        }
}

void pblank(int times)
{
        int i;
        for (i = 0; i < times; ++i) {
                printf(" ");
        }
}

void newline(void)
{
        printf("\n");
}

void pline(int blank_times, int hash_times)
{
        pblank(blank_times);
        phash(hash_times);
}

void piramid(int height)
{
        int i;
        int hash = 2;
        int blank = height - 1;
        for (i = 0; i < height; ++i) {
                pline(blank, hash);
                newline();
                hash++;
                blank--;
                
        }
}
