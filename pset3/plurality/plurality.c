#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (vote(name) == false)
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
// If name matches one of the names of the candidates in the election, then update that candidate’s vote total to account for the new vote. The vote function in this case should return true to indicate a successful ballot.
bool vote(string name)
{
    // use a for loop to go through every candidate and check that once the name matches add one then return immediately, if not check the next name
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes = candidates[i].votes + 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // using 2 for loops coz i need 2 increments of candidates at diff rates
    // j will lock the candidate on the left while i will allow the candidate number on the right to continue to increase
    // only when i has reached the candidate number, then can j increase
    for (int j = 0; j < candidate_count; j++)
    {
        int counter = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            // the use of >= is impt coz it accounts for ties in the highest score
            if (candidates[j].votes >= candidates[i].votes)
            {
                counter++;
            }
            // the winner will ALWAYS have a counter score equal to the candidate number because that candidate will be everyone, including itself
            // even if there is a tie, they will both have the full score as their votes will "beat"(equals to) each other as well as everyone else
            if (counter == candidate_count)
            {
                printf("%s\n", candidates[j].name);
            }
        }
    }


    return;
}

