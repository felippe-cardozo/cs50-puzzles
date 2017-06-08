#include <stdio.h>
#include <cs50.h>
int count(long long number);
int first_digit(long long number);
string lenght_check(int card);
int * second_to_last(long long card, int *Ar);
int sum_sec_to_last(long long card);

int main(void)
{
        long long card = 378282246310005;
        /* int * s_t_l = second_to_last(card); */
        /* int sum = sum_sec_to_last(card); */
        int longArray[count(card) - 1];
        int i;
        for (i = count(card) - 1; i >= 0 ; --i) {
                longArray[i] = card % 10;
                printf("array[%d] = %d\n", i, longArray[i]);
                card = card / 10;
                printf("card = %llu\n", card);
                
        }

}


string lenght_check(int card)
{
        if (count(card) == 15 && first_digit(card) == 3)
        { return "AMEX"; }
        else if(count(card) == 13)
        { return "VISA"; }
        else if(count(card) == 16 && first_digit(card) == 4)
        {return "VISA";}
        else if(count(card) == 16 && first_digit(card) == 5)
        {return "MASTER";}
        else
        {
                return "INVALID";
        }
}

int count(long long number)
{
        int i;
        for (i = 0; number >= 10; ++i) {
               number /= 10;
        }
        return i + 1;
}

int first_digit(long long number)
{
        while (number >= 10)
        {
                number /= 10;
        }
        return number;
}
        

int * second_to_last(long long card, int *Ar)
{
        int length = count(card);
        /* int * cardarray = to_a(card, count(card) - 1); */
        int i = 0;
        int ii = 1;
        int sum[length / 2];
        while (ii <= length)
        {
                sum[i] = Ar[ii] * 2;
                ii += 2;
                i++;
        }
        return sum;
}

int sum_sec_to_last(long long card)
{
        int length = count(card) / 2;
        int * sec_to_last = second_to_last(card);
        int i;
        int sum = 0;
        for (i = 0; i <= length; ++i) {
                if (sec_to_last[i] > 9){
                        sum += sec_to_last[i] / 10;
                        sum += sec_to_last[i] % 10;
                } 
                else { sum += sec_to_last[i]; }
        }
        return sum;
}

