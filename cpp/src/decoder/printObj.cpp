#include "printObj.h"

#include <iostream>
#include <iomanip>

using namespace std;

void decoder::printParams(decoder::decodeparam &params) {
    cout << "[" << setprecision(2) << params.cscore << ", ";
    cout << setprecision(2) << params.sscore  << ", ";
    cout << setprecision(2) << params.cscale  << ", ";
    cout << setprecision(2) << params.scale << ", ";
    cout << setprecision(2) << params.absScale;
    cout << "]";
}

void decoder::printResults(const array<int,3*3> &results) {
    int index = 0;
    cout << "[";
    for (auto it = results.begin(); it != results.end(); it++, index++) {
        cout << *it;
        if (index != 8) {
            cout << ", ";
        }
    }
    cout << "]";
}