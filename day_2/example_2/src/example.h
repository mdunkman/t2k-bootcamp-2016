#ifndef BOOTCAMP_DAY2_EXAMPLE_H
#define BOOTCAMP_DAY2_EXAMPLE_H

#include "FakeTH1D.h"
#include "FakeTH1D_2.h"


namespace version1 {
TH1D make_histogram(const char* name, const char* title, int nbins, double min, double max);
};
namespace version2 {
TH1D make_histogram(const char* name, const char* title, int nbins, double min, double max);
};


#endif /*BOOTCAMP_DAY2_EXAMPLE_H*/
