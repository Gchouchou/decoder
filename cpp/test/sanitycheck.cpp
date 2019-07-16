#include <iostream>
#include <random>

int rand_num(int start, int end) {
    int range = end - start;
    return start + (std::rand()%range);
}

int main(int argc, char const *argv[])
{
    srand((unsigned)(time(0)));
    for (int i = 0; i < 10; i++)
    {
        float percentage = rand_num(0,100) / (float) 100;
        if (percentage > .80)
        {
            std::cout << "got it";
        }
    }
    return 0;
}
