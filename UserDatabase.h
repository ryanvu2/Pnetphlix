#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include "treemm.h"

class User;

class UserDatabase
{
  public:
    UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
    //maps email to User (should only be 1 user per email)
    TreeMultimap <std::string, User> m_database;
};

#endif // USERDATABASE_INCLUDED
