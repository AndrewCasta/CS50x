#include <stdio.h>
#include <cs50.h>

int collatz(int n);

int count = 0;

int main(void)
{
    int i = get_int("Number: ");
    printf("Collatz: %i\n", collatz(i));
}

int collatz(int n)
{

    if (n == 1)
    {
        return count;
    }
    else if (n % 2 == 0) //even case
    {
        count++;
        collatz(n / 2);
    }
    else
    {
        count++;
        collatz((3 * n) + 1);
    }
    return count;
}


