#ifndef SIGMAG_H
#define SIGMAG_H
#include "integer.h"
#include <string> //include Qstring e sul .pro QT += core
class sigMag : public integer { //[-32767, +32767]
  static int minV;
  static int maxV;
  static sigMag minB;
  static sigMag maxB;
  static sigMag zero;
  virtual std::string toBin(int) const override;
  void twosComp(sigMag&) const;
  void plus(sigMag&, sigMag) const;
  void discord(sigMag&, sigMag) const;
public:
  sigMag(std::string ="");
  sigMag(const char*);
  sigMag(int);
  sigMag(std::string::const_iterator, std::string::const_iterator);
  int toVal() const;
  bool operator<(const sigMag& r) const;
  bool operator>(const sigMag& r) const;
  bool operator<=(const sigMag& r) const;
  bool operator>=(const sigMag& r) const;
  sigMag& operator++();
  sigMag& operator--();
  sigMag& operator+(const binary&) override;
  sigMag& operator-(const binary&) override;
  sigMag& operator*(const binary&) override;
  sigMag& operator/(const binary&) override;
};
std::ostream& operator<<(std::ostream&, const sigMag&); //os.str() ritorna cio' che contiene lo stream sotto forma di stringa
#endif // SIGMAG_H
