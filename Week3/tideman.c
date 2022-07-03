#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
bool has_circle(int start, int end);
bool has_road(int start, int end);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (preferences[i][j] < preferences[j][i]) {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int array[pair_count];
    int array_index[pair_count];
    for (int i = 0; i < pair_count; i++) {
        /* Desperate fault */
        array[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    // for (int i = 0; i < pair_count - 1; i++) {
    //     for (int j = 0; j < pair_count - i - 1; j++) {
    //         if (array[j] < array[j + 1]) {
    //             int tmp = array[j];
    //             array[j] = array[j + 1];
    //             array[j + 1] = tmp;
    //             pair tmp1 = pairs[j];
    //             pairs[j] = pairs[j + 1];
    //             pairs[j + 1] = tmp1;
    //             /* Can I swap like this? */
    //         }
    //     }
    // }
    for (int i = 0; i < pair_count; i++) {
        int max = i;
        for (int j = i + 1; j < pair_count; j++) {
            if (array[j] > array[max]) {
                max = j;
            }
        }
        int tmp1 = array[i];
        array[i] = array[max];
        array[max] = tmp1;
        pair tmp = pairs[max];
        pairs[max] = pairs[i];
        pairs[i] = tmp;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // int i = 0;
    // while (!has_circle(pairs[i].loser, pairs[i].winner && i != pair_count)) {
    //     locked[pairs[i].winner][pairs[i].loser] = true;
    //     i++;
    // }
    // return;
    // 错的原因在于中途添边会导致循环终止，后面的边就添不上了
    for (int i = 0; i < pair_count; i++)
    {
        if (!has_circle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

bool has_circle(int start, int end) {
    if (start == end) {
        return true;
    }

    for (int i = 0; i < candidate_count; i++) {
        if (locked[start][i]) {
            if (has_circle(i, end)) {
                return true;
            }
        }
    }

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) {
        bool isSource = true;
        for (int j = 0; j < candidate_count; j++) {
            if (i == j) {
                continue;
            }
            if (!has_circle(i, j)) {
                isSource = false;
                break;
            }
        }
        if (isSource) {
            printf("%s\n", candidates[i]);
            return;
        }

    }
    return;
    // for (int i = 0; i < candidate_count; i++)
    // {
    //     bool isLoser = false;
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         // j -> i
    //         if (locked[j][i])
    //         {
    //             isLoser = true;
    //             break;
    //         }
    //     }
    //     if (!isLoser)
    //     {
    //         printf("%s\n", candidates[i]);
    //         break;
    //     }
    // }
    // return;
}