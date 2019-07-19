#ifndef poph
#define poph

#define logLocation "log/"
#define filePrefix "gen"
#define fileExt ".csv"

#include <vector>
#include <string>

namespace genetic
{
    class individual;

    class population
    {
    private:
        std::vector<individual*> people;
        int generation;
        // constructor for creating new generations
        population(int g): generation(g) {}
    public:
        // evaluate the current generation, also prints results
        void evalGen();
        // create newly evaluated generation, (this will empty the current generation)
        genetic::population* makeNewGen();
        int getGen() {return generation;}
        // clears the current people and fills it with random people
        // they are also evaluated
        void populate();

        // write a file that contains all of our chromosones and fitness
        void writeFile();
        // read population from file
        static genetic::population* genFromFile(int genNumb);

        population(): generation(0) {}
    };
} // namespace genetic


#endif