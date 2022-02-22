#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();
        printf("%s total votes is %i\n", candidates[0].name, candidates[0].votes);
        printf("%s total votes is %i\n", candidates[1].name, candidates[1].votes);
        printf("%s total votes is %i\n", candidates[2].name, candidates[2].votes);

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        // Restart loop again
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int index = i;
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = index;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //make an array to store the index of eliminated candidates
    //declaring an unknown array coz idk how many elimnated there will be
    //i am putting in fake values coz if u leave the array blank it might give 0
    int elim[9] = {101, 102, 103, 104, 105, 106, 107, 108, 109,};
    int x = 0;
    int j;
    for (int c = 0; c < candidate_count; c++)
    {
        //if a candidate had been eliminated, store its index value in an array called elim
        if (candidates[c].eliminated == true)
        {
            elim[x] = c;
            x++;
        }
    }

    //for every candidate,
    for (int c = 0; c < candidate_count; c++)
    {
        //set j to 0 each time i am looking at a new candidate, so as to be able to always look at rank 1 first
        j = 0;
        //if that candidate is not eliminated
        if (candidates[c].eliminated == false)
        {
            //for every voter's ballot
            for (int i = 0; i < voter_count; i++)
            {
                //if the first rank is not eliminated, add one to his score
                if (preferences[i][j] == c)
                {
                    candidates[c].votes = candidates[c].votes + 1;
                }
                else
                {
                    //going through array of elim index to check one by one if the current preference matches
                    for (int a = 0; a < candidate_count; a++)
                    {
                        //if the preference matches an eliminated candidate
                        while (preferences[i][j] == elim[a])
                        {
                            //look at the next rank
                            j++;
                            //if that index is not c, just forget it and move on to the next c
                            if (preferences[i][j] == c)
                            {
                                candidates[c].votes = candidates[c].votes + 1;
                            }
                        }

                    }
                }
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2)
        {
            printf("Winner is %s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //m is a variable which will be the max number of votes possible
    int m = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            //if the votes under this candidate is lesser than m, its votes value will be stored as the new m
            //this alogrithm proofreads itself to make sure its taking the smallest m value out of all the candidates
            if (candidates[i].votes < m)
            {
                m = candidates[i].votes;
            }
        }
    }
    return m;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    //in and out will be a counter as to the eliminated ppl and those with the min score
    //if it is all tied up, the everyone should have the min score except those who are eliminated
    //hence if in and out is equal to candidate count then it must be all tied up
    int in = 0;
    int out = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes == min)
            {
                in = in + 1;
            }
        }
        else
        {
            out = out + 1;
        }
    }
    if (in + out == candidate_count)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
