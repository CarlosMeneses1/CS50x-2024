#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for a credit card number
    long number = get_long("Number: ");

    // Check the number length
    long pivot = number;
    int length = 0;

    while (pivot > 0)
    {
        length++;
        pivot = pivot / 10;
    }

    // --- Calculate checksum ---
    // 1. Multiply every two number by 2, starting with the second to the last
    // 2. Sum each product between then
    long checksum = 0;
    long remainder = 1;
    long x = 100;
    long y = 10;
    int c = 0;

    while (c < length)
    {
        pivot = number % x;
        remainder = pivot / y;
        remainder = remainder * 2;

        if (remainder > 9)
        {
            pivot = remainder % 10;
            remainder = remainder / 10;
            checksum = checksum + pivot + remainder;
        }
        else
        {
            checksum = checksum + remainder;
        }
        x = x * 100;
        y = y * 100;
        c++;
    }

    // 3. Take the result of the previuo sum and add then with the numbers that were not multiplied
    // by two
    remainder = 1;
    x = 10;
    y = 1;
    c = 0;

    while (c < length)
    {
        pivot = number % x;
        remainder = pivot / y;
        checksum = checksum + remainder;

        x = x * 100;
        y = y * 100;
        c++;
    }

    // 4. Take the result of the previous sum and check if the second number is equal to '0'
    // 5. if is TRUE, check the credit card type according to the number of digits and their initial
    // digits
    int check;
    int a = checksum % 10;

    if (a == 0)
    {
        if (length == 15)
        {
            check = number / 10000000000000;
            if (check == 34 || check == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (length == 13)
        {
            check = number / 1000000000000;
            if (check == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (length == 16)
        {
            check = number / 1000000000000000;
            if (check == 5)
            {
                check = number / 100000000000000;
                if (check == 51 || check == 52 || check == 53 || check == 54 || check == 55)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else if (check == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
