#include "example3.h"

#include <vector>
#include <cstdlib>      // for std::rand, RAND_MAX
#include <algorithm>    // for std::generate

namespace bootcamp {

//
// Define a new object! This will be a functor (or function object), see
//      http://web.stanford.edu/class/cs106l/course-reader/Ch13_Functors.pdf
// for detailed motivation.
//
struct generator {
    const double m; //< slope
    const double b; //< y-intercept
    int x;          //< the current x-value

    //
    // Define a constructor for the object.
    // 'explicit' means that the arguments must actually be what you demand them to be.
    // It forbids implicit conversions (e.g. casting int's to double's by the compiler).
    //
    explicit generator(int nbins, double min, double max)
        : m( (max-min)/nbins )  //< we construct 'm' with the appropriate value
        , b(min)    //< This is a comma-seperated list, so we choose
        , x(0)      //  to put the comma's in line with the initial colon.
                    //
                    //  ...It is purely a style-choice, but I like it...
                    //
    {
        //
        // We already assigned values to all of our objects in
        // the member initialization list above, so nothing else needs to be done.
        // 
        // For more information, see:
        //  http://en.cppreference.com/w/cpp/language/initializer_list
        //
    }

    //
    // Define the "call operator" for this class.
    // This makes 'generator' a FunctionObject "conceptual type"
    //  (http://en.cppreference.com/w/cpp/concept/FunctionObject)
    //
    // Conceptual types are defined through "duck typing",
    //      "If it looks like a duck, ..., walks like a duck, then it must BE a duck."
    //
    //  This method of typing is particularly useful for templates because
    //  templates cannot make any run-time requests on objects.
    //  Templates are expanded at compile-time to be Plain-Jane functions,
    //  and have no knowledge that they were once generic objects that can do magic.
    //
    // The STL makes extensive use of templates---it's in the name (Standard _Template_ Library).
    //
    //              These parenthesis are attached to 'operator' specifying
    //              |   which operator (the call operator!) we are defining.
    //              |   
    //              |   This is the place for arguments to the function
    //              |   |   for this function, there are no arguements.
    //              |   |
    //              V   V
    double operator( ) ( )
    {
        double retval = m*x + b;
        x += 1;
        return retval;
    }
};

TH1D make_histogram_3(const char* name, const char* title, int nbins, double min, double max) 
{
    std::vector<double> bins(nbins+1);
    //
    // We are now using the 'generate' algorithm to populate the vector, see:
    //  http://en.cppreference.com/w/cpp/algorithm/generate
    //
    std::generate(bins.begin(), bins.end(), generator(nbins, min, max));
    //            \         /   \        /  \_______________________/
    //             \       /     \      /              |
    //              \     /       \    /       Create a temporary functor defined above.
    //               \   /         \  /        This object will be destroyed once the algorithm completes.
    //                \ /           ||         So there is no extra stuff polluting our code (hurrah!).
    //                 |            ||         
    //                 |            Stop generating here.
    //                 Start generating here.

    TH1D histogram(name, title, nbins, &bins.front());

    for (int i=0; i!=10000; ++i) {
		double random_variable = static_cast<double>(std::rand())/RAND_MAX;
		histogram.Fill(random_variable);
    }
    return histogram;
}

};

