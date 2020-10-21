#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
    char *word = "'''";

    // int hash1 = ((int)tolower(word[0])) - 97;
    // printf("%i\n", hash1);
    // int hash2 = ((int)tolower(word[1])) - 97;
    // printf("%i\n", hash2);
    // int hash3 = ((int)tolower(word[2])) - 97;
    // printf("%i\n", hash3);

    // // // output a number, between 0 & N - 1
    // // return 625 * hash3 + 25 * hash2 + hash1;
    // printf("%i\n", 625 * hash1 + 25 * hash2 + hash3);

     // input word (alphabetical char, maybe ' etc')
    int hash[3];
    for (int i = 0; i < 3; i++)
    {
        if ((int)word[i] != 39)
        {
            hash[i] = ((int)tolower(word[i])) - 97;
        }
        if ((int)word[i] == 39)
        {
            hash[i] = 26;
        }
    }
    printf("%i\n", word[0]);
    printf("%i\n", word[1]);
    printf("%i\n", word[2]);
    printf("%i\n", word[3]);
    printf("%i\n", hash[0]);
    printf("%i\n", hash[1]);
    printf("%i\n", hash[2]);
    // printf("%i\n", hash[3]);
    // output a number, between 0 & N - 1
    // return 676 * hash[0] + 26 * hash[1] + hash[2];
    printf("%i\n", 676 * hash[0] + 26 * hash[1] + hash[2]);
    // return 1;
}