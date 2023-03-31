#include "myTwitter.h"
#include <fstream>

int main() {
    /* Initialize my Twitter */
    init_user();

    /* Add relationships based on following_relationship.txt */
    char buffer[256];
    ifstream following("following_relationship.txt");
    if (!following.is_open())
        throw invalid_argument( "Cannot find following_relationship.txt, please check your current path!" );
    while (!following.eof()) {
        following.getline(buffer, 100);
        follow(int(buffer[0] - '0'), int(buffer[2] - '0'));
    }

    /* Post tweets based on tweet.txt */
    ifstream tweets("tweet.txt");
    if (!tweets.is_open())
        throw invalid_argument( "Cannot find tweet.txt, please check your current path!" );
    while (!tweets.eof()) {
        tweets.getline(buffer, 100);
        postTweet(int(buffer[0] - '0'));
    }

    /* Check Task 1 and Task 2 */
    cout << "******************************************" << endl;
    cout << "All tweets in current myTwitter: " << endl;
    cout << "******************************************" << endl;
    for (int user_id=0; user_id<MAX_USER; user_id++)
        printTweets(user_id);

    // /* Check Task 3 */
    // cout << "******************************************" << endl;
    // cout << "Please input tweet_id and user id you want to delete. " << endl;
    // int tweet_id, user_id;
    // cin >> tweet_id >> user_id;
    // cout << "User " << user_id << " deletes " << tweet_id << endl;
    // delTweet(tweet_id, user_id);
    // cout << "All tweets in current myTwitter: " << endl;
    // cout << "******************************************" << endl;
    // for (int user_id=0; user_id<MAX_USER; user_id++)
    //     printTweets(user_id);

    /* Check Task 4 */
    cout << "******************************************" << endl;
    cout << "Recent news feed of user 1: " << endl;
    cout << "******************************************" << endl;
    printNewsFeed(1);
}