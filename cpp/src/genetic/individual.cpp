#include "individual.h"
#include "genetic.h"

using namespace std;

// initialize static variables
const genetic::abstractFitnessCal *genetic::individual::function = nullptr;

genetic::individual::individual(string chromosome) {
    this->chromosome = chromosome;
    eval = false;
}

genetic::individual::individual(string chromosome,int fitness) {
    this->chromosome = chromosome;
    this->fitness = fitness;
    eval = true;
}


void genetic::individual::cal_fitness() {
    this->fitness = function->cal_fitness(chromosome);
    this->eval = true;
    // fitness = random_num(0,200);
}

// Perform mating and produce new offspring 
genetic::individual* genetic::individual::mate(individual &par2) 
{ 
    // chromosome for offspring 
    string child_chromosome = ""; 
  
    int len = chromosome.size(); 
    for(int i = 0;i<len;i++) 
    { 
        // random probability  
        float p = random_num(0, 100)/(float)100; 
  
        // if prob is less than 0.45, insert gene 
        // from parent 1  
        if(p < 0.5*(1-MUTATION_CHANCE)) 
            child_chromosome += chromosome[i]; 
  
        // if prob is between 0.45 and 0.90, insert 
        // gene from parent 2 
        else if(p < 1- MUTATION_CHANCE) 
            child_chromosome += par2.chromosome[i]; 
  
        // otherwise insert random gene(mutate),  
        // for maintaining diversity 
        else
            child_chromosome += mutated_genes(); 
    } 
  
    // create new individual(offspring) using  
    // generated chromosome for offspring 
    return new genetic::individual(child_chromosome); 
}; 