#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char substitution(string key, char c);

// take key as command line argument
int main(int argc, string argv[])
{
    string key = argv[1];
    printf("Key: %s\n",key);

    // key validation
    // if 0 or 2+ arguments provided error (argc = ?) - printf("error") return 1 (error)
    // invalid if - not 26 char, contains chars not a-z or A-Z, not containing each letter exactly once (?) - printf("error") return 1 (error)

    // input
    // plaintext: (get string)
    string plainText = get_string("plaintext: ");


    // substitution
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        printf("%c", substitution(key, plainText[i]));
    }
    printf("\n");

    // output
    // ciphertext: (print substituted cipher)
    // return 0



}
// substitution function
//// substitute each letter in the string with the indexed key, per alphabetic position
//// preserve case: capitalized letters must remain capitalized letters

char substitution(string key, char c)
{
    // char for substitution
    char sub = c;

    // key
    string kUpper = key;
    printf("Pre Upper Key: %s\n",kUpper);

    // covert key to lowercase
    string kLower = key;
    for (int j = 0; key[j]; j++)
    {
        kLower[j] = tolower(key[j]);
    }

    printf("Upper Key: %s\n",kUpper);
    printf("Lower Key: %s\n",kLower);



    // store the lower case aplhabet
    string alphabetL = "abcdefghijklmnopqrstuvwxyz";
    // store the update case aplhabet
    string alphabetU = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


    // for each c in the string, check for upper and lower case and substitute for key value
    // upper case loop
    // for (int i = 0, n = strlen(kUpper); i < n; i++)
    // {
    //     if (sub == alphabetU[i])
    //     {
    //         sub = kUpper[i];
    //     }
    // }
    // lower case loop


    // return subbed value
    return sub;
}