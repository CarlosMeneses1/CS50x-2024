#include <cs50.h>
#include <stdio.h>

void make_pyramid(int h);

int main(void)
{
    // Prompt user the pyramid heihgt
    // Check the condition: The height must be between 1 and 8
    int n;
    do
    {
        n = get_int("Heihgt: ");
    }
    while (n < 1 || n > 8);

    // Print a pyramid  with 'n' heihgt
    make_pyramid(n);
}

void make_pyramid(int h)
{
    int c = h - 1;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < h - c; j++)
        {
            printf("#");
        }

        printf("  ");

        for (int j = 0; j < h - c; j++)
        {
            printf("#");
        }
        c--;
        printf("\n");
    }
}
