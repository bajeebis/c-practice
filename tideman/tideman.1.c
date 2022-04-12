#include <cs50.h>
#include <stdio.h>
#include <strings.h>

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
}
pair;

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

int check_true(int x);
int winner_check(int x, int winner);
int incycle(int x, int y);

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

    printf("%i\n", MAX * (MAX - 1) / 2);

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

    for (int i = 0; i < pair_count; i++)
    {
        printf("%i and %i is %s\n", pairs[i].winner, pairs[i].loser, locked[pairs[i].winner][pairs[i].loser] ? "true" : "false");

    }

    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        // make an if here where it gets the previous rank or after and see if it's the same
        if (strcasecmp(name, candidates[i]) == 0)
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
    // TODO
    // Update preference[i][j]. Example: preference[Alice][Bob] where voters prefer alice over bob; [i][j] = vote distance.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (ranks[i] == ranks[j])
            {
                continue;
            }
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]] += 1;
                /* CONTINUE HERE: RECHECK IF MAY MALI BEFORE PROCEEDING */
            }
        }
    }
    // 0 for temporary
    //return 0;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO

    int x = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i] && i != j)
            {
                pairs[x].winner = i;  // FIX THIS
                pairs[x].loser = j;

                x += 1;
            }
        }
    }
    pair_count = x;
    printf("\tPair count: %i\n", pair_count);
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int temp_winner, temp_loser, winner, loser;
    int swap_counter = -1;
    while(swap_counter != 0)
    {
        swap_counter = 0;
       for (int i = 0; i < pair_count - 1; i++)
       {
           // Assign to adhere 80 char limit
           winner = pairs[i].winner;
           loser = pairs[i].loser;
           temp_winner = pairs[i + 1].winner;
           temp_loser = pairs[i + 1].loser;

           // Loop and check then sort
           if (preferences[winner][loser] < preferences[temp_winner][temp_loser])
           {
               pairs[i].winner = temp_winner;
               pairs[i].loser = temp_loser;
               pairs[i + 1].winner = winner;
               pairs[i + 1].loser = loser;

               swap_counter += 1;
           }
       }
    }
    // 0 for temporary
    //return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    int marked[pair_count - 1];
    incycle(0, 0);

    //int j = pair_count - 1;
    for (int j = pair_count - 1; j > 0; j--)
    {
        for (int i = 0; i < j; i++)
        {
            printf("%i:%i\n", j, i);
            if (preferences[i][j] > preferences[j][i])
            {
                locked[i][j] = false;
                printf("\t%i:%i\n", j, i);
            }
        }
        //j--;
    }

}

// Print the winner of the election
void print_winner(void)
{
    // TODO
}

int incycle(int x, int y)
{
    if (x < pair_count && y < pair_count)
    {
        locked[pairs[x].winner][pairs[y].loser] = true;
        // If the loser is the winner of the previous, then change it
        for (int i = 0; i < y; i++)
        {
            if (pairs[y].loser == pairs[i].winner && i != y)
            {
                if (preferences[pairs[x].loser][pairs[y].winner] < preferences[pairs[i].winner][pairs[i].loser])
                {
                    //locked[pairs[y].loser][pairs[y].winner] = false;
                    incycle(x + 1, y + 1);
                }
                else
                {
                    locked[pairs[y].loser][pairs[y].winner] = false;
                    incycle(x + 1, y + 1);
                }
            }
            else
            {
                incycle(x + 1, y + 1);
            }
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

int winner_check(int x, int winner)
{
    if (x < pair_count)
    {
        for (int i = 0; i < pair_count; i++)
        {
            if (locked[i][pairs[x].winner] == true && i != x)
            {
                winner_check(x + 1, winner);
            }
            else
            {
                return pairs[x].winner;
            }
        }

    }
    return 0;
}
