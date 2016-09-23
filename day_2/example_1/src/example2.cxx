#include "example2.h"

#include <vector>
#include <cstdlib> // for std::rand(), RAND_MAX

namespace bootcamp {

TH1D make_histogram_2(const char* name, const char* title, int nbins, double min, double max) 
{
    // 
    // Now we're using a vector of double's instead of an array.
    //
    std::vector<double> bins(nbins+1);
    for (int bin=0; bin!=nbins+1; ++bin) {
        bins.at(bin) = min + static_cast<double>(bin)*(max - min)/nbins;
        //  \_____/
        //     Vectors have a _checked_ version of operator[]!
        //     This means that it will check at runtime if 'bin' is within
        //     the allowed bounds [0 <= bin < bins.size()] and throw an
        //     exception instead of blindly reading the memory at the
        //     specified location.
        //
    }

    TH1D histogram(name, title, nbins, &bins.front());
    //                                 /    \______/
    //                                /      / 
    //                               /   This returns the first element of the vector,
    //                              /    it is functionally equivalent to `*bins.begin()`.
    //                             /    
    //                            This is the 'address-of' operator.
    // 
    // This combination returns the address of the first element of the vector.
    // The internal structure of a vector is guaranteed to be contiguous array,
    //  so this is functionally equivalent to a c-style array, which is what TH1D
    //  expects in its constructor.
    //

    for (int i=0; i!=10000; ++i) {
		double random_variable = static_cast<double>(std::rand())/RAND_MAX;
		histogram.Fill(random_variable);
    }
    return histogram;
}

};

