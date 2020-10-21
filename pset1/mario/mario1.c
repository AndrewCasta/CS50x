#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // declare height, ask user for value between 0 and 8
    int height;
    do
    {
    height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // loop through height number of times, and print incrementing block length each time

    // spaces(height - i);
    // block(i);
    // printf("\n");


    for (int i = 0; i < height; i++)
    {
        // loop for spaces

        // loop for hashes
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        // new line in loop
        printf("\n");
    }



}
// print # n times
// void block(int n)
// {
//   for (int i = 0; i < n; i++)
//   {
//         printf("#");
//   }
// }

// void spaces(int n)
// {
//     for (int i = 0; i < n; i++)
//     {
//         printf(" ");
//     }
// }