def main():
    # Prompt to the user a height for a pyramid
    h = get_height()

    # Make pyramid with height 'h'
    make_pyramid(h)


def get_height():
    # Ask the user for a valid height
    while True:
        try:
            h = int(input("Height: "))
            if h > 0 and h < 9:
                return h
        except ValueError:
            pass


def make_pyramid(h):
    # Print a pyramid with height 'h'
    for height in range(h):
        for space in range(h - 1 - height):
            print(" ", end="")
        for block in range(height + 1):
            print("#", end="")
        print()


main()
