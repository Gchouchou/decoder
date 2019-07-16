#ifndef genetich
#define genetich
#include "game.h"

using namespace std;

#define POPULATION_SIZE 100
#define GENOME_SIZE 10

namespace Genetic {
    // VALID GENES
    // trying for 5 genes with each 10 combinations
    const string GENES = "abcdefghij";

    // Function to generate random numbers in given range
    int random_num(int start, int end);

    // Create random genes for mutation 
    char mutated_genes();

    // create chromosome or string of genes 
    string create_gnome();

    class Individual
    {
    private:
        static const gamestate* situation;
    public:
        // data members
        int fitness;
        string chromosome;
        bool eval;

        // helper methods
        void cal_fitness();
        static void setSituation(const gamestate &s) {situation = new gamestate(s);}
        static void delSituation() {delete(situation);}
        Individual* mate(Individual &parent2); 
        static bool compareptr(const Individual *ind1, const Individual *ind2);

        // constructor
        Individual(string chromosome);
        Individual(string chromosome,int fitness);
    };

}

#endif