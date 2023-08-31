#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <fstream>
#include <cctype>
using namespace std;

MovieDatabase::MovieDatabase()
{
}

//MAKE EVERYTHINGS LOWERCASE (CASE INSENSITIVE)
bool MovieDatabase::load(const string& filename)
{
    ifstream infile (filename);
    if (!infile)
        return false;
    std::string s;
    while (getline (infile,s))
    {
    //gets ID
        std::string id = s;
        if (id[id.size()-1] == '\r')
            id.pop_back();
    //gets name
        std::string name;
        getline(infile, name);
        if (name[name.size()-1] == '\r')
            name.pop_back();
    //gets release year
        std::string year;
        getline(infile, year);
        if (year[year.size()-1] == '\r')
            year.pop_back();
    //for the while loops
        int indexDirectors = 0;
        std::string director = "";
        std::vector <std::string> m_directors;
        std::vector <std::string> m_actors;
        std::vector <std::string> m_genres;
    //gets directors
        std::string allDirectors;
        getline (infile, allDirectors);
        if (allDirectors[allDirectors.size()-1] == '\r')
            allDirectors.pop_back();
        while (indexDirectors != allDirectors.size())
        {
            if (allDirectors[indexDirectors] == ',')
            {
                //add director to vector
                m_directors.push_back(director);
                indexDirectors++;
                director = "";
            }
            else
            {
                director += allDirectors[indexDirectors];
                indexDirectors++;
            }
        }
        //for the very last one (with no comma after it)
        m_directors.push_back(director);
    //gets actors
        std::string allActors;
        getline (infile, allActors);
        if (allActors[allActors.size()-1] == '\r')
            allActors.pop_back();
        int indexActors = 0;
        std::string actor = "";
        while (indexActors != allActors.size())
        {
            if (allActors[indexActors] == ',')
            {
                //add director to vector
                m_actors.push_back(actor);
                indexActors++;
                actor = "";
            }
            else
            {
                actor += allActors[indexActors];
                indexActors++;
            }
        }
        //for the very last one (with no comma after it)
        m_actors.push_back(actor);
    //gets genres
        std::string allGenres;
        getline (infile, allGenres);
        if (allGenres[allGenres.size()-1] == '\r')
            allGenres.pop_back();
        int indexGenres = 0;
        std::string genre = "";
        while (indexGenres != allGenres.size())
        {
            if (allGenres[indexGenres] == ',')
            {
                //add director to vector
                m_genres.push_back(genre);
                indexGenres++;
                genre = "";
            }
            else
            {
                genre += allGenres[indexGenres];
                indexGenres++;
            }
        }
        //for the very last one (with no comma after it)
        m_genres.push_back(genre);
    //get rating
        float rating;
        infile >> rating;
        infile.ignore (10000, '\n');
    //makes tree of movies
        //converts id to lowercase
        string lowerid = id;
        for (int i =0; i<lowerid.size();i++)
            tolower(lowerid[i]);
        movie_database.insert(lowerid, Movie (id, name, year, m_directors, m_actors, m_genres,rating));
    //makes tree of directors
        for (int i =0; i< m_directors.size(); i++)
        {
            string lowerdirector = m_directors[i];
            //converts key to lowercase
            for (int j =0; j<lowerdirector.size(); j++)
                tolower(lowerdirector[j]);
            director_database.insert(lowerdirector, Movie (id, name, year, m_directors, m_actors, m_genres,rating));
        }
    //makes tree of actors
        for (int i =0; i< m_actors.size(); i++)
        {
            string loweractor = m_actors[i];
            for (int j =0; j<loweractor.size(); j++)
                tolower(loweractor[j]);
            actor_database.insert(loweractor, Movie (id, name, year, m_directors, m_actors, m_genres,rating));
        }
    //makes tree of genres
        for (int i =0; i< m_genres.size(); i++)
        {
            string lowergenre = m_genres[i];
            for (int j =0; j<lowergenre.size();j++)
                tolower(lowergenre[j]);
            genre_database.insert(lowergenre, Movie (id, name, year, m_directors, m_actors, m_genres,rating));
        }
    //removes empty line separating users?
        std::string emptyLine;
        getline(infile, emptyLine);
    }
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string lowerid = id;
    //lowercase the passed in id
    for (int i =0; i<id.size();i++)
        tolower(lowerid[i]);
    TreeMultimap <std::string, Movie> :: Iterator it = movie_database.find(lowerid);
    if (it.is_valid() == false)
        return nullptr;
    
    return &it.get_value();
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string lowerdir = director;
    for (int i =0; i<director.size(); i++)
        tolower(lowerdir[i]);
    
    TreeMultimap <std::string, Movie> :: Iterator it = director_database.find (lowerdir);
    vector <Movie*> movies;
    while (it.is_valid() == true)
    {
        movies.push_back(&it.get_value());
        it.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string loweractor = actor;
    for (int i =0; i< loweractor.size();i++)
        tolower(loweractor[i]);
    TreeMultimap <std::string, Movie> :: Iterator it = actor_database.find (loweractor);
    vector <Movie*> movies;
    while (it.is_valid() == true)
    {
        movies.push_back(&it.get_value());
        it.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string lowergenre = genre;
    for (int i =0; i<lowergenre.size();i++)
        tolower(lowergenre[i]);
    TreeMultimap <std::string, Movie> :: Iterator it = genre_database.find (lowergenre);
    vector <Movie*> movies;
    while (it.is_valid() == true)
    {
        movies.push_back(&it.get_value());
        it.advance();
    }
    return movies;
}
