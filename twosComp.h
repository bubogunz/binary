#ifndef TWOSCOMP_H
#define TWOSCOMP_H
#include "integer.h"
class twosComp: public integer { //[-32768, +32767]
  static int min;
  static int max;
  static twosComp zero;
  void toBin(int x);
public:
  twosComp(std::string ="");
  twosComp(const char*);
  twosComp(int);
  int toVal() const;
  twosComp operator+(const twosComp&) const;
  //twosComp& operator++(int);
  twosComp operator-(const twosComp&) const;
  twosComp operator*(const twosComp&) const;
  twosComp operator/(const twosComp&) const;
};
std::ostream& operator<<(std::ostream&, const twosComp&);
#endif // TWOSCOMP_H
