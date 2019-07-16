#include "genetic.h"
#include "converteval.h"

using namespace Genetic;

const gamestate* Individual::situation = nullptr;

int Genetic::random_num(int start, int end) 
{ 
    int range = (end-start)+1; 
    int random_int = start+(rand()%range); 
    return random_int; 
}

char Genetic::mutated_genes() 
{ 
    int len = GENES.size(); 
    int r = random_num(0, len-1); 
    return GENES[r]; 
}

string Genetic::create_gnome()
{ 
    int len = GENOME_SIZE;
    string gnome = ""; 
    for(int i = 0;i<len;i++) 
        gnome += mutated_genes(); 
    return gnome; 
} 

Individual::Individual(string chromosome) {
    this->chromosome = chromosome;
    eval = false;
}

Individual::Individual(string chromosome,int fitness) {
    this->chromosome = chromosome;
    this->fitness = fitness;
    eval = true;
}


void Individual::cal_fitness() {
    int i = 0;
    this->fitness = 0;
    this->eval = true;
    // fitness = random_num(0,200);
}

// Perform mating and produce new offspring 
Individual* Individual::mate(Individual &par2) 
{ 
    // chromosome for offspring 
    string child_chromosome = ""; 
  
    int len = chromosome.size(); 
    for(int i = 0;i<len;i++) 
    { 
        // random probability  
        float p = random_num(0, 100)/100; 
  
        // if prob is less than 0.45, insert gene 
        // from parent 1  
        if(p < 0.40) 
            child_chromosome += chromosome[i]; 
  
        // if prob is between 0.45 and 0.90, insert 
        // gene from parent 2 
        else if(p < 0.80) 
            child_chromosome += par2.chromosome[i]; 
  
        // otherwise insert random gene(mutate),  
        // for maintaining diversity 
        else
            child_chromosome += mutated_genes(); 
    } 
  
    // create new Individual(offspring) using  
    // generated chromosome for offspring 
    return new Individual(child_chromosome); 
}; 

bool Individual::compareptr(const Individual *ind1, const Individual *ind2) {
    return ind1->fitness < ind2->fitness;
}