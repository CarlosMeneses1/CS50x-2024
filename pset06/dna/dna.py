import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: dna.py databases.csv sequences.txt")
        sys.exit()

    # Read database file into a variable
    with open(sys.argv[1]) as database:
        reader = csv.DictReader(database)

        headers = reader.fieldnames
        content_database = list(reader)

        # Read DNA sequence file into a variable
        with open(sys.argv[2], "r") as sequences:
            content_sequences = sequences.read()

            # Find longest match of each STR in DNA sequence
            results = []

            for header in headers[1:]:
                results.append(longest_match(content_sequences, header))

            # Check database for matching profiles
            for person in range(len(content_database)):
                match = 0
                for header in range(1, len(headers)):
                    if int(content_database[person][headers[header]]) == results[header - 1]:
                        match += 1
                    if match == len(results):
                        print(content_database[person]["name"])
                        sys.exit(0)
            print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
