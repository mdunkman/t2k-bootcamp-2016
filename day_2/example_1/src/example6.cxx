#include "example6.h"

#include <vector>
#include <cstdlib>    // for std::rand, RAND_MAX
#include <numeric>    // for std::partial_sum
#include <functional> // for std::plus<double>

namespace bootcamp {
TH1D make_histogram_6(const char* name, const char* title, int nbins, double min, double max) 
{
    //
    // std::generate is a bit complicated and requires a functor...
    // but there is also an algorithm called "partial_sum"!
    //      http://en.cppreference.com/w/cpp/algorithm/partial_sum
    //
    std::vector<double> bins(nbins+1, (max-min)/nbins);
    //                       \_____/  \_____________/
    //                       /        /
    //                      /   Initial value for all the elements
    //                     /    (slope)
    //                    / 
    //               number of entries
    //

    //
    //  We then reset the 0th bin to be the minimum value
    //
    bins.front() = min;

    // 
    // And here's the partial_sum:
    //      Computes the partial sums of the elements in the subranges of
    //      the range [first, last) and writes them to the range
    //      beginning at d_first. This version uses the given binary function op.
    // 
    // Therefore, if we wanted we could use any functor that takes two doubles
    // as arguments.
    //      e.g. partial_sum could calculate a partial product with std::multiplies<double>()
    //           or anything else we can imagine
    //
    std::partial_sum(bins.begin(), bins.end(), bins.begin(), std::plus<double>());
    //               \_________/   \________/  \__________/  \_________________/
    //               /             /           /             /                  
    //              /             /           /        Binary operator to act on the range
    //            /             /     Where we store the result of the binary operator
    //          /         Where should we stop?
    //     Where should we start?
    //

    TH1D histogram(name, title, nbins, &bins.front());

    for (int i=0; i!=10000; ++i) {
		double random_variable = static_cast<double>(std::rand())/RAND_MAX;
		histogram.Fill(random_variable);
    }
    return histogram;
}

};

