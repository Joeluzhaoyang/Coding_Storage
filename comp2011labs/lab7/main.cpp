#include <iostream>
#include <cstring>
#include "lab7.h"
using namespace std;



int main()
{
   // Create an election
   Election election;
   int numCandidates, numVoters;

   cout << "===============================" << endl;
   cout << " Welcome to the voting system! " << endl;
   cout << "===============================" << endl;
   cout << "Preparing ... " << endl;
   do
   {
      cout << "Enter how many candidates will run for the election: \n";
      cin >> numCandidates;
      cout << "Enter how many more voters: \n";
      cin >> numVoters;
   } while (((numCandidates + numVoters) > MAX_SIZE) || (numCandidates <= 0));
   cout << "\n";

   // the setup phase
   setup(election, numCandidates, numVoters);

   // print candidates and voters
   printParticipants(election);

   int currentId;
   int voteCount = 0;

   // voting
   cout << "Voting starts ..." << endl;
   char cmd;
   do
   {
      cout << "Enter the voter id to start voting:\n"; //candidates can also vote
      cin >> currentId;
        if (currentId>=(numCandidates+numVoters))
        {
            cout << "Invalid voter ID!" << endl;
        }
        else 
        {voting(election, currentId);}

      cout << "Continue with the next voter? (y/n) ";
      cin >> cmd;
   } while ((cmd == 'y') || (cmd == 'Y'));

   cout << "Tallying votes ..." << endl;
   //the result-tallying phase
   resultTallying(election);

   cout << "End of the election!" << endl;
   return 0;
}