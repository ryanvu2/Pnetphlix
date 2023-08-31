#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//given all the users && all the posible movies
Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_userDatabase = &user_database;
    m_movieDatabase = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count)
{
    //gets a *User
    User* user = m_userDatabase->get_user_from_email(user_email);
    
    //if user doesn't exist
    vector <MovieAndRank> emptyMovies;
    if (user == nullptr || movie_count < 1)
        return emptyMovies;
    //gets User's watch history (vector of movie ID's)
    vector<string> watchHistory = user->get_watch_history();

    //looks through all unwatched movies and compares them to each watched movie
    vector <string> :: iterator it = watchHistory.begin();
    //vector of unwatched movies with their scores
    vector <MovieWithScore> movieCompats;
//for all movies in User watch history
    while (it != watchHistory.end())
    {
        string curUserMovieID = *it;
        
        Movie* curUserMovie = m_movieDatabase->get_movie_from_id(curUserMovieID);
        
        //compare each user movie and slowly ups scores of movies with similar attributes
        vector <string> directors = curUserMovie->get_directors();
    //for each director
        for (int i =0; i<directors.size(); i++)
        {
            vector <Movie*> moviesWithDirector = m_movieDatabase->get_movies_with_director(directors[i]);
        //for each Movie within database with that director, update their score
            for (int j =0; j< moviesWithDirector.size(); j++)
            {
                //current movie from database (with matching director)
                MovieWithScore curMovieInData (moviesWithDirector[j]->get_id(),moviesWithDirector[j]->get_rating(), moviesWithDirector[j]->get_title() );
                //check if movieID already entered before
                bool movieExists = false;
                MovieWithScore* movieInVector = nullptr;
                //already watched movies
                if (curMovieInData.getID() == curUserMovieID)
                    continue;
                //loops through vector to see if movie is already added
                for (int k =0; k<movieCompats.size();k++)
                {
                    //if movie was already added
                    if (movieCompats[k].getID() == curMovieInData.getID())
                    {
                        //pointer to movie which is already in vector
                        movieInVector = &movieCompats[k];
                        movieExists = true;
                    }
                }
            //if movie is not in vector yet
                if (movieExists == false)
                {
                    curMovieInData.addToScore(20);
                    movieCompats.push_back(curMovieInData);
                }
                //if movie is already in vector
                else if (movieExists == true)
                {
                    movieInVector->addToScore(20);
                }
            }
        }
    //for each actor
        vector <string> actors = curUserMovie->get_actors();
        for (int i =0; i<actors.size(); i++)
        {
            vector <Movie*> moviesWithActor = m_movieDatabase->get_movies_with_actor(actors[i]);
        //for each Movie within database with that director, update their score
            for (int j =0; j< moviesWithActor.size(); j++)
            {
                //current movie from database (with matching director)
                MovieWithScore curMovieInData (moviesWithActor[j]->get_id(), moviesWithActor[j]->get_rating(), moviesWithActor[j]->get_title());
                //check if movieID already entered before
                bool movieExists = false;
                MovieWithScore* movieInVector = nullptr;
                //already watched movies
                if (curMovieInData.getID() == curUserMovieID)
                    continue;
                //loops through vector to see if movie is already added
                for (int k =0; k<movieCompats.size();k++)
                {
                    //if movie was already added
                    if (movieCompats[k].getID() == curMovieInData.getID())
                    {
                        //pointer to movie which is already in vector
                        movieInVector = &movieCompats[k];
                        movieExists = true;
                    }
                }
                //if movie is not in vector yet
                if (movieExists == false)
                {
                    curMovieInData.addToScore(30);
                    movieCompats.push_back(curMovieInData);
                }
                //if movie is already in vector
                else if (movieExists == true)
                {
                    movieInVector->addToScore(30);
                }
            }
        }
    //for each genre
        vector <string> genres = curUserMovie->get_genres();
        for (int i =0; i<genres.size(); i++)
        {
            vector <Movie*> moviesWithGenre = m_movieDatabase->get_movies_with_genre(genres[i]);
        //for each Movie within database with that director, update their score
            for (int j =0; j< moviesWithGenre.size(); j++)
            {
                //current movie from database (with matching director)
                MovieWithScore curMovieInData (moviesWithGenre[j]->get_id(),moviesWithGenre[j]->get_rating(), moviesWithGenre[j]->get_title() );
                //check if movieID already entered before
                bool movieExists = false;
                MovieWithScore* movieInVector = nullptr;
                //already watched movies
                if (curMovieInData.getID() == curUserMovieID)
                    continue;
                //loops through vector to see if movie is already added
                for (int k =0; k<movieCompats.size();k++)
                {
                    //if movie was already added
                    if (movieCompats[k].getID() == curMovieInData.getID())
                    {
                        //pointer to movie which is already in vector
                        movieInVector = &movieCompats[k];
                        movieExists = true;
                    }
                }
                //if movie is not in vector yet
                if (movieExists == false)
                {
                    curMovieInData.addToScore(1);
                    movieCompats.push_back(curMovieInData);
                }
                //if movie is already in vector
                else if (movieExists == true)
                {
                    movieInVector->addToScore(1);
                }
            }
        }
        it++;
    }
    //sort vector (using STL sort)
    sort(movieCompats.begin(), movieCompats.end());
    
    //remove movies already watched
    vector <MovieWithScore> :: iterator iters = movieCompats.begin();
    while (iters != movieCompats.end())
    {
        for (int i =0; i<watchHistory.size();i++)
        {
            if (iters->getID()==watchHistory[i])
            {
                movieCompats.erase(iters);
                iters = movieCompats.begin();
            }
        }
            iters++;
    }
    
    //put movies from vector into a MovieAndRank vector (which we return)
    vector <MovieAndRank> rankedMovies;
    vector <MovieWithScore> :: iterator iter = movieCompats.end();
    int numberOfMoviesToAdd = 0;
    //while there are compatible movies and keeping track of how many movies to add
    while (iter != movieCompats.begin() && numberOfMoviesToAdd != movie_count)
    {
        iter--;
        //created a MovieAndRank object from MovieWithScore vector
        MovieAndRank addedMovie (iter->getID(), iter->getScore());
        //adds object to new vector
        rankedMovies.push_back(addedMovie);
        
        numberOfMoviesToAdd++;
    }
    return rankedMovies;
}
