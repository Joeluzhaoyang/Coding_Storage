#include <iostream> 
#include <cstdlib>
#include <cstring>
using namespace std;

const int MAX_SIZE = 10;
const int MAX_STRING_LENGTH = 20;


enum Role
{
   CANDIDATE,
   VOTER
};
struct Participant
{
   int id;
   char name[MAX_STRING_LENGTH];
   Role role;     // CANDIDATE or VOTER
   bool hasVoted; // true if voter has voted, false otherwise
   int voteCount; // number of votes received if the participant is a candidate of election, initilized as 0
};
struct Election
{
   Participant participants[MAX_SIZE];
   int numCandidates; //note candidates can also vote
   int numVoters;
   // the candidates will occupy the first numCandidates elements in the participants array,
   // while the other voters will occupy the next numVoters elements in the participants array
};

void printParticipants(const Election &election);
void setup(Election &election, int numCandidates, int numVoters);
void voting(Election &election, int voterID);
void resultTallying(const Election &election);