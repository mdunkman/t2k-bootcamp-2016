#ifndef BOOTCAMP_DAY2_EXAMPLE1_FAKE_TH1D_2_H
#define BOOTCAMP_DAY2_EXAMPLE1_FAKE_TH1D_2_H

#include <string>
#include <vector>
namespace version2 {

class TH1D {
  private: 
    std::string name;
    std::string title;
    int nbins;
    std::vector<double> bins;
    std::vector<double> bin_contents;

    typedef std::vector<double>::const_iterator const_bin_iterator;
    typedef std::vector<double>::iterator bin_iterator;

  public:
    explicit TH1D(const char* name_, const char* title_, int nbins_, const std::vector<double>& bins_);
    explicit TH1D(const char* name="htemp",
                  const char* title="Title;X axis title; Y axis title",
                  int nbins=0, double min=0, double max=1);
    TH1D(const TH1D& rhs);
    TH1D& operator=(const TH1D& rhs);
    ~TH1D();

    int Fill(double value);
    int FindBin(double value) const;
    double Integral() const;
    void Print() const;
};

};

#endif/*BOOTCAMP_DAY2_EXAMPLE1_FAKE_TH1D_2_H*/

