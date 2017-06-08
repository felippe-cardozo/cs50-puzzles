/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

int get_min(int values[], int n, int start);
/**
 * Returns true if value is in array of n values, else false.
 */

bool search(int value, int values[], int n)
{
        int max = n - 1;
        int min = 0;
        int guess = n / 2;
        while(true)
        {
                if (max - min == 0){
                        if (values[min] == value){
                                return true;
                        }
                        else { 
                                return false; }
                }
                if(values[guess] == value){
                        return true;
                }
                else if(values[guess] < value) {
                        min = guess + 1;

                }
                else if(values[guess] > value){
                        max = guess - 1;
                }
                guess = (max + min) / 2;
        }
        return false;

}
/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
        int count = 0;
        int temp = 0;
        for(int i = 0; i < n -1; i++) {
                int min = get_min(values, n, i);
                if (min >= 0) {
                        temp = values[count];
                        values[count] = values[min];
                        values[min] = temp;
                        count++;
                }
        }
        return;
}

int get_min(int values[], int n, int start)
{
        int small = values[start];
        int count = start;
        int size = n - start;
        int idx = -1;
        for(int i = 0; i < size; i++) {
                if (small > values[count]) {
                        small = values[count];
                        idx = count;
                }
                count++;
        }
        return idx;

}
