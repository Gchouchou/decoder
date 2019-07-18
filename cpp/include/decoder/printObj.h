#ifndef printObjh
#define printObjh
#include "decode_param.h"

#include <array>

// print elements
namespace decoder
{
    void printParams(decoder::decodeparam &param);
    void printResults(const std::array<int,3*3> &results);
} // namespace printStuff
#endif