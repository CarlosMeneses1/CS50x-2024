def main():
    # Ask user how much change is owned
    change = get_change()

    # Calculate and Print change
    print(calculate_change(change))


def get_change():
    # Ask user for a valid number
    while True:
        try:
            change = float(input("Change: "))
            if change > 0:
                return change
        except ValueError:
            pass


def calculate_change(change):

    coins = 0

    # Calculate the amount of coins for the change
    while change > 0.0:
        if change >= 0.25:
            change = round(change - 0.25, 2)
        elif change >= 0.10:
            change = round(change - 0.10, 2)
        elif change >= 0.05:
            change = round(change - 0.05, 2)
        elif change >= 0.01:
            change = round(change - 0.01, 2)
        coins += 1
    return coins


main()
