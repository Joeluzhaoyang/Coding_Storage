#ifndef _MYTWITTER_H
#define _MYTWITTER_H

#include <iostream>
#include <math.h>
using namespace std;

const int MAX_USER = 5;
const int MAX_FOLLOWEE = 5;            // define the max number of followee
const int MAX_TWEETS = 1000;            // define the max tweets of each user. e.g.: User 1 can send MAX_TWEETS tweets totally

struct Tweet {
    /* Tweet data */
    int timestamp;
    int tweet_id;               // user_id + timestamp
    /* Use for link list */
    Tweet *p_next_tweet;        // next node in link list
};
struct User {
    /* Use for self */
    int self_id;                                // represents id of this user
    Tweet *p_my_tweets_head;                    // head node of the link list
    /* Use for followings */
    int followings_size;
    User* followings[MAX_FOLLOWEE];             // following list
};

/* Global varaibles */
extern int current_time;
extern int max_recent_num;
extern User UsrList[MAX_USER];

/* Define functions */
void init_user();
bool isEmpty(int user_id);
void postTweet(int user_id);
void printNewsFeed(int user_id);
void follow(int user_id_A, int user_id_B);
void printTweets(int user_id);

#endif
