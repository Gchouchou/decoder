#include "genetic.h"
#include "geneticSettings.h"

#include <random>

using namespace genetic;
using namespace std;

// uniform
int genetic::random_num(int start, int end) 
{ 
    int range = (end-start)+1; 
    int random_int = start+(rand()%range); 
    return random_int; 
}

char genetic::mutated_genes() 
{ 
    int len = GENES.size(); 
    int r = random_num(0, len-1); 
    return GENES[r]; 
}

string genetic::create_gnome()
{ 
    int len = GENOME_SIZE;
    string gnome = ""; 
    for(int i = 0;i<len;i++) 
        gnome += mutated_genes(); 
    return gnome; 
} 
