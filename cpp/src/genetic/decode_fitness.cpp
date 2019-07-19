#include "decode_fitness.h"
#include "algo.h"
#include "genetic.h"
#include "tester.h"

namespace converters {
    const decoder::decodeparam* decode(std::string chromosome) {
        char c;
        decoder::decodeparam *params = new decoder::decodeparam();
        params->absScale = 0;
        params->scale = 0;
        params->cscale = 0;
        params->cscore = 0;
        params->sscore = 0;
        for (size_t i = 0; i < Genetic::GENES.length(); i++)
        {
            c = Genetic::GENES[i];
            if (chromosome[0] == c) {
                // we want a bit less variance on absScale
                params->absScale += 0.1*i;
            }
            if (chromosome[1] == c) {
                params->cscale += 0.1*i;
            }
            if (chromosome[2] == c) {
                params->sscore += 0.1*i - 0.1;
            }
            if (chromosome[3] == c) {
                params->scale += 0.1*i;
            }
            if (chromosome[4] == c) {
                // cscore cannot be 0.
                params->cscore += 0.1 + i;
            }
            if (chromosome[5] == c) {
                // we want a bit less variance on absScale
                params->absScale += i;
            }
            if (chromosome[6] == c) {
                params->cscale += i;
            }
            if (chromosome[7] == c) {
                params->sscore += i;
            }
            if (chromosome[8] == c) {
                params->scale += i;
            }
            if (chromosome[9] == c) {
                // cscore cannot be 0.
                params->cscore += i;
            }
        }
        return params;
    }
}


int decode_fitness::cal_fitness(const std::string &chromosome) const{
    int i =0,fitness = 0;
    const decoder::decodeparam *params = converters::decode(chromosome);
    const std::array<int,3*3> *results = decoder::testAll(situation,*params);
    delete(params);
    for (auto it = results->begin(); it != results->end(); it++,i++){
        fitness += i*(*it);
    }
    delete(results);
    return fitness;
}