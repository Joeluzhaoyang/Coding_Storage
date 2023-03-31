#include <iostream>
using namespace std;
//you are NOT allowed to include any additional library
const int ARRAY_MAX_SIZE = 12;

//given; do NOT modify; please refer to the webpage description
void printArray(int array[], int arraySize, int currentPosition)
{
    cout << array[currentPosition];
    if(currentPosition < arraySize-1)
    {
        if(array[currentPosition+1] > 0)
            cout << "+";
        printArray(array, arraySize, currentPosition+1);
    }
    else
        cout << endl;
}

//given; do NOT modify; please refer to the webpage description
void printArray(int array[], int arraySize)
{
     printArray(array, arraySize, 0);
}

int ArraySum(int array[], int arraySize, int pos1)
{
    if(pos1<arraySize)
    {
        return array[pos1]+ArraySum(array,arraySize,pos1+1);
    }
    else if(pos1>=arraySize)
    {
        return 0;
    }
    return 0;
}
//***** Only write your code below this line, remember that NO loop is allowed! ***** 
int arraySum(int array[], int arraySize)
{
    return ArraySum(array, arraySize, 0);  //change this line if you want
}

bool Solve(int input[], int size, int target, int result[], int& resultSize, int pos2,int& sum,int pos3)
{
    if (pos2==size)
    {
        return false;
    }
    if(sum!=target)
    {
        sum=input[pos2]+sum;
        result[pos3]=input[pos2];
        resultSize++;
        pos3++;
        if(sum==target)
        {
            return true;
        }

        {
        Solve(input,size,target,result,resultSize,pos2+1, sum,pos3);
        }
        
        if(sum!=target)
        {
            sum=sum-input[pos2];
            result[pos3]=0;
            resultSize--;
            pos3--;
        }
        if(sum==target)
        {
            return true;
        }
    }

    if(sum!=target)
    {
        sum=sum-input[pos2];
        result[pos3]=-input[pos2];
        resultSize++;
        pos3++;
        if(sum==target)
        {
            return true;
        }

        {
        Solve(input,size,target,result,resultSize,pos2+1, sum,pos3);
        }
        
        if(sum!=target)
        {
            sum=sum+input[pos2];
            result[pos3]=0;
            resultSize--;
            pos3--;
        }
        if(sum==target)
        {
            return true;
        }
    }

    if(sum==target)
    {
        return true;
    }

    if(sum!=target)
    {
        {
        Solve(input,size,target,result,resultSize,pos2+1, sum,pos3);
        }        
    }
    if(sum==target)
    {
        return true;
    }
    return false;
} 

bool solve(int input[], int size, int target, int result[], int& resultSize) 
{
    int sum=0;
    return Solve(input, size, target, result, resultSize,0,sum,0) ;  //change this line if you want
}

bool PrintString(const char str[],int pos4)
{
    if (str[pos4]=='\0')
    {
        cout<<endl;
        return false;
    }
    if (str[pos4]!='\0')
    {
        cout << str[pos4];
        
        if(!PrintString(str,pos4+1) )
        {
            return false;
        }
    }
    return false;

}

void printString(const char str[])
{
    PrintString(str,0);
}

int pow(int diff,int &temp)
{
    if(diff!=0)
    {
        temp=temp*10;
        pow(diff-1,temp);
    }
    else if(diff==0)
    {
        return temp;
    }
    return temp;
}

int GetIntValue(const char str[],int start,int end,int pos9, int& result)
{
    if(start<=end)
    {
        int temp=str[start]-48;
        result+=pow(end-start,temp);
        GetIntValue(str,start+1,end,pos9+1,result);
    }
    else
    {
        return result;
    }
    return result;
}

int getIntValue(const char str[], int start, int end)
{
    int result=0;
    GetIntValue(str,start,end,0,result);
    return result;
}



void strlen(const char str[],int& length)//task6
{
    if(str[length]!='\0')
    {
        length++;
        strlen(str,length);
    }
}

int getLoca(const char str[],int loca)
{
    if(str[loca]=='+'||str[loca]=='-' ||str[loca]=='\0')
    {
        return loca;
    }
    else 
    {
        getLoca(str,loca+1);
    }
}

int Number(const char str[],int numberArray[],int pos5,int init, int length, int ArrPos)
{
    int final;
    if(init==length+1)
    {
        return arraySum(numberArray,ArrPos);
    }
    else
    {
        final=getLoca(str,init);
        //cout << final;
        if(str[pos5-1]!='-')
        {
            numberArray[ArrPos]=getIntValue(str,  init,  final-1);
            ArrPos++;
            Number(str,numberArray,final+1,final+1,length,ArrPos);
        }
        else if(str[pos5-1]=='-')
        {
            numberArray[ArrPos]=0-getIntValue(str,  init,  final-1);
            ArrPos++;
            Number(str,numberArray,final+1,final+1,length,ArrPos);
        }
        
    }
}

int evaluate(const char str[])
{
    int length=0;int numberArray[]={'\0'};
    int ArrPos=0;
    strlen(str,length);
    return Number(str,numberArray,1,0,length,ArrPos);
       //change this line if you want
}
//***** Only write your code above this line, remember that NO loop is allowed! *****


int main()
{
    int testCase;
    cout << "Hi, recursion master! Which test case do you want to run?" << endl;
    cin >> testCase;

    cout << endl << "Test case " << testCase << " output:" << endl;
    cout << "===================================" << endl;

    if(testCase == 0) //this test case is used to show you how printArray works; it is NOT used to grade your work and it is NOT on ZINC; no mark is allocated to this; try it on your own computer if you want
    {
        int array1[] = {1, 2, 3};
        printArray(array1, 3);
        int array2[] = {1, 2, 3, -4};
        printArray(array2, 4);
        int array3[] = {-8, 2, 1, -4};
        printArray(array3, 4);
        int array4[] = {99};
        printArray(array4, 1);
        int array5[] = {-1199};
        printArray(array5, 1);
    }
    
    else if(testCase == 1) //test arraySum
    {
        int array[] = {1, 2, 3};
        cout << arraySum(array, 3) << endl;
    }
    else if(testCase == 2) //test arraySum
    {
        int array[] = {-1, -234, 33, 5};
        cout << arraySum(array, 4) << endl;
    }

    else if(testCase == 3) //test solve
    {
        int input[] = {1, 2, 3, 4};
        int size = 4;
        int target = 2;
        int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
        int resultSize = 0;
        if(solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }
    else if(testCase == 4) //test solve
    {
        int input[] = {1, 2, 3, 4};
        int size = 4;
        int target = -2;
        int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
        int resultSize = 0;
        if(solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }
    else if(testCase == 5) //test solve
    {
        int input[] = {1, 2, 3, 4};
        int size = 4;
        int target = -9;
        int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
        int resultSize = 0;
        if(solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }
    else if(testCase == 6) //test solve
    {
        int input[] = {8, 13, 1, 3, 5, 9};
        int size = 6;
        int target = 9;
        int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
        int resultSize = 0;
        if(solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }
    else if(testCase == 7) //test solve
    {
        int input[] = {88, 13, 1, 3, 5, 9};
        int size = 6;
        int target = 9;
        int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
        int resultSize = 0;
        if(solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }
    else if(testCase == 8) //test solve
    {
        int input[] = {888, 13333, 20000, 1, 99, 3, 5, 9, 33, 44, 55, 100};
        int size = 12;
        int target = -165;
        int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
        int resultSize = 0;
        if(solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }

    else if(testCase == 9) //test printString
    {
        printString("1+1-2+1234");
    }
    else if(testCase == 10) //test printString
    {
        printString("Wow this assignment is so much fun!!!");
    }

    else if(testCase == 11) //test getIntValue
    {
        char str[] = "567";
        cout << getIntValue(str, 0, 2) << endl;
    }
    else if(testCase == 12) //test getIntValue
    {
        char str[] = "567";
        cout << getIntValue(str, 0, 1) << endl;
    }
    else if(testCase == 13) //test getIntValue
    {
        char str[] = "567";
        cout << getIntValue(str, 0, 0) << endl;
    }
    else if(testCase == 14) //test getIntValue
    {
        char str[] = "abc567abc";
        cout << getIntValue(str, 4, 5) << endl;
    }
    
    else if(testCase == 15) //test evaluate
    {
        cout << evaluate("172") << endl;
    }
    else if(testCase == 16) //test evaluate
    {
        cout << evaluate("3+2") << endl;
    }
    else if(testCase == 17) //test evaluate
    {
        cout << evaluate("1+2-4") << endl;
    }
    else if(testCase == 18) //test evaluate
    {
        cout << evaluate("11+21-43") << endl;
    }
    else if(testCase == 19) //test evaluate
    {
        cout << evaluate("11+21-43+888") << endl;
    }
    else if(testCase == 20) //test evaluate
    {
        cout << evaluate("-21") << endl;
    }
   
    cout << "===================================" << endl;

    return 0;
}

