#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>


string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVXZYabcdefghijklmnopqrstuvxzy";

char *get_salt(string s)
{
        char *salt = (char *)malloc(2);
        salt[0] = s[0];
        salt[1] = s[1];
        return salt;
}

bool match_pwd(string candidate, string actual, string salt)
{
        if (strcmp(actual, crypt(candidate, salt)) == 0) {
                return true;
        }
        return false;
}

string brute_force(string cripted, string salt)
{
        char *candidate = (char *)malloc(4);
        int n = strlen(ALPHA);
        for (int i = 0; i < n; i++) {
                candidate[0] = ALPHA[i];
                /* printf("candidate = %s\n", candidate); */
                if (match_pwd(candidate, cripted, salt)) {
                        printf("%s\n", candidate);
                        return "found";
                }}
        // second level
        for (int i = 0; i < n; i++) {
                candidate[0] = ALPHA[i];
                for (int ii=0; ii < n; ii++) {
                        candidate[1] = ALPHA[ii];
                        /* printf("%s\n", candidate); */
                        if (match_pwd(candidate, cripted, salt)) {
                                printf("%s\n", candidate);
                                return "found";
                        }}}
        //third level
        for (int i = 0; i < n; i++) {
                candidate[0] = ALPHA[i];
                for (int ii = 0; ii < n; ii++) {
                        candidate[1] = ALPHA[ii];
                        for (int iii=0; iii < n; iii++) {
                                candidate[2] = ALPHA[iii];
                                /* printf("%s\n", candidate); */
                                if (match_pwd(candidate, cripted, salt)) {
                                        printf("%s\n", candidate);
                                        return "found";
                                }
                        }
                }
        }
        for (int i = 0; i < n; i++) {
                candidate[0] = ALPHA[i];
                for (int ii = 0; ii < n; ii++) {
                        candidate[1] = ALPHA[ii];
                        for (int iii=0; iii < n; iii++) {
                                candidate[2] = ALPHA[iii];
                                for (int iiii=0; iiii < n; iiii++) {
                                        candidate[3] = ALPHA[iiii];
                                        /* printf("%s\n", candidate); */
                                        if (match_pwd(candidate, cripted, salt)) {
                                                printf("%s\n", candidate);
                                                return "found";
                                        }
                                }
                        }
                }
        }

printf("not found\n");
return "";
}


int main(int argc, char *argv[])
{
        char *salt = (char *)malloc(2);
        salt[0] = argv[1][0];
        salt[1] = argv[1][1];
        printf("%d\n", match_pwd("rofl", "50fkUxYHbnXGw", "50"));
        printf("salt = %s, argv[1] = %s\n", salt, argv[1]);
        brute_force(argv[1], salt);

        return 0;
}
