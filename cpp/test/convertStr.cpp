#include "tester.h"
#include "convert.h"

int main(int argc, char const *argv[])
{
    algo::algoparam *ab = converter::convert(argv[1]);
    cout << "absScale:" << (ab->absScale)<< "\n";
    cout << "cscale:" << std::to_string(ab->cscale) << "\n";
    cout << "cscore:" << std::to_string(ab->cscore) << "\n";
    cout << "scale" << std::to_string(ab->scale) << "\n";
    cout << "sscore:" << std::to_string(ab->sscore) << "\n";
    gamestate a;
    tester::testAll(a,*ab);
    delete(ab);
    return 0;
}
