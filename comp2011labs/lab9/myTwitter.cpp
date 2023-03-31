#include "myTwitter.h"

/*
    In this Lab, we will design a simple Twitter.
    1. Maintain several users.
    2. Each user has ID and a Tweet list, which is defined in myTwitter.h.
    3. Each user can follow other users.

    Main functions in myTwitter:
    1. Post a tweet (Insert a node in link list) - Task 2
    2. Get the latest news from followings - Task 3
*/

/* ----------------------------------------- */
/* ----------------Functions---------------- */
/* ----------------------------------------- */

/* Global varaibles */
int current_time = 1;
int max_recent_num = 5;
User UsrList[MAX_USER];

/* Initialize each User */
void init_user() {
    for (int i=0; i<MAX_USER; i++) {
        UsrList[i].self_id = i;
        UsrList[i].p_my_tweets_head = NULL;
        UsrList[i].followings_size = 0;
        for (int j=0; j<MAX_FOLLOWEE; j++)
            UsrList[i].followings[j] = NULL;
    }
}

/* 
    Task 1: Determines if the specified user has sent a tweet
    Link List: isEmpty
    Input:
        user_id: int, must smaller than MAX_USER. Used to get the User in UsrList
    Return:
        True: empty
        False: not empty
*/
bool isEmpty(int user_id) {
    if (user_id > MAX_USER)
        throw invalid_argument( "User ID is out of scope!" );
    /*******************************************
                 Your code begin at here
    *******************************************/
    if(UsrList[user_id].p_my_tweets_head==nullptr)
    {return true;}
    else 
    {return false;}
    /*******************************************
                 Your code end at here
    *******************************************/
}

/* 
    Task 2: Post a tweet given a user 
    Link List : Insert 
    Input:
        user_id: int, must smaller than MAX_USER. Used to get the User in UsrList
    Return:
        None
*/
void postTweet(int user_id) {
    if (user_id > MAX_USER)
        throw invalid_argument( "User ID is out of scope!" );
    /* Initialize new Tweet */
    Tweet *p_NewTweet = new Tweet();
    p_NewTweet->timestamp = current_time;
    p_NewTweet->tweet_id = MAX_TWEETS*user_id + current_time;
    p_NewTweet->p_next_tweet = NULL;

    /*******************************************
                 Your code begin at here
    *******************************************/
    User* p_usr = &UsrList[user_id];
    p_NewTweet->p_next_tweet = p_usr->p_my_tweets_head;
    p_usr->p_my_tweets_head = p_NewTweet;
    /*******************************************
                 Your code end at here
    *******************************************/
    current_time++;     // Time incremented by 1 for each tweet added
}

/* 
    Task 3: 
    Retrieve the 5 most recent tweets in the user's news feed. 
    Each item in the news feed must be posted by users who the user followed or by the user herself. 
    Tweets must be ordered from most recent to least recent.

    Link List : Search & Compare
    Input:
        user_id: int, must smaller than MAX_USER. Used to get the User in UsrList
    Return:
        None
*/
void printNewsFeed(int user_id) {
    cout << "Current time is: " << current_time << endl;
    cout << "You should display recent " << max_recent_num << " tweets" << endl;

    /*******************************************
                 Your code begin at here
    *******************************************/
    if (user_id > MAX_USER)
        throw invalid_argument( "User ID is out of scope!" );
    
    /*******************************************
                 Your code end at here
    *******************************************/

}

void follow(int user_id_A, int user_id_B) {
    int current_size = UsrList[user_id_A].followings_size;
    UsrList[user_id_A].followings[current_size] = &UsrList[user_id_B];
    UsrList[user_id_A].followings_size++;
}

void printTweets(int user_id) {
    Tweet *p = UsrList[user_id].p_my_tweets_head;
    if (isEmpty(user_id)) {
        cout << "Tweet of user " << user_id << " is empty. " << endl;
        return;
    }
    cout << "Tweets of user " << user_id << ": ";
    if (user_id == 0)
        while (p != NULL) {
            cout << p->tweet_id << " ";
            p = p->p_next_tweet;
        }
    else
        while (p != NULL) {
            cout << p->tweet_id << " ";
            p = p->p_next_tweet;
        }
    cout << endl;
}
