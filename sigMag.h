#ifndef SIGMAG_H
#define SIGMAG_H
#include "integer.h"
#include <string> //include Qstring e sul .pro QT += core
class sigMag : public integer { //[-32767, +32767]
  static int min;
  static int max;
  static sigMag zero;
  void toBin(int);
  void twosComp(sigMag&) const;
  void plus(sigMag&, sigMag) const;
  void discord(sigMag&, sigMag) const;
  bool checkSign(bool o1, bool o2) const;
public:
  sigMag(std::string ="");
  sigMag(const char*);
  sigMag(int);
  sigMag(std::string::const_iterator, std::string::const_iterator);
  int toVal() const;
  sigMag& operator++();
  sigMag& operator--();
  sigMag operator+(const sigMag&) const;
  sigMag operator-(const sigMag&) const;
  sigMag operator*(const sigMag&) const;
  sigMag operator/(const sigMag&) const;
};
std::ostream& operator<<(std::ostream&, const sigMag&); //os.str() ritorna cio' che contiene lo stream sotto forma di stringa
#endif // SIGNUM_H
