#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string key);
int rotate(char c, int n);

int main(int argc, string argv[])
{
    // Make sure the command line only has '1' item
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Make sure the 'key' only has digits
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Change 'key' from string type to int type
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string text = get_string("plaintext:  ");

    // Rotate each 'text' character with 'key'
    int length = strlen(text);

    printf("ciphertext: ");
    for (int i = 0; i < length; i++)
    {
        printf("%c", rotate(text[i], key));
    }
    printf("\n");
}

bool only_digits(string key)
{
    // Declare variable to save key's length
    int length = strlen(key);

    // Iterate through each 'key' item to check if every 'key' item is a digit
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(key[i]))
        {
            return false;
        }
    }
    return true;
}

int rotate(char c, int n)
{
    int rotate;

    /* 1. Change 'c' position from ASCCI to alphabetic order
       2. Rotate 'c', 'n' times
       3. Return 'c' change. From alphabetic order to ASCCI */
    if (isupper(c))
    {
        rotate = ((c - 'A') + n) % 26;
        return rotate + 'A';
    }
    else if (islower(c))
    {
        rotate = ((c - 'a') + n) % 26;
        return rotate + 'a';
    }
    else
    {
        return c;
    }
    return c;
}
