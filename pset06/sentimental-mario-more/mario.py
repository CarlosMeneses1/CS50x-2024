def main():
    # Promtp to user for a height
    h = get_height()

    # Make a pyramid with height 'h'
    make_pyramid(h)


def get_height():
    # Ask user for a valid height
    while True:
        try:
            h = int(input("Height: "))
            if h > 0 and h < 9:
                return h
        except ValueError:
            pass


def make_pyramid(h):
    # Print a pyramid with a height 'h'
    for height in range(h):
        # First half of the pyramid
        for space in range(h - 1 - height):
            print(" ", end="")
        for block in range(height + 1):
            print("#", end="")

        print("  ", end="")

        # Second half of the pyramid
        for block in range(height + 1):
            print("#", end="")
        print()


main()
