#include "FakeTH1D.h"
#include <exception>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>

// Default constructor
TH1D::TH1D(const char* name_, const char* title_, int nbins_, double min_, double max_)
try : name(name_)
    , title(title_)
    , nbins(nbins_)
    , bins(new double[nbins+1])
    , bin_contents(new double[nbins+1])
{

    //                         overflow
    //           underflow     |
    //           |             |
    for (int bin=0; bin!=nbins+1; ++bin) 
    {
        bins[bin] = min_ + static_cast<double>(bin)*(max_ - min_)/nbins;
        bin_contents[bin] = 0;
    }

} catch(std::exception& e) {
    std::cerr << "["<<__FILE__<<":L"<<__LINE__<<"] TH1D default constructor failed: " << e.what() << '\n';
}

// Copy constructor
TH1D::TH1D(const TH1D& rhs)
    try : name(rhs.name)
        , title(rhs.title)
        , nbins(rhs.nbins)
        , bins(new double[nbins+1])
        , bin_contents(new double[nbins+1])
{
    //                         overflow
    //           underflow     |
    //           |             |
    for (int bin=0; bin!=nbins+1; ++bin) 
    {
        bins[bin] = rhs.bins[bin];
        bin_contents[bin] = rhs.bin_contents[bin];
    }

} catch(std::exception& e) {
    std::cerr << "["<<__FILE__<<":L"<<__LINE__<<"] TH1D copy constructor failed: " << e.what() << '\n';
}

// Assignment operator
TH1D& TH1D::operator=(const TH1D& rhs)
try {
    name = rhs.name;
    title = rhs.title;
    nbins = rhs.nbins;

    delete[] bins; bins = new double[nbins+1];
    delete[] bin_contents; bin_contents = new double[nbins+1];
    //                         overflow
    //           underflow     |
    //           |             |
    for (int bin=0; bin!=nbins+1; ++bin) 
    {
        bins[bin] = rhs.bins[bin];
        bin_contents[bin] = rhs.bin_contents[bin];
    }

    return *this;
} catch(std::exception& e) {
    std::cerr << "["<<__FILE__<<":L"<<__LINE__<<"] TH1D assignment operator failed: " << e.what() << '\n';
    throw e;
}

// Secondary constructor
TH1D::TH1D(const char* name_, const char* title_, int nbins_, double* bins_)
try : name(name_)
    , title(title_)
    , nbins(nbins_)
    , bins(new double[nbins+1])
    , bin_contents(new double[nbins+1])
{

    //                         overflow
    //           underflow     |
    //           |             |
    for (int bin=0; bin!=nbins+1; ++bin) 
    {
        bins[bin] = bins_[bin];
        bin_contents[bin] = 0;
    }

} catch(std::exception& e) {
    std::cerr << "["<<__FILE__<<":L"<<__LINE__<<"] TH1D array-of-bins constructor failed: " << e.what() << '\n';
}

TH1D::~TH1D() {
    delete[] bins;
    delete[] bin_contents;
}

int TH1D::Fill(double value) {
    int bin = FindBin(value);
    bin_contents[bin] += 1;
    return bin;
}

double TH1D::Integral() const {
    double integral = 0;
    for (int bin=0; bin != nbins+1; ++bin)
    {
        integral += bin_contents[bin];
    }
    return integral;
}

int TH1D::FindBin(double value) const {
    int bin = 0;
    for (; bin != nbins+1; ++bin)
    {
        if (bins[bin] > value) { break; }
    }
    return bin;
}

void TH1D::Print() const {
    const double integral = Integral();
    std::cout << std::fixed << std::setprecision(4)
              << name << ": " << title << '\n'
              << "========================================================================\n";

    int bin = 0;
    std::cout << "Bin " << std::setw(3) << bin << ": (" << std::setw(8) << "-inf, " << bins[bin] << "] = "
              << bin_contents[bin] / integral << '\n';
    bin += 1;
    for (; bin!=nbins+1; ++bin) 
    {
        std::cout << "Bin " << std::setw(3) << bin << ": (" << bins[bin-1] << ", " << bins[bin] << "] = "
                  << bin_contents[bin]  / integral<< "\n";
    }
    std::cout << "Bin " << std::setw(3) << bin << ": (" << bins[bin-1] << std::setw(8) << std::left << ", +inf"<< "] = "
              << bin_contents[bin] / integral << "\n"
              << "========================================================================\n"
              << std::endl;
    return;
}

