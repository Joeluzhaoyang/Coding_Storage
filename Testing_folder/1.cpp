#include <iostream>
#include "print.h"
using namespace std;

int numbers;
const int size=5;

void print(int,int);

int main()
{
    cout<<"put some numbers:)"<<endl;
    cin>>numbers;
    print(numbers,size);
}