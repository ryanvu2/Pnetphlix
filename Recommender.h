#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include <unordered_map>
class UserDatabase;
class MovieDatabase;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email, int movie_count);

  private:
//Allows for updating of Movie compatibility score
    class MovieWithScore
    {
    public:
        MovieWithScore(std::string id, float rating, std::string name )
        {
            m_score = 0; m_id = id;
            m_rating = rating;
            m_name= name;
        }
        std::string getID () const
        {
            return m_id;
        }
        float getRating () const
        {
            return m_rating;
        }
    std::string getName() const
        {
        return m_name;
        }
        void addToScore (int num)
        {
            m_score += num;
        }
        int getScore () const
        {
            return m_score;
        }

//this is how the vector will be sorted (break ties here)
    bool operator < (const MovieWithScore& m1) const
    {
        if (getScore() < m1.getScore())
            return true;
        else if (getScore() > m1.getScore())
            return false;
        
    //for ties
        if (getRating() < m1.getRating())
            return true;
        else if (getRating() > m1.getRating())
            return false;
        
        if (getName() > m1.getName())
            return true;
        
        return false;
    }

    private:
        int m_score;
        std::string m_id;
        float m_rating;
        std::string m_name;
    };

    //pointers to user/movie database 
    const UserDatabase* m_userDatabase;
    const MovieDatabase* m_movieDatabase;
    //map from movie ID's to Compatibility Score (maps are sorted)
    std::unordered_map<std::string,int> movieMap;
};

#endif // RECOMMENDER_INCLUDED
