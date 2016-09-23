#include "example.h"

#include <iostream>
#include <vector>
#include <cstdlib>      // for std::rand, RAND_MAX
#include <algorithm>    // for std::generate
#include <numeric>

namespace version1 {
TH1D make_histogram(const char* name, const char* title, int nbins, double min, double max) 
{
    TH1D histogram(name, title, nbins, min, max);
    for (int i=0; i!=10000; ++i) {
		double random_variable = static_cast<double>(std::rand())/RAND_MAX;
		histogram.Fill(random_variable);
    }
    return histogram;
}
};

namespace version2 {
TH1D make_histogram(const char* name, const char* title, int nbins, double min, double max) 
{
    TH1D histogram(name, title, nbins, min, max);
    for (int i=0; i!=10000; ++i) {
		double random_variable = static_cast<double>(std::rand())/RAND_MAX;
		histogram.Fill(random_variable);
    }
    return histogram;
}
};

