#include <stdlib.h>
#include <iostream>
using namespace std;
const int MAX_HEIGHT=6;
const int MAX_WIDTH=6;
    int result = 0;

bool findUncoveredGrid(int board[][MAX_WIDTH], int height, int width, int& r_id, int& c_id){
    // to be completed
    //
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if(board[i][j]==0)
            {
                r_id=i;
                c_id=j;
                
                //cout << board << endl;
                return true;
            }
        }
    }
    return false;
}


int numberLayout(int board[][MAX_WIDTH], int height, int width){

    int rid=0,cid=0,result=0;
    if((height * width) % 2 == 1){return 0;}
    if(findUncoveredGrid( board, height, width, rid, cid) == false)
    {
        return 1;
    }


    // to be completed               
    //

    if (rid+1<height && board[rid+1][cid]==0)
    {
        board[rid][cid]=1;
        board[rid+1][cid]=1;
        
        result+=numberLayout(board,height,width);

        board[rid][cid]=0;
        board[rid+1][cid]=0;
    }

    if(cid+1<width && board[rid][cid+1]==0)
    {
        board[rid][cid]=1;
        board[rid][cid+1]=1;
        result+=numberLayout(board,height,width);
        board[rid][cid]=0;
        board[rid][cid+1]=0;
    }
    
    return result;
    
}


int main(){
    int width, height;
    int board[MAX_HEIGHT][MAX_WIDTH] = {};

    // enter the height (number of rows)
    do{
    cout << "Please enter the height [1, " << MAX_HEIGHT << "]:" << endl;
    cin >> height;
    }
    while((height < 1)||(height > MAX_HEIGHT));

    // enter the width (number of columns)
    do{
    cout << "Please enter the width [1, " << MAX_WIDTH << "]:" << endl;
    cin >> width;
    }while((width < 1)||(width > MAX_WIDTH));

    cout << "The number of layouts is " << numberLayout(board, height, width) << "." << endl;

    return 0;
}