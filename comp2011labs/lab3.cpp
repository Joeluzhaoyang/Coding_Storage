#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>



using namespace std;

// TODO Task 1: Implementing the RandomInitBalance function which can return a random double type number between dMin and dMax.
double RandomInitBalance(double dMin, double dMax)
{
    int ii=0;
    ii=rand()%99+1;
    return ii;

}

// TODO Task 2: Implementing the Mining function. This function returns a double-type value representing the mining rewards.
// 1. The function has two arguments, which are the selected miner and the number of blocks to be mined by the miner. Different miners will get different benefits.
// 2. Alice's basic reward is 10 coins per block. In case of sequential mining, the latter block yields 10 coins more the previous one. For example, if Alice mines 5 blocks, she will gain 10+20+30+40+50 coins as the reward.
// 3. Bob can gain 20 coins per block. For example, if Bob mines 5 blocks, he will gain 100 coins as the reward.
// 4. Carl's basic reward is 40 coins per block. In case of sequential mining, the latter block yields 5 coins less than the previous one. For example, if Carl mines 5 blocks, he will gain 40+35+30+25+20 coins as the reward.
// 5. The accumulated block reward will be recalculated after each round. For example, if we enter 3 blocks for mining and choose Alice as the miner twice, the block reward for Alice is like :[10,20,30,10,20,30]
double Mining(int selectedMiner, int blockNumber)
{
if(selectedMiner == 1)
{
    int result1=0;
    int xx=0;
    for(;xx<=blockNumber;xx++)
    {
        result1+=xx*10;
    }
    return result1;
}
else if(selectedMiner == 2)
{
    int result2=0;
    int yy=1;
    for(;yy<=blockNumber;yy++)
    {
        result2+=20;
    }
    return result2;
}
else if(selectedMiner == 3)
{
    int result3=0;
    int ss = 40;
    int zz=1;
    for(;zz<=blockNumber;zz++)
    {
        result3+=ss;
        ss-=5;
    }
    return result3;
}
return 0;
}

// TODO Task 3: Implementing the ComputeFinalBalance function. This function returns the average of the three double-type arguments.
double ComputeFinalBalance(double a, double b, double c)
{
    double Average = (a+b+c)/3;
    return Average;
}


// TODO Task 4: Implementing the ComputeTransferValuePBV function used to calculate the value to be transferred between two users based on the final Balance.
// For example: ComputeTransferValuePBV(11, 9, 10) will return 1. It means the fromBalance need to to transfer 1 coin to tiBalance when the finalBalance is 10.
// Hint: the real transferring scenarios can be more complex, so think carefully about all possible scenarios.
double ComputeTransferValuePBV(double fromBalance, double toBalance, double finalBalance)
{
double different;
different = fromBalance - finalBalance;
return different;
}


bool isDoubleEqual (double a, double b) 
{
    const double eps = 1e-6;
    // Hint: the fabs() function returns the absolute value of a double-type variable.
    return fabs(a-b)< eps;
        
}

int main() {

    cout<< "--------------------------------------------------------------" << endl;
    cout<<"Welcome to Lab3! This is simulated mining pool for 2011Coin!"<< endl;
    cout<< "--------------------------------------------------------------" << endl<<endl;

    srand ((unsigned int) time (0));
    double AliceBalance = RandomInitBalance(1,100);
    double BobBalance= RandomInitBalance(1,100);
    double CarlBalance= RandomInitBalance(1,100);

    // Show the users' balance after initialization.
    cout<< "-----------------------Initialization-------------------------" << endl;
    cout<< "The balance of Alice after initialization: " << AliceBalance << endl;
    cout<< "The balance of Bob   after initialization: " << BobBalance << endl;
    cout<< "The balance of Carl  after initialization: " << CarlBalance << endl ;
    cout<< "--------------------------------------------------------------" << endl<<endl;

    int chooseMinerCommand;
    int blockNumber;
    int count1=0,count2=0,count3=0;

    cout<<"Please input the number of the blocks that need to be mined (1 - 5) in each round:"<< endl;
    cin >> blockNumber;

    if (blockNumber ==1 || blockNumber == 2 || blockNumber ==3 || blockNumber == 4 || blockNumber ==5){
        cout<< "The miner will mine " << blockNumber << " blocks." << endl << endl;
        cout<< "--------------------------------------------------------------" << endl;

    } else{
        blockNumber = 1;
        cout<< "Worry input, The miner will only mine " << blockNumber << " block." << endl << endl;
        cout<< "--------------------------------------------------------------" << endl;
    }

    do{
        cout<< "Choose the first miner: "<< endl;
        cout<< "1. Alice "<< endl;
        cout<< "2. Bob" << endl;
        cout<< "3. Carl" << endl;
        cin >> chooseMinerCommand;

        cout<< ".....Mining Start ...." << endl<< endl;

        if (chooseMinerCommand == 1) {

            AliceBalance = AliceBalance + Mining(1, blockNumber);
            count1++;
            break;
        } else if (chooseMinerCommand ==2) {
            BobBalance = BobBalance + Mining(2, blockNumber);
            count2++;
            break;
        } else if (chooseMinerCommand == 3){
            CarlBalance = CarlBalance + Mining(3, blockNumber);
            count3++;
            break;
        }
        else {
            cout << "Worry input, please re-enter your selection."<<endl;
        }
    } while (true);

    do{
        cout<< "Choose the Second miner: "<< endl;
        cout<< "1. Alice "<< endl;
        cout<< "2. Bob" << endl;
        cout<< "3. Carl" << endl;
        cin >> chooseMinerCommand;

        cout<< ".....Mining Start ...." << endl<< endl;
        if (chooseMinerCommand == 1) {
            AliceBalance = AliceBalance + Mining(1, blockNumber);
            count1++;
            break;
        } else if (chooseMinerCommand ==2) {
            count2++;
            BobBalance = BobBalance + Mining(2, blockNumber);
            break;
        } else if (chooseMinerCommand == 3){
            CarlBalance = CarlBalance + Mining(3, blockNumber);
            count3++;
            break;
        }
        else {
            cout << "Wrong input, please re-enter your selection."<<endl;
        }
    } while (true);

    cout<< ".....Mining Done....." << endl<<endl;


    // Show the users' balance after mining.
    cout<< "----------------------------Mining----------------------------" << endl;
    cout<< "The balance of Alice after mining: " << AliceBalance << endl;
    cout<< "The balance of Bob   after mining: " << BobBalance << endl;
    cout<< "The balance of Carl  after mining: " << CarlBalance << endl ;
    cout<< "--------------------------------------------------------------" << endl<<endl;


    // TODO Task 5: Finishing the Crypto Transferring Process.
    //  Goal: Make three people have the same amount of coins by using the ComputeTransferValuePBV function.
    // 1. The two miners that have been chosen will transfer coins to the remaining one.
    // 2. If the same miner is chosen twice, she or he will transfer money to the remaining two participants.
    double average1;
    average1 = ComputeFinalBalance(AliceBalance, BobBalance, CarlBalance);
    double T1=0,T2=0;

    if (count1==1 && count2==1)
    {
        T1 = ComputeTransferValuePBV(AliceBalance, CarlBalance, average1);
        T2 = ComputeTransferValuePBV(BobBalance, CarlBalance, average1);
        AliceBalance-=T1;
        BobBalance-=T2;
        CarlBalance=CarlBalance+T1+T2;
        cout << "Alice transfer"<< T1 << "coins to Carl\n"<<endl;
        cout << "Bob transfer"<< T2 << "coins to Carl"<<endl;
    }
    else if (count1==1 && count3==1)
    {
        T1 = ComputeTransferValuePBV(AliceBalance, BobBalance, average1);
        T2 = ComputeTransferValuePBV(CarlBalance, BobBalance, average1);
        AliceBalance-=T1;
        CarlBalance-=T2;
        BobBalance+=T1+T2;
        cout << "Alice transfer"<< T1 << "coins to Bob\n"<<endl;
        cout << "Carl transfer"<< T2 << "coins to Bob"<<endl;
    }
    else if (count2==1 && count3==1)
    {
        T1 = ComputeTransferValuePBV(BobBalance, AliceBalance, average1);
        T2 = ComputeTransferValuePBV(CarlBalance, AliceBalance, average1);
        BobBalance-=T1;
        CarlBalance-=T2;
        AliceBalance+=T1+T2;
        cout << "Bob transfer"<< T1 << "coins to Alice\n"<<endl;
        cout << "Carl transfer"<< T2 << "coins to Alice"<<endl;
    }
    else if (count1==2)
    {
        T1 = ComputeTransferValuePBV(BobBalance, AliceBalance, average1);
        T2 = ComputeTransferValuePBV(CarlBalance, AliceBalance, average1);
        BobBalance-=T1;
        CarlBalance-=T2;
        AliceBalance+=T1+T2;
        cout << "Alice transfer"<< -T1 << "coins to Bob\n"<<endl;
        cout << "Alice transfer"<< -T2 << "coins to Carl"<<endl;
    }
    else if (count2==2)
    {
        T1 = ComputeTransferValuePBV(AliceBalance, BobBalance, average1);
        T2 = ComputeTransferValuePBV(CarlBalance, BobBalance, average1);
        AliceBalance-=T1;
        CarlBalance-=T2;
        BobBalance+=T1+T2;
        cout << "Bob transfer"<< -T1 << "coins to Alice\n"<<endl;
        cout << "Bob transfer"<< -T2 << "coins to Carl"<<endl;
    }
    else if (count3==2)
    {
        T1 = ComputeTransferValuePBV(AliceBalance, CarlBalance, average1);
        T2 = ComputeTransferValuePBV(BobBalance, CarlBalance, average1);
        AliceBalance-=T1;
        BobBalance-=T2;
        CarlBalance+=T1+T2;
        cout << "Carl transfer"<< -T1 << "coins to Alice\n"<<endl;
        cout << "Carl transfer"<< -T2 << "coins to Bob"<<endl;
    }

    // Show the users' balance after crypto transferring process.
    cout<< "-------------------------Transferring-------------------------" << endl;
    cout<< "The final balance of Alice after crypto transferring: "  << AliceBalance << endl;
    cout<< "The final balance of Bob   after crypto transferring: " << BobBalance << endl;
    cout<< "The final balance of Carl  after crypto transferring: " << CarlBalance << endl;
    cout<< "--------------------------------------------------------------" << endl<<endl;

    cout<< "------------------------Testing-------------------------------" << endl;
    if (isDoubleEqual(AliceBalance,BobBalance)  && isDoubleEqual(BobBalance,CarlBalance)) {
        cout << "Congrats! Lab 3 Testing Passed!" << endl;
    } else {
        cout << "There are still some issues with the code that need to be fixed." << endl;
    }
    cout<< "--------------------------------------------------------------" << endl;
    return 0;
}