#include <iostream>
using namespace std;

int main() {
   // Initialize the puzzle.
   char pos1 = 'B', pos2 = 'C', pos3 = 'A', pos4 = '*';
   int temp;
   char choice;
   int round = 0;
   
   // Start the game.
   cout << "Welcome to the Sliding Puzzle Game!" << endl;
   
   // Task 1: modify the condition of while loop
   while ( pos1!='A' || pos2!='B' || pos3!='C' || pos4!='*') {
      
      round++;
      cout << "Round " << round << ": " << endl;
      cout << "Position info:" << endl;
      cout << "12" << endl << "34" << endl;
      cout << "Puzzle status:" << endl;
      cout << pos1 << pos2 << endl;
      cout << pos3 << pos4 << endl;

      do{cout << "Enter a position number between 1 to 4 to slide:" << endl;
      cin >> choice;
      if(choice!='1'&&choice!='2'&&choice!='3'&&choice!='4')
      {
         cout << "Invalid Input" << endl;
      }
      }
      while(choice!='1'&&choice!='2'&&choice!='3'&&choice!='4');

      // Task 2: check the input


      // Task 3: slide the chosen block
      // We show the example for position 1, please finish the other 3 positions.
      switch (choice){
         case '1':
            if (pos1 == '*') {round--;cout << "the input is not that valid." << endl;}
            if (pos1 != '*') {
               if (pos2 == '*') { temp = pos2; pos2 = pos1; pos1 = temp; }
               else if (pos3 == '*') { temp = pos3; pos3 = pos1; pos1 = temp; }
               else if (pos4 == '*') {round--;cout << "the input is not that valid." << endl;}
            }
            break;
         case '2':
            if (pos2 == '*') {round--;cout << "the input is not that valid.." << endl;}
            if (pos2 != '*') {
               if (pos1 == '*') { temp = pos1; pos1 = pos2; pos2 = temp; }
               else if (pos4 == '*') { temp = pos4; pos4 = pos2; pos2 = temp; }
               else if (pos3 == '*') {round--;cout << "the input is not that valid." << endl;}
            }
            break;
         case '3':
            if (pos3 == '*') {round--;cout << "the input is not that valid." << endl;}
            if (pos3 != '*') {
               if (pos1 == '*') { temp = pos1; pos1 = pos3; pos3 = temp; }
               else if (pos4 == '*') { temp = pos4; pos4 = pos3; pos3 = temp; }
               else if (pos2 == '*') {round--;cout << "the input is not that valid." << endl;}
            }
            break;
         case '4':
            if (pos4 == '*') {round--;cout << "the input is not that valid." << endl;}
            if (pos4 != '*') {
               if (pos2 == '*') { temp = pos2; pos2 = pos4; pos4 = temp; }
               else if (pos3 == '*') { temp = pos3; pos3 = pos4; pos4 = temp; }
               else if (pos1 == '*') {round--;cout << "the input is not that valid." << endl;}
            }
            break;

         default:
            cout << "Please input a number again" << endl;
            break;
      }
   }  
   
   // Task 4: output the congratulation message and the total number of steps (rounds).
   

   // Show the final puzzle status.
   cout << "Final puzzle status: " << round << endl;
   cout << pos1 << pos2 << endl;
   cout << pos3 << pos4 << endl;
   
   return 0;
}