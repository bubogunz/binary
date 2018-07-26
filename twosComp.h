#ifndef TWOSCOMP_H
#define TWOSCOMP_H
#include "integer.h"
class twosComp: public integer { //[-32768, +32767]
  static int minV;
  static int maxV;
  static twosComp minB;
  static twosComp maxB;
  static twosComp zero;
  void toBin(int x);
public:
  twosComp(std::string ="");
  twosComp(const char*);
  twosComp(int);
  int toVal() const;
  twosComp& operator++();
  twosComp& operator--();
  twosComp& operator+(const binary&);
  twosComp& operator-(const binary&);
  twosComp& operator*(const binary&);
  twosComp& operator/(const binary&);
};
std::ostream& operator<<(std::ostream&, const twosComp&);
#endif // TWOSCOMP_H
