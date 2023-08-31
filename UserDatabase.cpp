#include "UserDatabase.h"
#include "User.h"
#include "treemm.h"
#include <iostream>
#include <fstream>

#include <string>
#include <vector>
using namespace std;

UserDatabase::UserDatabase()
{
}

bool UserDatabase::load(const string& filename)
{
    ifstream infile (filename);
    if (!infile)
        return false;
    std::string s;
    while (getline (infile,s))
    {
    //gets name
        std::string name = s;
        if (name[name.size()-1] == '\r')
            name.pop_back();
    //gets email
        std::string email;
        getline(infile, email);
        if (email[email.size()-1] == '\r')
            email.pop_back();
    //gets number of movies
        int numMovies;
        infile >> numMovies;
        infile.ignore (10000, '\n');
    //puts all movies into User
        std::vector <std::string> userWatchHistory;
        for (int i =0; i<numMovies; i++ )
        {
            std::string movieID;
            getline (infile, movieID);
            if (movieID[movieID.size()-1] == '\r')
                movieID.pop_back();
            userWatchHistory.push_back(movieID);
        }
        m_database.insert(email, User(name, email, userWatchHistory));
    //removes empty line separating users?
        std::string emptyLine;
        getline(infile, emptyLine);
    }
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap <std::string, User>:: Iterator it = m_database.find(email);
    //returns the address of the user within tree
    if (it.is_valid() == false)
        return nullptr;
    
    return &it.get_value();
}
