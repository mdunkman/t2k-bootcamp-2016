//
// bootcamp/day_2/example_1/example.cxx
//
// Something a bit more complicated
//

#include "example.h"
#include <cstdlib> // for std::srand(...)

int main()
{
    std::srand(20160924); // use fixed seed
    TH1D histogram = bootcamp::make_histogram_5("uniform", "Uniform Random Numbers", 5, 0, 1);
    histogram.Print();
    return 0;
}

