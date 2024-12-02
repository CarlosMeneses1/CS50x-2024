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
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int winner, int loser);

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
    // Iterate through each candidate and check:
    for (int i = 0; i < candidate_count; i++)
    {
        // If the name given by the voter match with any candidate's name, update ith preferences in
        // 'ranks[rank]' and return true
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // Else, return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Iterate through 'ranks[]' and add +1 in 'preference[][]' based on position among 'ranks[]'
    // items
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
    // Iterate through each element of the upper triangle of the two-dimensional array (matrix)
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Compare each element to its opposite (its pair). Depending on the result, update the
            // array 'pairs[]'
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
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
    int comp1, comp2, temp1, temp2;
    bool swap;

    // Bubble Sort. Decreasing order of strength of victory
    do
    {
        swap = false;

        for (int i = 0; i < pair_count - 1; i++)
        {
            comp1 = preferences[pairs[i].winner][pairs[i].loser] -
                    preferences[pairs[i].loser][pairs[i].winner];
            comp2 = preferences[pairs[i + 1].winner][pairs[i + 1].loser] -
                    preferences[pairs[i + 1].loser][pairs[i + 1].winner];

            if (comp1 < comp2)
            {
                temp1 = pairs[i].winner;
                temp2 = pairs[i].loser;

                pairs[i].winner = pairs[i + 1].winner;
                pairs[i].loser = pairs[i + 1].loser;

                pairs[i + 1].winner = temp1;
                pairs[i + 1].loser = temp2;

                swap = true;
            }
        }
    }
    while (swap);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

bool cycle(int winner, int loser)
{
    if (locked[loser][winner] == true)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {

        if (locked[i][winner] == true)
        {
            return cycle(i, loser);
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    int n = 0;
    bool source = false;
    string winner;

    do
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][n] == true)
            {
                source = false;
                break;
            }
            else
            {
                winner = candidates[n];
                source = true;
            }
        }
        n++;
    }
    while (!source);

    printf("%s\n", winner);
    return;
}
