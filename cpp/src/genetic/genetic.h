#ifndef genetich
#define genetich

#include <string>

namespace genetic {

    // Function to generate random numbers in given range
    int random_num(int start, int end);

    // Create random genes for mutation 
    char mutated_genes();

    // create chromosome or string of genes 
    std::string create_gnome();
}

#endif
