#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculate_score(string s);

int main(void)
{
    // Prompt user for two pharases
    string phrase1 = get_string("Player 1: ");
    string phrase2 = get_string("Player 2: ");

    // Calculate the score of each phrase
    int player1 = calculate_score(phrase1);
    int player2 = calculate_score(phrase2);

    // Print the winner
    if (player1 > player2)
    {
        printf("Player 1 wins!\n");
    }
    else if (player1 < player2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int calculate_score(string s)
{
    // Declare score array for each alphabetic letter
    const int scores[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                            1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    // Declare variables for calculate the score
    int length = strlen(s);
    int counter = 0;
    int index = 0;

    // Iterate throught each letter of 's' and assing a score
    for (int i = 0; i < length; i++)
    {
        if (isalpha(s[i]) != 0)
        {
            index = toupper(s[i]) - 65;
            counter += scores[index];
        }
        else
        {
            return counter;
        }
    }
    return counter;
}
