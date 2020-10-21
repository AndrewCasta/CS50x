#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char substitution(string key, char c);

// take key as command line argument
int main(int argc, string argv[])
{
    string key = argv[1];

    // key validation
    // if 0 or 2+ arguments provided error (argc = ?) - printf("error") return 1 (error)
    if (argc != 2)
    {
        printf("Error: Expecting single argument\n");
        return 1;
    }
    // invalid if - not 26 char, contains chars not a-z or A-Z, not containing each letter exactly once (?) - printf("error") return 1 (error)
    if (strlen(key) != 26)
    {
        printf("Error: Expecting 26 char key\n");
        return 1;
    }
    for (int x = 0, m = strlen(key); x < m; x++)
    {
        if (isalpha(key[x]) == 0)
        {
            printf("Error: Expecting chars a-z or A-Z\n");
            return 1;
        }
    }
    // invalid if string contains duplicates
    for (int y = 0, dupe = 0, o = strlen(key); y < o; y++)
    {
        for (int z = 0, p = strlen(key); z < p; z++)
        {
            if (key[z] == key[y])
            {
                dupe++;
            }
        }
        dupe--;
        if (dupe == 2)
        {
            printf("Error: Expecting non-duplicate chars\n");
            return 1;
        }
    }



    // input
    // plaintext: (get string)
    string plainText = get_string("plaintext: ");


    // substitution
    // output
    // ciphertext: (print substituted cipher)
    // return 0
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        printf("%c", substitution(key, plainText[i]));
    }
    printf("\n");
    return 0;

}
// substitution function
//// substitute each letter in the string with the indexed key, per alphabetic position
//// preserve case: capitalized letters must remain capitalized letters

char substitution(string key, char c)
{
    // char for substitution
    char sub = c;

    // key
    string k = key;
    // store the lower case aplhabet
    string alphabetL = "abcdefghijklmnopqrstuvwxyz";
    // store the update case aplhabet
    string alphabetU = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


    // for each c in the string, check for upper and lower case and substitute for key value
    // upper case loop
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (sub == alphabetU[i])
        {
            sub = toupper(key[i]);
            return sub;
        }
    }
    // lower case loop
    for (int l = 0, m = strlen(key); l < m; l++)
    {
        if (sub == alphabetL[l])
        {
            sub = tolower(key[l]);
            return sub;
        }
    }

    // return value if not subbed
    return sub;
}