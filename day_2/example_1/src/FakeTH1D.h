#ifndef BOOTCAMP_DAY2_EXAMPLE1_FAKE_TH1D_H
#define BOOTCAMP_DAY2_EXAMPLE1_FAKE_TH1D_H

#include <string>
class TH1D {
  private: 
    std::string name;
    std::string title;
    int nbins;
    double* bins;
    double* bin_contents;

  public:
    explicit TH1D(const char* name_, const char* title_, int nbins_, double* bins_);
    explicit TH1D(const char* name="htemp",
                  const char* title="Title;X axis title; Y axis title",
                  int nbins=0, double min=0, double max=1);
    TH1D(const TH1D& rhs);
    TH1D& operator=(const TH1D& rhs);
    ~TH1D();

    int Fill(double value);
    double Integral() const;
    void Print() const;

  private:
    int FindBin(double value) const;
};


#endif /*BOOTCAMP_DAY2_EXAMPLE1_FAKE_TH1D_H*/

