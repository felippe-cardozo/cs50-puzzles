#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
char crypt_char(int key, char c);
char crypt_alpha_UP(int key, char c);
char crypt_alpha_DOWN(int key, char c);

int main(int argc, string argv[])
{
        int key = atoi(argv[1]);
        char a = crypt_char(13, 'H');
        printf("%c\n", a);
        printf("enter text:\n");
        string s = get_string();
        for (int i = 0, n = strlen(s); i < n; i++) {
                printf("%c", crypt_char(key, s[i]));
        }
        printf("\n%s\n", s);

        return 0;
}
/* int main(void) */
/* { */
/*         char c = 'A'; */
/*         /1* c = ('A' - 65 + 2) % 26; *1/ */
/*         /1* printf("%i\n", c); *1/ */
/*         /1* c = c + 65; *1/ */
/*         /1* printf("%c\n", c); *1/ */
/*         printf("%c\n", crypt_alpha_UP(28, c)); */
/*         /1* int key = atoi(argv[1]); *1/ */
/*         /1* printf("%d\n", key); *1/ */
/*         /1*         for(int i = 2; i < argc; i++) { *1/ */
/*         /1*                 for(int j = 0, n = strlen(argv[i]); j < n; j++) { *1/ */
/*         /1*                         if (isalpha(argv[i][j])) { *1/ */
/*         /1*                                 printf("%c", argv[i][j] + key); *1/ */
/*         /1*                         } *1/ */
/*         /1*                         else { printf("%c", argv[i][j]); } *1/ */
/*         /1*                 } *1/ */
/*         /1*         } *1/ */
/*         /1*         printf("\n"); *1/ */
        
/*         /1* return 0; *1/ */
/* } */

// checks the type of the char and calls the apropriate method
/* string crypt_string(string s, key) */
/* { */
        
/*         for(int i = 0, n = strlen(s), string output; i < n; i++) { */
/*                 output[i] = crypt_char(key, s[i]); */
/*         } */
/*         return output; */
/* } */

char crypt_char(int key, char c)
{
        if (isalpha(c)) {
                if (isupper(c)) { return crypt_alpha_UP(key, c); }
                else { return crypt_alpha_DOWN(key, c); }
        }
        else {
                return c;
        }
}

char crypt_alpha_UP(int key, char c)
{
       c = (c - 65 + key) % 26;
       return toupper(c += 65);

}

char crypt_alpha_DOWN(int key, char c)
{
        c = (c - 97 + key) % 26;
        return tolower(c += 65);
}
