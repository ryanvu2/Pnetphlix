#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    //maps movieID to movies
    TreeMultimap <std::string, Movie> movie_database;
    //maps director to movies
    TreeMultimap <std::string, Movie> director_database;
    //maps actor to movies
    TreeMultimap <std::string, Movie> actor_database;
    //maps genre to movies
    TreeMultimap <std::string, Movie> genre_database;
};

#endif // MOVIEDATABASE_INCLUDED
