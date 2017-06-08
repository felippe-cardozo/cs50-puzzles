#include <stdio.h>
#include <cs50.h>
#include <math.h>
int length(long long card);
int step_one(long long card);
int get_on_index(long long card, int index);
int step_two(long long card);
bool luhn(long long card);
bool length_check(long long card);
string card_type(long long card);

int main(void)
{
        printf("Enter Credit Card:\n");
        long long card = get_long_long();
        if (length_check(card) && luhn(card)) {
               printf("%s\n", card_type(card)); 
        }
        else { printf("Card Invalid"); }

}

int length(long long card)
{
        int length = 0;
        while (card > 9){
                card /= 10;
                length++;
        }
        return length;
}

int get_on_index(long long card, int index)
{
        int len = length(card);
        while(index != len){
                card = card / 10;
                len--;
        }
        return card % 10;
}

int step_one(long long card)
{
        int cardlength = length(card);
        int sum = 0;
        for (int i = 1; i <= cardlength; i += 2) {
                int num = get_on_index(card, i) * 2;
                if (num > 9){
                        sum += 1 + (num % 10);
                }
                else {
                        sum += num;
                }
                
        }
        return sum;
}

int step_two(long long card)
{
        int cardlength = length(card);
        int sum = 0;
        for(int i = 0; i <= cardlength; i += 2) {
                sum += get_on_index(card, i);
        }
        return sum;
}

bool luhn(long long card)
{
        return (step_one(card) + step_two(card)) % 10 == 0;

}

bool length_check(long long card)
{
        return length(card) == 12 || length(card) == 14 || length(card) == 15;
}

string card_type(long long card)
{
        string cardtype;
        if (length(card) == 14) {
                return cardtype = "AMEX";
        }
        else if (length(card) == 12) {
                return cardtype = "VISA";
        }
        else if (length(card) == 15 && get_on_index(card, 0) == 4) {
                return cardtype = "VISA";
        }
        else if (length(card) == 15 && get_on_index(card, 0) == 5) {
                return cardtype = "MASTER";
        }
        else {
                return cardtype = "INVALID";
        }
}
