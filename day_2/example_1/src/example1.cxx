#include "example1.h"

#include <cstdlib> // for std::rand(), RAND_MAX

namespace bootcamp {

TH1D make_histogram_1(const char* name, const char* title, int nbins, double min, double max) 
{
    //
    // Define an array of double's that has nbins+1 elements.
    //
    double bins[nbins+1];
    for (int bin=0; bin!=nbins+1; ++bin) {
        //
        // Fill the array by linearly interpolating between 'min' and 'max' in 'nbins' steps.
        //
        bins[bin] = min + static_cast<double>(bin)*(max - min)/nbins;
        //                \_____________________/
        //                /
        //             bin is an integer, but we want floating point arithmetic.
        //
    }

    TH1D histogram(name, title, nbins, bins);

    for (int i=0; i!=10000; ++i) {
		double random_variable = static_cast<double>(std::rand())/RAND_MAX;
		histogram.Fill(random_variable);
    }
    return histogram;
}

};

