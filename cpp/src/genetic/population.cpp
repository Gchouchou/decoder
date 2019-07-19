#include "population.h"
#include "individual.h"
#include "genetic.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

void genetic::population::evalGen() {
    if (genetic::individual::function == nullptr)
    {
        cerr << "no fitness function object defined\n" << flush;
        exit(2);
    }
    for (auto it = people.begin(); it != people.end(); it++) {
        // if it hasn't been already evaluated
        if (!(*it)->getEval()) {
            (*it)->cal_fitness();
        }
    }
    sort(people.begin(),people.end());
    cout<< "Generation: " << generation << "\t"; 
    cout<< "String: "<< people.front()->getChro() <<"\t"; 
    cout<< "Fitness: " << people.front()->getFit() << "\n" << flush;
}

void genetic::population::writeFile() {
    // file name in the form of fileprefix + genNumber + fileExt
    string name = string(logLocation) + filePrefix + std::to_string(generation) + fileExt;
    ofstream outf(name, ios::trunc);
    if (!outf)
    {
        // Print an error and exit
        cerr << "File " << name << "could not be opened for writing!" << endl;
        exit(1);
    }
    for (auto it = people.begin(); it != people.end(); it++) {
        outf << (*it)->getChro() << "," << std::to_string((*it)->getFit()) << endl;
    }
    outf.close();
}


genetic::population* genetic::population::genFromFile(int genNumb) {
    // we read from the file
    // file name in the form of fileprefix + genNumber + fileExt
    string name = logLocation + string(filePrefix) + std::to_string(genNumb) + fileExt;
    ifstream inf(name, ios::in);
    if (!inf)
    {
        // Print an error and exit
        cerr << "File " << name << " could not be opened for reading!" << flush;
        exit(1);
    }
    population *newPop = new population(genNumb);
    while (inf) {
        string line;
        getline(inf,line);
        // make sure that this is not an empty line
        if (line.length() > GENOME_SIZE) {
            // we hope that there is a fitness number
            int fit = std::stoi(line.substr(GENOME_SIZE+1));
            newPop->people.push_back(new individual(line.substr(0,GENOME_SIZE),fit));
        }
        else if (line.length() == GENOME_SIZE) {
            newPop->people.push_back(new individual(line.substr(0,GENOME_SIZE)));
        }
    }
    inf.close();
    if (newPop->people.size() != POPULATION_SIZE) {
        cout << "Warning! Number of individuals from file does not match specified population size.\n" << flush;
    }
    return newPop;
}


void genetic::population::populate() {
    people.clear();
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        string genome = create_gnome();
        people.push_back(new individual(genome));
    }
    evalGen();
}

genetic::population* genetic::population::makeNewGen() {
    genetic::population* newgen = new population(generation + 1);
    if (people.size() != POPULATION_SIZE)
    {
        cout << "Warning! Number of individuals from file does \
        not match specified population size.\n" << flush;
    }
    // Everything Above does not need to be changed
    size_t s,i;
    // we create an iterator type
    const size_t len = people.size();
    // Perform  Elitism the top 10% is moved directly to the next generation
    s = (10*len)/100;
    auto it = people.begin();
    for (i = 0; i < s; it++,i++) {
        newgen->people.push_back(*it);
    }

    // we fill in the rest by uniformly selecting both parents
    s = len - s;
    for (i = 0; i < s; i++)
    {
        int r = random_num(0, len/2); 
        individual *parent1 = people.at(r); 
        r = random_num(0, len/2); 
        individual *parent2 = people.at(r); 
        individual *offspring = parent1->mate(*parent2); 
        newgen->people.push_back(offspring);  
    }

    // delete the no longer needed
    // kill the unfit!
    for (; it != people.end(); it++){
        delete(*it);
    }
    // we clear the vector to make sure we cannot manipulate
    // the objects
    people.clear();
    
    // end of modifiable section
    // evaluate the new generation
    newgen->evalGen();
    return newgen;
}