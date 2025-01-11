def main():
    # Prompt user for a text
    text = input("Text: ")

    # Count the letters of the text
    letters = count_letters(text)

    # Count the words of the text
    words = count_words(text)

    # Count the sentences of the text
    sentences = count_sentences(text)

    # Calculated the Coleman-Liau index
    index = calculate_coleman_index(letters, words, sentences)

    # Print the grade of the text
    print_grade(index)


def count_letters(text):

    letters = 0

    # Iterate through the text and count the letters
    for caracter in text:
        if caracter.isalpha():
            letters += 1
    return letters


def count_words(text):

    words = 0

    # Iterate through the text and count the words
    for caracter in text:
        if caracter.isspace():
            words += 1
    return words + 1


def count_sentences(text):

    sentences = 0

    # Iterate through the text and count the sentences
    for caracter in text:
        if caracter in ['.', '!', '?']:
            sentences += 1
    return sentences


def calculate_coleman_index(letters, words, sentences):

    # Calculate the Coleman-Liau index
    L = (letters / words) * 100
    S = (sentences / words) * 100

    return round(0.0588 * L - 0.296 * S - 15.8)


def print_grade(index):

    # Print the grade of the text based in the Coleman-Liau index
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


main()
