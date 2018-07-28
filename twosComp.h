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
  void plus(twosComp&, twosComp) const;
  void discord(twosComp&, twosComp) const;
  bool checkSign(bool, bool) const;
  void conj();
public:
  twosComp(std::string ="");
  twosComp(const char*);
  twosComp(int);
  twosComp(std::string::const_iterator, std::string::const_iterator);
  int toVal() const;
  twosComp& operator++();
  twosComp& operator--();
  twosComp& operator+(const binary&);
  twosComp& operator-(const binary&);
  twosComp& operator*(const binary&); //Booth's algorithm for 2's complement multiplication
  twosComp& operator/(const binary&);
};
std::ostream& operator<<(std::ostream&, const twosComp&);
#endif // TWOSCOMP_H
