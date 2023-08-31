#include "UserDatabase.h"
#include "User.h"
#include <iostream>
#include <string>
#include "Recommender.h"
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";

//int main()
//{
//	UserDatabase udb;
//	if (0&&!udb.load(USER_DATAFILE))  // In skeleton, load always return false
//	{
//		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
//		return 1;
//	}
//	for (;;)
//	{
//		cout << "Enter user email address (or quit): ";
//		string email;
//		getline(cin, email);
//		if (email == "quit")
//			return 0;
//		User* u = udb.get_user_from_email(email);
//		if (u == nullptr)
//			cout << "No user in the database has that email address." << endl;
//		else
//			cout << "Found " << u->get_full_name() << endl;
//	}
//}

#include "treemm.h"
//int main()
//{
//    TreeMultimap <string, int> tree;
//    tree.insert("ryan", 40);
//    TreeMultimap <string, int>:: Iterator it = tree.find("ryan");
//    cout << it.get_value();
//}

//int main()
//{
//    UserDatabase data;
//    data.load("/Users/ryanvu/Downloads/miniUsers.txt");
//    User* user = data.get_user_from_email("AbFow2483@charter.net");
//    cout<< user->get_full_name() <<endl;
//}

#include "MovieDatabase.h"
#include "Movie.h"
//int main()
//{
//    MovieDatabase movies;
//    movies.load("/Users/ryanvu/Downloads/miniMovies.txt");
//    Movie* specificMovie = movies.get_movie_from_id("ID10782");
//    cout<< specificMovie->get_title()<<endl;
//    vector<Movie*> moviesWithDirector = movies.get_movies_with_director("M. Raja");
//    vector<Movie*> moviesWithActor = movies.get_movies_with_actor("Ben Shapiro");
//    vector<Movie*> moviesWithGenre = movies.get_movies_with_genre("Documentary");
//    for (int i =0; i<moviesWithDirector.size(); i++)
//    {
//        cout<< (moviesWithDirector.at(i))->get_title()<<endl;
//    }
//    for (int i =0; i<moviesWithActor.size(); i++)
//    {
//        cout<< (moviesWithActor.at(i))->get_title()<<endl;
//    }
//    for (int i =0; i<moviesWithGenre.size(); i++)
//    {
//        cout<< (moviesWithGenre.at(i))->get_title()<<endl;
//    }
//}

void findMatches(Recommender& r,
 const MovieDatabase& md,
 const string& user_email,
 int num_recommendations)
{
 // get up to ten movie recommendations for the user
 vector<MovieAndRank> recommendations = r.recommend_movies(user_email, num_recommendations);
    if (recommendations.empty())
        cout << "We found no movies to recommend :(.\n";
    else {
        for (int i = 0; i < recommendations.size(); i++)
        {
            const MovieAndRank& mr = recommendations[i];
            Movie* m = md.get_movie_from_id(mr.movie_id);
            cout << i << ". " << m->get_title() << " ("
            << m->get_release_year() << ")\n Rating: "
            << m->get_rating() << "\n Compatibility Score: "
            << mr.compatibility_score << "\n";
        }
    }
}

//"/Users/ryanvu/Downloads/Pnetphlix/miniUsers.txt"
//"/Users/ryanvu/Downloads/Pnetphlix/miniMovies.txt"

int main()
{
    MovieDatabase movies;
    movies.load("/Users/ryanvu/Downloads/Pnetphlix/miniMovies.txt");
    UserDatabase data;
    data.load("/Users/ryanvu/Downloads/Pnetphlix/miniUsers.txt");
    Recommender rec (data, movies);
    findMatches(rec, movies, "climberkip@gmail.com", 10);
}
