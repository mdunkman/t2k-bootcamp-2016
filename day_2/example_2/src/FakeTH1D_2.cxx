#include "FakeTH1D_2.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <iterator>

namespace version2 {

// Default constructor (using the approach from 'day_2/example_1/src/example6.cxx'
TH1D::TH1D(const char* name_, const char* title_, int nbins_, double min_, double max_)
    : name(name_)
    , title(title_)
    , nbins(nbins_)
    , bins(nbins+1, ((max_ - min_)/nbins_)) //< Look ma! No new!
    , bin_contents(nbins+1, 0)
{
    bins.front() = min_;
    std::partial_sum(bins.begin(), bins.end(), bins.begin());

    // 
    // std::vectors are super safe and do not require the try-catch block
    // around the constructor. Simple code is happy code!
    //
}

// Copy constructor
TH1D::TH1D(const TH1D& rhs)
    : name(rhs.name)
    , title(rhs.title)
    , nbins(rhs.nbins)
    , bins(rhs.bins)                    //< std::vectors have copy constructors, so 
    , bin_contents(rhs.bin_contents)    //  transferring the bins and contents is trivial.
{ }

// Assignment operator
TH1D& TH1D::operator=(const TH1D& rhs)
{
    name = rhs.name;
    title = rhs.title;
    nbins = rhs.nbins;
    bins = rhs.bins;                    //< std::vectors also have assignment operators, so
    bin_contents = rhs.bin_contents;    //  transferring the bins and contents is still trivial.
    return *this;
}

// Secondary constructor
TH1D::TH1D(const char* name_, const char* title_, int nbins_, const std::vector<double>& bins_)
    : name(name_)
    , title(title_)
    , nbins(nbins_)
    , bins(bins_)
    , bin_contents(bins.size(), 0)
{ }

TH1D::~TH1D()
{
    //
    // No new means no delete!
    // I love me a destructor with no content.
    //
}

int TH1D::Fill(double value) {
    int bin = FindBin(value);
    //
    // Use the pre-increment operator, which does 2 things:
    //      1. increment the value of the object
    //      2. return a reference to the object (no copies made).
    //
    ++bin_contents.at(bin);
    return bin;
}

double TH1D::Integral() const {
    //
    // Read all about accumulate:
    //      http://en.cppreference.com/w/cpp/algorithm/accumulate
    //
    return std::accumulate(bin_contents.begin(), bin_contents.end(), 0);
}

int TH1D::FindBin(double value) const {
    //
    // Read all about lower_bound:
    //      http://en.cppreference.com/w/cpp/algorithm/lower_bound
    // it is does exactly what we want!
    //
    // Especially interesting is the complexity of lower_bound:
    //      at most log_2(N) + constant
    //  for RandomAccessIterator's (like we have for std::vector).
    //
    //  The implementation is left to the algorithm's team at g++/clang,
    //  so it is highly optimized for just about any hardware configuration.
    //  I know I wouldn't want to spend time implementing a binary search
    //  by hand here, especially when somebody else already has!
    //
    const_bin_iterator bin = std::lower_bound(bins.begin(), bins.end(), value);

    //
    // If the value is not in the range, the algorithm returns bins.end(), which
    // is one past the last accessible bin... but we are using the final bin as
    // overflow, so we'll just stick it there by decrementing the iterator once.
    //
    if (bin == bins.end()) { --bin; }

    //
    // These iterators are valid on the vector of bin edges, but we want to use
    // them on the vector of bin_contents. We can get the index of the found bin
    // using std::distance, which---in this case---counts the number of elements
    // between bins.begin() and the found bin.
    //
    // std::distance is guaranteed to be no worse than O(N), and is actually
    // constant for RandomAccessIterator's (like we have for std::vector).
    //
    return std::distance(bins.begin(), bin);

    //
    // NB: By using these algorithms, we have reduced the complexity of 
    // FindBin from O(N) to O(log_2(N)). If there were many bins, this
    // would be a huge savings, and the code looks significantly cleaner
    // thereby decreasing the chance of there being errors.
    //
}

void TH1D::Print() const {
    const double integral = Integral();
    std::cout << std::fixed << std::setprecision(4)
              << name << ": " << title << '\n'
              << "========================================================================\n";

    int bin = 0;
    std::cout << "Bin " << std::setw(3) << bin << ": (" << std::setw(8) << "-inf, " << bins.at(bin) << "] = "
              << bin_contents.at(bin) / integral << '\n';
    bin += 1;
    for (; bin!=nbins+1; ++bin) 
    {
        std::cout << "Bin " << std::setw(3) << bin << ": (" << bins.at(bin-1) << ", " << bins.at(bin) << "] = "
                  << bin_contents.at(bin)  / integral<< "\n";
    }
    std::cout << "Bin " << std::setw(3) << bin << ": (" << bins.at(bin-1) << std::setw(8) << std::left << ", +inf"<< "] = "
              << bin_contents.at(bin-1) / integral << "\n"
              << "========================================================================\n"
              << std::endl;
    return;
}

};

