#include "example4.h"

#include <vector>
#include <cstdlib>      // for std::rand, RAND_MAX
#include <algorithm>    // for std::generate

namespace bootcamp {

struct generator {
    const double m;
    const double b;
    int x;
    explicit generator(int nbins, double min, double max)
        : m((max - min)/nbins)
        , b(min)
        , x(0)
    { }

    double operator( )( ) { return b + m*x++; }
    //                                 \ /
    //                                Magic!
    //
    // Don't kick me out of the magicians guild...
    //
    // 'x++' uses the "post-increment operator", this does three things
    //      1. creates a copy of 'x' (yes, it really creates a copy!)
    //      2. increment the value of 'x'
    //      3. return the copy (containing the value before the copy)
    //
    // for more information, refer to:
    //      http://en.cppreference.com/w/cpp/language/operator_incdec
    //  
};

TH1D make_histogram_4(const char* name, const char* title, int nbins, double min, double max) 
{
    std::vector<double> bins(nbins+1);
    std::generate(bins.begin(), bins.end(), generator(nbins, min, max));

    TH1D histogram(name, title, nbins, &bins.front());

    for (int i=0; i!=10000; ++i) {
		double random_variable = static_cast<double>(std::rand())/RAND_MAX;
		histogram.Fill(random_variable);
    }
    return histogram;
}

};

