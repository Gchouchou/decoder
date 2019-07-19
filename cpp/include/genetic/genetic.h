#ifndef genetich
#define genetich

#define POPULATION_SIZE 100
#define GENOME_SIZE 10
#define MUTATION_CHANCE 0.2

#include <string>

namespace genetic {
    // VALID GENES
    // trying for 5 genes with each 10 combinations
    const std::string GENES = "abcdefghij";

    // Function to generate random numbers in given range
    int random_num(int start, int end);

    // Create random genes for mutation 
    char mutated_genes();

    // create chromosome or string of genes 
    std::string create_gnome();
}

#endif