#ifndef fitnessh
#define fitnessh
#include <string>

// abstract class that returns the int from cal fitness
class AbstractFitnessCal
{
public:
    virtual int cal_fitness(std::string chromosome) const = 0 ;
    virtual ~AbstractFitnessCal() {};
};

#endif