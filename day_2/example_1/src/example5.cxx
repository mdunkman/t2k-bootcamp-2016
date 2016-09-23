#include "example5.h"

#include <vector>
#include <cstdlib>      // for std::rand, RAND_MAX
#include <algorithm>    // for std::generate

namespace bootcamp {
TH1D make_histogram_5(const char* name, const char* title, int nbins, double min, double max) 
{
    std::vector<double> bins(nbins+1);
    {
        //
        // Here starts 'local scope'.
        // It means that 'generator' will _only_ be defined until the '}'
        //
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
        };
        std::generate(bins.begin(), bins.end(), generator(nbins, min, max));

        //
        // This is the end of local scope, you can no longer use 'generator'
        //
    }
    //
    // That means the following line will not compile. ---!--- Test it ---!---
    // generator test(0,0,0);
    //

    TH1D histogram(name, title, nbins, &bins.front());

    for (int i=0; i!=10000; ++i) {
		double random_variable = static_cast<double>(std::rand())/RAND_MAX;
		histogram.Fill(random_variable);
    }
    return histogram;
}

};

