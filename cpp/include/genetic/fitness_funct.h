#ifndef fitnessh
#define fitnessh

#include <string>

namespace genetic {
    // abstract class that returns the int from cal fitness
    class abstractFitnessCal
    {
    public:
        virtual int cal_fitness(const std::string &chromosome) const = 0 ;
        virtual ~abstractFitnessCal() {};
    };
}

#endif