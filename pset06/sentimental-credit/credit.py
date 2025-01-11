import sys


def main():
    # Prompt user for a credit card number
    credit_card = input("Number: ")

    # Calculate Luhn’s Algorithm
    check_sum = calculate_check_sum(credit_card)

    # If is not a valid credit card number, exit
    if not is_valid_credit_card(check_sum):
        print("INVALID")
        sys.exit()

    # Print the type of credit card
    print_credit_card(credit_card)


def calculate_check_sum(number):

    # Flipping credit card number
    reversed_number = number[::-1]
    check_sum = 0

    # Multiply every two number by 2, starting with the second to the last
    for digit in reversed_number[1::2]:

        digit = int(digit) * 2

        # If the result is greater than 10, add each digit between them
        if digit > 9:
            digit1 = digit // 10
            digit2 = digit % 10
            check_sum += digit1 + digit2
        # Else, sum digit
        else:
            check_sum += digit

    # Take the result of the previus sum and add the numbers that were not multiplied
    for digit in reversed_number[0::2]:
        check_sum += int(digit)

    return check_sum


def is_valid_credit_card(number):

    # If the second number of the result of Luhn’s Algorithm is 0, is a valid credit card number
    if (number % 10) == 0:
        return True
    # Else, it doesn't
    else:
        return False


def print_credit_card(number):

    length = len(number)

    # Check the lenght and the initial digits of the credit card number and return the type
    if length == 15 and int(number[:2]) in [34, 37]:
        print("AMEX")
    elif length == 16 and int(number[:2]) in [51, 52, 53, 54, 55]:
        print("MASTERCARD")
    elif (length == 13 or length == 16) and int(number[:1]) == 4:
        print("VISA")
    else:
        print("INVALID")


main()
