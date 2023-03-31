#include <iostream> 
#include <cstdlib> 
#include <cstring>
using namespace std; 






int main(){
    int y;
    int& x = y;
    int&& a = 7;
    cout<<x<<endl;

    return 0;
}