#include <cs50.h>
#include <stdio.h>

int calculate_change(int x);

int main(void)
{
    // Prompt user for an amount of money. Check the condition 'money > 0'
    int money;
    do
    {
        money = get_int("Change owed: ");
    }
    while (money < 1);

    // Calculate quarters, dimes, nickels, pennies according  to the amount of money
    int change = calculate_change(money);

    // Print the total change
    printf("%i\n", change);
}

int calculate_change(int x)
{
    int change = 0;

    while (x > 0)
    {
        if (x >= 25)
        {
            change++;
            x = x - 25;
        }
        else if (x >= 10)
        {
            change++;
            x = x - 10;
        }
        else if (x >= 5)
        {
            change++;
            x = x - 5;
        }
        else if (x >= 1)
        {
            change++;
            x--;
        }
    }
    return change;
}
