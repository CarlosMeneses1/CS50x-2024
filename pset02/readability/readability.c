#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calculate_coleman_liau_index(float l, float w, float s);

int main(void)
{
    // Prompt user for a text
    string s = get_string("Text: ");

    // Declare variable to save 's' length
    int l = strlen(s);

    // Count the number of letters, words and sentences from text
    float letters = count_letters(s);
    float words = count_words(s);
    float sentences = count_sentences(s);

    // Calculate Coleman-Liau index
    int index = calculate_coleman_liau_index(letters, words, sentences);

    // Print the text grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int c = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            c++;
        }
    }
    return c;
}

int count_words(string text)
{
    int c = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (isspace(text[i]))
        {
            c++;
        }
    }
    return c + 1;
}

int count_sentences(string text)
{
    int c = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            c++;
        }
    }
    return c;
}

int calculate_coleman_liau_index(float l, float w, float s)
{
    float L = ((l / w) * 100);
    float S = ((s / w) * 100);
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}
