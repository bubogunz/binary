#ifndef SIGMAG_H
#define SIGMAG_H
#include "integer.h"
class sigMag : public integer { //[-32767, +32767]
  static int min;
  static int max;
  static sigMag zero;
  virtual std::string toBin(int) const override;
  int toVal() const override;
  void twosComp(sigMag&) const;
  void plus(sigMag&, sigMag) const;
  void discord(sigMag&, sigMag) const;
public:
  sigMag(std::string ="");
  sigMag(const char*);
  sigMag(int);
  sigMag(std::string::const_iterator, std::string::const_iterator);
  bool operator<(const sigMag& r) const;
  bool operator>(const sigMag& r) const;
  bool operator<=(const sigMag& r) const;
  bool operator>=(const sigMag& r) const;
  sigMag& operator++() override;
  sigMag& operator--() override;
  sigMag& operator+(const binary&) override;
  sigMag& operator-(const binary&) override;
  sigMag& operator*(const binary&) override;
  sigMag& operator/(const binary&) override;
};
#endif // SIGMAG_H
