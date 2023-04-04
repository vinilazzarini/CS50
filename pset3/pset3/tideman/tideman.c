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
    // TODO
    for(int p = 0; p < candidate_count; p++){
        if (strcmp(name,candidates[p]) == 0){
            ranks[rank] = p;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for(int i = 0; i < candidate_count; i++){
        for(int j = i+1; j < candidate_count; j++){
            preferences[ranks[i]][ranks[j]]++;
        }
    } 
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;
    for(int i = 0; i < candidate_count; i++){
        for(int j = i+1; j < candidate_count; j++){

            if (preferences[i][j] > preferences[j][i]){
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }else{
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;    
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    pair tmp;
    for(int p = 0; p < pair_count;p++){
        for(int q = p + 1; q < pair_count; q++){
            if (preferences[pairs[p].winner][pairs[p].loser] < preferences[pairs[q].loser][pairs[q].winner]){
                tmp = pairs[p];
                pairs[p] = pairs[q];
                pairs[q] = tmp;
            }   
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
bool tem_ciclo(int winner, int loser)
{
    //Verify if arrow comebacks to first
    if (locked[loser][winner] == true){
        return true; 
    }
    
    //checks if there is any candidate that the loser points out that may return to the winner
    for(int p = 0; p < candidate_count;p++){
        if(locked[loser][p] == true && tem_ciclo(winner,p)){
            return true;
        }
    }
   
   return false;
    
}


void lock_pairs(void)
{
    // TODO
    for(int p = 0; p < pair_count;p++){
        if(!tem_ciclo(pairs[p].winner,pairs[p].loser)){
            locked[pairs[p].winner][pairs[p].loser] = true;
        }
    }    
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int found = 0;
    for(int i = 0; i < candidate_count;i++){
        for(int j = 0; j < candidate_count; j++){
            if (locked[j][i] == true){
                found++;
            }
            
        }
        if(found == 0){
            printf("Winner is: %s\n", candidates[i]);
        }else{
            found = 0;
        }
    }
    return;
}

