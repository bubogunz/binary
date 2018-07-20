#ifndef FLOAT16_H
#define FLOAT16_H
#include "floatP.h"
class float16: public floatP{
  static double OF; //overflow
  static double UF; //underflow
  static int bias;
  void toBin(double);
  int sumExp(const binary&, int =0, int =4, int =5) const;
  static int* min(int&, int&);
  static int* max(int&, int&);
  static char buildStr(double&, int);
  static char buildStr(int&, int);
public:
    float16(std::string ="0000000000000000");
    float16(const char*);
    float16(double);
    double toVal() const;
    float16 operator+(const float16&) const;
};
std::ostream& operator<<(std::ostream&, const float16&);
#endif // FLOAT16_H
