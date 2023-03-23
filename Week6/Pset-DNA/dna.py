import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Incorrecr number of arguments.")
        sys.exit(1)

    # TODO: Read database file into a variable
    database = []
    database_file = sys.argv[1]
    with open(database_file) as file:
        reader = csv.DictReader(file)
        # Save each row
        for row in reader:
            database.append(row)

    # Create a list of all DNAs
    DNA = [dna for dna in database[0].keys()][1:]

    # TODO: Read DNA sequence file into a variable
    dna_file = sys.argv[2]
    with open(dna_file, 'r') as file:
        dna = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    # Save the longest repetition of each DNA to a dict
    results = {}
    for STR in DNA:
        longest = longest_match(dna, STR)
        results[STR] = longest

    # TODO: Check database for matching profiles
    for person in database:
        # Check a person's DNA matches with database record
        match = 0
        for dna in DNA:
            if int(person[dna]) == results[dna]:
                match += 1
        if match == len(DNA):
            print(person["name"])
            sys.exit(0)
    print("No match")


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
