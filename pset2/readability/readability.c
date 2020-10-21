#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

// function declerations
int wordCounter(string text);
int letterCounter(string text);
int sentenceCounter(string text);


// main program
int main(void)
{
    // get string for analysis
    string text = get_string("Enter text: ");

    // printf("%s\n", text);

    // count number words, letters & sentences
    int wordCount = wordCounter(text);
    // printf("Word count: %i\n", wordCount);

    int letterCount = letterCounter(text);
    // printf("Letter count: %i\n", letterCount);

    int sentenceCount = sentenceCounter(text);
    // printf("Sentence count: %i\n", sentenceCount);

    // Calc index
    // L is the average number of letters per 100 words
    float L = (float) letterCount / wordCount * 100;
    // printf("L: %f\n", L);
    // S is the average number of sentences per 100 words
    float S = (float) sentenceCount / wordCount * 100;
    // printf("S: %f\n", S);

    // index = 0.0588 * L - 0.296 * S - 15.8
    int readabilityIndex = round(0.0588 * L - 0.296 * S - 15.8);
    // printf("I: %f\n", 0.0588 * L - 0.296 * S - 15.8);
    // printf("Grade: %i\n", readabilityIndex);



    // output Grade X
    // X = index
    // if X > 16 = Grade 16+
    // if X < 1 = Before Grade 1
    if (readabilityIndex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (readabilityIndex > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", readabilityIndex);
    }

}

// external functions

// words - seperated by spaces (+ 1)
int wordCounter(string text)
{
    string s = text;
    int wordCount = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == ' ')
        {
            wordCount++;
        }
    }
    wordCount++;
    return wordCount;
}


// letters - chars from a to z or A to Z (ASCI)
int letterCounter(string text)
{
    string s = text;
    int letterCount = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122))
        {
            letterCount++;
        }
    }
    return letterCount;
}

// sentences - ends with . ! or ?
int sentenceCounter(string text)
{
    string s = text;
    int sentenceCount = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            sentenceCount++;
        }
    }
    return sentenceCount;
}