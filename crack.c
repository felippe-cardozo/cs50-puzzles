#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
char *get_salt(string s);
string one_digit_pass(string hs, string salt);
string two_digit_pass(char *hs, string salt);
string three_digit_pass(char *hs, string salt);

int main(int argc, char *argv[])
{
  string test = crypt("zzz", "50"); 
  printf("test = %s\n", test);
  printf("%s should equals %s\n", test, three_digit_pass(argv[1], "50"));
  /* printf("%s should equals %s\n", test, two_digit_pass(argv[1], "50")); */
  /* printf("crypting b : %s\n", crypt("b", "50")); */
  /* printf("%s should equals %s\n", test, one_digit_pass(argv[1], "50")); */
  /* printf("%s\n", crypt("rofl", "50")); */   
  /* printf("%s\n", get_salt(argv[1])); */
        return 0;
}

char *get_salt(string s)
{
        char *salt = (char *)malloc(2);
        salt[0] = s[0];
        salt[1] = s[1];
        return salt;
}

string one_digit_pass(char *hs, string salt)
{
        string alpha = "ABCDEFGHIJKLMNOPQRSTUVXZYabcdefghijklmnopqrstuvxzy";
        char *try = (char *)malloc(1);
        printf("%s HASH\n", hs);
        for(int i = 0, n = strlen(alpha); i < n; i++){
                try[0] = alpha[i];
                char *target = crypt(try, salt);
                printf("try is : %s\n", try);
                printf("target is: %s\n", target);
                printf("hs is: %s\n", hs);
                printf("%d\n", strcmp(target, hs));
                if (strcmp(target, hs) == 0){
                        printf("hash inside IF is %s\n", hs);
                        printf("crypt is : %s\n", target);
                        return try;
                }
        }
        return "not found";
}

string two_digit_pass(char *hs, string salt)
{
        string alpha = "ABCDEFGHIJKLMNOPQRSTUVXZYabcdefghijklmnopqrstuvxzy";
        char *try = (char *)malloc(2);
        for(int i = 0, n = strlen(alpha); i < n; i++){
                try[0] = alpha[i];
                for(int ii = 0, nn = strlen(alpha); ii < nn; ii++){
                        try[1] = alpha[ii];
                        char *target = crypt(try, salt);
                        printf("try is %s\n", try);
                        printf("target is %s\n", target);
                        printf("hs is %s\n", hs);
                        if (strcmp(target, hs) == 0){
                                return try;
                        }
                }

        }
        return "not found";
}

string three_digit_pass(char *hs, string salt)
{
        
        string alpha = "ABCDEFGHIJKLMNOPQRSTUVXZYabcdefghijklmnopqrstuvxzy";
        char *try = (char *)malloc(3);
        for (int i = 0, n = strlen(alpha); i < n; i++){
                try[0] = alpha[i];
                for (int ii = 0, nn = strlen(alpha); i < nn; ii++){
                        try[1] = alpha[ii];
                        for(int iii = 0, nnn = strlen(alpha); i < nnn; iii++) {
                                try[2] = alpha[iii];
                                char *target = crypt(try, salt);
                                if (strcmp(target, hs) == 0) {
                                        return try;
                                }
                        }
                }
        }
        return "not found";
}
