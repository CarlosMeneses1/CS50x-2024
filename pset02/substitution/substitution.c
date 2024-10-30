#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid_length_key(string k);
bool only_alphabetic(string k);
bool no_repeat_characters(string k);
char encrypt(char c, string k);

int main(int argc, string argv[])
{
    // -- 'key' validation --
    // Make sure the command line only has '1' element
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Make sure the 'key' is only 26 characters long
    if (!valid_length_key(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Make sure the 'key' has only alphabetic characters
    if (!only_alphabetic(argv[1]))
    {
        printf("Key must contain alphabetic characters.\n");
        return 1;
    }

    // Make sure the 'key' does not have repeated characters
    if (!no_repeat_characters(argv[1]))
    {
        printf("Key must no contain repeated characters.\n");
        return 1;
    }

    // Declare variable to save 'key'
    string key = argv[1];

    // Prompt user for plaintext
    string text = get_string("plaintext:  ");
    int length = strlen(text);

    // Encrypt 'text'
    printf("ciphertext: ");
    for (int i = 0; i < length; i++)
    {
        printf("%c", encrypt(text[i], key));
    }
    printf("\n");
}

bool valid_length_key(string k)
{
    // Declare variable to save key's length
    int length = strlen(k);

    // Check the condition. Key's length must contain only 26 characters
    if (length != 26)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool only_alphabetic(string k)
{
    // Declare variable to save key's length
    int length = strlen(k);

    // Iterate through each 'key' item to check if every 'key' item is an alphabetic character
    for (int i = 0; i < length; i++)
    {
        if (!isalpha(k[i]))
        {
            return false;
        }
    }
    return true;
}

bool no_repeat_characters(string k)
{
    // Declare vatiable to save key's length
    int length = strlen(k);

    // Iterate through each 'key' item to check if there is not a repeated item
    for (int i = 0; i < length; i++)
    {
        for (int j = 1 + i; j < length; j++)
        {
            if (k[i] == k[j])
            {
                return false;
            }
        }
    }
    return true;
}

char encrypt(char c, string k)
{
    /* Return 'c' but in the alphabetic position of 'key'
       - Keeping lower and upper case
       - Keeping numbers or special characters */
    if (isupper(c))
    {
        return toupper(k[c - 'A']);
    }
    else if (islower(c))
    {
        return tolower(k[c - 'a']);
    }
    return c;
}
