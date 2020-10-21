#include <stdio.h>
#include <cs50.h>

void build(int h);

int main(void)
{
    int n = get_int("Height: ");
    build(n);
}
void build(int h)
{
    // if nothing return
    if (h == 0)
    {
        return;
    }

    // Draw pyramid of height h - 1
    build(h - 1);

    // Draw one more row of width h
    for (int i = 0; i < h; i++)
    {
        printf("#");
    }
    printf("\n");
}

