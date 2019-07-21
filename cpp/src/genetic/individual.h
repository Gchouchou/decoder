#ifndef indivh
#define indivh
#include "fitness_funct.h"
#include "geneticSettings.h"

#include <string>

namespace genetic {
    class individual
    {
    private:
        // data members
        std::string chromosome;
        bool eval;
        int fitness;
    public:
        // getters
        bool getEval() const{return eval;}
        int getFit() const{return fitness;}
        std::string getChro() const{return chromosome;}

        static const genetic::abstractFitnessCal *function;

        // helper methods
        void cal_fitness();
        individual* mate(individual &parent2); 
        friend bool operator<(const individual &ind1, const individual &ind2)
        {return ind1.fitness < ind2.fitness;}

        // constructor
        individual(std::string chromosome);
        // set eval to true when we obtain fitness
        individual(std::string chromosome,int fitness);
        ~individual(){};
    };
}
#endif
