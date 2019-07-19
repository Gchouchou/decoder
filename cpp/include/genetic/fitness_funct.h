#ifndef fitnessh
#define fitnessh

namespace genetic {
    // abstract class that returns the int from cal fitness
    class abstractFitnessCal
    {
    public:
        virtual int cal_fitness(std::string chromosome) const = 0 ;
        virtual ~abstractFitnessCal() {};
    };
}

#endif