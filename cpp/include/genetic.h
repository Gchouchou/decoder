#ifndef genetich
#define genetich
#include "fitness_funct.h"

#define POPULATION_SIZE 100
#define GENOME_SIZE 10
#define MUTATION_CHANCE .2

namespace Genetic {
    // VALID GENES
    // trying for 5 genes with each 10 combinations
    const std::string GENES = "abcdefghij";

    // Function to generate random numbers in given range
    int random_num(int start, int end);

    // Create random genes for mutation 
    char mutated_genes();

    // create chromosome or string of genes 
    std::string create_gnome();

    class Individual
    {
    private:
        static const AbstractFitnessCal *function;
    public:
        // data members
        int fitness;
        std::string chromosome;
        bool eval;

        // helper methods
        void cal_fitness();
        Individual* mate(Individual &parent2); 
        static bool compareptr(const Individual *ind1, const Individual *ind2);

        // constructor
        Individual(std::string chromosome);
        Individual(std::string chromosome,int fitness);
    };

}

#endif