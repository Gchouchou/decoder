#include "genetic.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#define startGen 2
#define numbGen 10

using namespace Genetic;

// calls cal_fitness on everyone
void evalPopulation(vector<Individual*> &pop);

// save the generation for future use
void writeGen(vector<Individual*> &pop, int gen);

// reads generation from file
void readGen(int gen,vector<Individual*> &pop);

int main(int argc, char const *argv[])
{
    srand((unsigned)(time(0)));
    // current generation 
    int generation = startGen; 
    int i,s;

    // our population
    vector<Individual*> *population = new vector<Individual*>;
    vector<Individual*> *newgen;
    // setting the situation
    gamestate *test = new gamestate();
    Individual::setSituation(*test);
    delete(test);
    // just getting the iterator type
    auto iter = population->end();
    // read the generation
    readGen(generation,*population);
    while (generation < numbGen)
    {
        evalPopulation(*population);
        sort(population->begin(),population->end(),Individual::compareptr);
        writeGen(*population,generation);

        cout<< "Generation: " << generation << "\t"; 
        cout<< "String: "<< population->front()->chromosome <<"\t"; 
        cout<< "Fitness: ";
        printf("%d",population->front()->fitness);
        cout << "\n" << flush; 

        generation++;

        // generate new offsprings
        newgen = new vector<Individual*>;

        // Perform Elitism, that mean 10% of fittest population 
        // goes to the next generation 
        s = (10*POPULATION_SIZE)/100;
        i = 0;
        for (iter = population->begin(); i<s; i++,iter++) {
            newgen->push_back(*iter);
        }
        // we'll kill of the rest soon enough

        // fill in the rest
        s = POPULATION_SIZE - s;
        for(i = 0;i<s;i++) 
        { 
            int len = population->size(); 
            int r = random_num(0, len/2); 
            Individual *parent1 = population->at(r); 
            r = random_num(0, len/2); 
            Individual *parent2 = population->at(r); 
            Individual *offspring = parent1->mate(*parent2); 
            newgen->push_back(offspring);  
        }
        // kill the unfit!
        for (; iter != population->end(); iter++){
            delete(*iter);
        }
        delete(population);
        // move on to the new gen
        population = newgen;
    }
    // clear the population
    for (iter = population->begin(); iter != population->end(); iter++){
        delete(*iter);
    }
    delete(population);
    Individual::delSituation();
    return 0;
}


void evalPopulation(vector<Individual*> &pop) {
    for (auto it = pop.begin(); it != pop.end(); it++) {
        if (!(*it)->eval) {
            (*it)->cal_fitness();
        }
    }
}


void writeGen(vector<Individual*> &pop, int gen) {
    string name = "log/gen" + std::to_string(gen) + ".txt";
    ofstream outf(name, ios::trunc);
    if (!outf)
    {
        // Print an error and exit
        cerr << "Uh oh, could not be opened for writing!" << endl;
        exit(1);
    }
    for (auto it = pop.begin(); it != pop.end(); it++) {
        outf << (*it)->chromosome << "," << std::to_string((*it)->fitness) << endl;
    }
    outf.close();
}

void readGen(int gen,vector<Individual*> &pop) {
    if (gen == 0)
    {
        for (int i = 0; i < POPULATION_SIZE; i++)
        {
            string genome = create_gnome();
            pop.push_back(new Individual(genome));
        }
    }
    else {
        // else we read from the file
        string name = "log/gen" + std::to_string(gen) + ".txt";
        ifstream inf(name, ios::in);
        if (!inf)
        {
            // Print an error and exit
            cerr << "Uh oh, could not be opened for reading!" << endl;
            exit(1);
        }
        while (inf) {
            string line;
            getline(inf,line);
            int fit = std::stoi(line.substr(GENOME_SIZE+1));
            if (line.length() == GENOME_SIZE) {
                pop.push_back(new Individual(line.substr(0,GENOME_SIZE),fit));
            }
        }
        inf.close();
    }
}
