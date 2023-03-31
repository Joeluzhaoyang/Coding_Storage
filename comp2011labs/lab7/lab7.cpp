/* Lab 7: Voting -- An election system
 * Struct and separate compilation
 * File: lab7_skeleton.cpp
 */

/* Task 4: After finishing the coding task 1 to task 3
 * separate the single lab7.cpp to 3 files
 *  - lab7.h 
 *  - main.cpp with definition of main()
 *  - lab7functions.cpp with definitions of all other functions
 *  - (optional) Makefile
 * You will need to demo your lab 7 with separate compilation 
 */

#include <iostream>
#include <cstring>
#include "lab7.h"
using namespace std;



char names[MAX_SIZE][MAX_STRING_LENGTH] = {"JoeBiden", "QueenElizabethII", "Putin", "Trudeau", "XiJinping", "Macron", "KimJongun", "CarrieLam", "Zelenskyy", "Trump"};
/* Helper function
 * Print participants
 * Parameter:
 *    - election: the Election struct object
 */
void printParticipants(const Election &election)
{

   for (int i = 0; i < election.numCandidates + election.numVoters; i++)
   {
      cout << "ID: " << election.participants[i].id << "\tName:" << election.participants[i].name << "\t";
      if (election.participants[i].role == CANDIDATE)
         cout << "Role: Candidate" << endl;
      else
         cout << "Role: Voter" << endl;
   }
}

/* Task 1: 
 * Setup the election
 * - initialize all the member variables of the Election object
 * Parameters:
 *    - election: a Election struct object
 * Note:
 *    - id for voter/candidate are assigned as 1, 2, 3, ...in sequence
 *    - name for voter/candidate are copied from names[][] in sequence
 *    - role: CANDIDATE or VOTER (note candidate can also vote)
 *    - hasVoted = false, voteCount = 0
 */
void setup(Election &election, int numCandidates, int numVoters)
{
    election.numCandidates=numCandidates;
    election.numVoters=numVoters;
    for(int i=0;i<numCandidates;i++)
    {
        election.participants[i].id=i;
        strcpy(election.participants[i].name,names[i]);
        election.participants[i].role=CANDIDATE;
        election.participants[i].hasVoted=false;
        election.participants[i].voteCount=0;
    }
    for(int j=numCandidates;j<numCandidates+numVoters;j++)
    {
        election.participants[j].id=j;
        strcpy(election.participants[j].name,names[j]);
        election.participants[j].role=VOTER;
        election.participants[j].hasVoted=false;
        election.participants[j].voteCount=0;    
    }
}



/* Task 2:
 * Casting votes to some candidates by a specific voter given the voter id
 * Parameters:
 *    - election: the Election struct object
 *    - voterId: the voter's id
 * Note:
 *    validates the following 
 *    - voter id has to be valid, note candidate can also vote
 *    - candidate id has to be valid
 *    - voter can only vote once
 */
void voting(Election &election, int voterID)
{
    int target=0;
    cout << "Enter the candidate id you want to vote for:";
    cin >> target;
    
    if ( (election.participants[voterID].hasVoted==false) && (election.participants[target].role==CANDIDATE)&&(target<election.numCandidates+election.numVoters) )
    {
        election.participants[target].voteCount+=1;
        election.participants[voterID].hasVoted=true;
        cout << "You vote for " << election.participants[target].id << " " << election.participants[target].name << endl;
    }
    else if(target>=election.numCandidates+election.numVoters)
    {
        cout << "No such a target!" << endl;
    }
    else if(election.participants[target].role!=CANDIDATE)
    {
        cout << "This person is not the candidate!" << endl;
    }
    else if(election.participants[voterID].hasVoted==true)
    {
        cout << "The voter has already voted!" << endl;
    }
    
}

/* Task 3:
 * Output the number of votes for each candidate
 * and announce the winner by finding who has the maximum number of votes
 * Parameters:
 *    - election: the Election struct object
 * Note: if there is more than 1 candidate has the same number of maximum votes,
 * announce it as a tie election.
 */
void resultTallying(const Election &election)
{
    int max=0;
    int array[election.numCandidates+election.numVoters]={0};
    for(int i=0;i<election.numCandidates+election.numVoters;i++)
    {
        if (election.participants[i].role==CANDIDATE)
        {
           cout << "ID: " << election.participants[i].id << "   Name: " << election.participants[i].name 
           << "   Votes:" << election.participants[i].voteCount << endl;  
        }
    }
    for(int j=election.numCandidates+election.numVoters;j>=0;j--)
    {
        for(int k=0;k<election.numCandidates+election.numVoters;k++)
        {
            if(election.participants[k].voteCount==j)
            {
                array[max]=election.participants[k].id;
                max++;
            }
        }
        if(max!=0)
        {
            break;
        }
    }
    for(int p=1;p<=max;p++)
    {
        cout << "Winner" << p << ": " << election.participants[array[p-1]].name << endl;
    }

    

}

