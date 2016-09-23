#ifndef BOOTCAMP_DAY2_EXAMPLE_1_H
#define BOOTCAMP_DAY2_EXAMPLE_1_H

#include "FakeTH1D.h"
namespace bootcamp {
    TH1D make_histogram_1(const char* name, const char* title, int nbins, double min, double max);
};

#endif /*BOOTCAMP_DAY2_EXAMPLE_1_H*/

