import csv
from sys import argv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("python dna.py data.csv sequence.txt")
        sys.exit(1)
    if "databases" not in argv[1] and "sequences" not in argv[2]:
        print("python dna.py data.csv sequence.txt")
        sys.exit(2)

    # TODO: Read database file into a variable
    sequences = dict()

    database = open(argv[1], "r")
    reader = csv.reader(database)
    for row in reader:
        headLine = row  # not subscriptable 所以不能直接取下标
        break
    length = len(headLine)
    for i in range(1, length):
        sequences[headLine[i]] = 0

    # 下面一行不需要？？？
    # 难道是不迭代到底不重头来？
    # next(reader)
    
    databases = dict()
    for row in reader:
        person_sequence = list()
        for i in range(1, length):
            person_sequence.append(int(row[i]))
        databases[row[0]] = person_sequence

    # TODO: Read DNA sequence file into a variable
    person = open(argv[2], "r")
    for row in person:
        dna_person = row
        break


    # TODO: Find longest match of each STR in DNA sequence
    for sequence in sequences:
        sequences[sequence] = longest_match(dna_person, sequence)


    # TODO: Check database for matching profiles
    for person1 in databases:
        flag = True
        for i, val in enumerate(databases[person1]):
            # 需要加list，同样还是不能直接取下标
            if val != list(sequences.values())[i]:
                flag = False
        if flag:
            print(person1)
            break
    if not flag:
        print("No match")


    database.close()
    person.close()
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
