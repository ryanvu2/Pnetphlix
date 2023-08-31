#include "User.h"

#include <string>
#include <vector>
#include <iostream>
using namespace std;

User::User(const string& full_name, const string& email,
           const vector<string>& watch_history)
{
    userFullName = full_name;
    userEmail = email;
    for (int i =0; i<watch_history.size(); i++)
    {
        userWatchHistory.push_back(watch_history[i]);
    }
}

string User::get_full_name() const
{
    return userFullName;
}

string User::get_email() const
{
    return userEmail;
}

vector<string> User::get_watch_history() const
{
    return userWatchHistory;
}
