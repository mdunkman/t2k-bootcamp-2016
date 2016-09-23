//
// bootcamp/day_2/example_1/example.cxx
//
// Something a bit more complicated
//

#include <cstdlib> // for std::srand(...)

#include "example.h"
using namespace version2;

int main()
{
    std::srand(20160924); // use fixed seed
    TH1D histogram = make_histogram("uniform", "Uniform Random Numbers", 5, 0, 1);
    histogram.Print();
    return 0;
}

