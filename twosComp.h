#ifndef TWOSCOMP_H
#define TWOSCOMP_H
#include "integer.h"
class twosComp: public integer { //[-32768, +32767]
  static int minV;
  static int maxV;
  static twosComp minB;
  static twosComp maxB;
  static twosComp zero;
  virtual std::string toBin(int x) const override;
  void plus(twosComp&, twosComp) const;
  void discord(twosComp&, twosComp) const;
  void conj();
  char arShiftR(char ='\0'); //arithmetic shift right
  void shiftL();
public:
  twosComp(std::string ="");
  twosComp(const char*);
  twosComp(int);
  twosComp(std::string::const_iterator, std::string::const_iterator);
  int toVal() const;
  twosComp& operator++();
  twosComp& operator--();
  twosComp& operator+(const binary&) override;
  twosComp& operator-(const binary&) override;
  twosComp& operator*(const binary&) override; //Booth's algorithm for 2's complement multiplication
  twosComp& operator/(const binary&) override;
};
std::ostream& operator<<(std::ostream&, const twosComp&);
#endif // TWOSCOMP_H
