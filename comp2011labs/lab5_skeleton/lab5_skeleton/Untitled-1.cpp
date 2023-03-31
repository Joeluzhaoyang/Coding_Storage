#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int f(int y)
{
    int f1=0,f2=1,f3=2;
    if (y==1){return 0;}
    if(y==2){return 1;}
    if (f3!=y)
    {
        //int f1=0,f2=1,f3=2;
        f3=f1+f2;
        f1=f2;
        f2=f3;
        return f3+f(f3+1);

    }
}

int main()
{
    int x;
cout<<"enter a number"<<endl;
cin>>x;
cout<<f(x)<<endl;

}