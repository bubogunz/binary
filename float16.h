#ifndef FLOAT16_H
#define FLOAT16_H
#include "floatP.h"
class float16: public floatP{
  static double OF; //overflow
  static double UF; //underflow
  static int bias;
  static float16 zero;
  void toBin(double);
  int sumExp(const binary&, int =0, int =4, int =5) const;
  static int* min(int&, int&);
  static int* max(int&, int&);
  char buildStr(double&, int) const;
  char buildStr(int&, int) const;
public:
    float16(std::string ="");
    float16(const char*);
    float16(double);
    double toVal() const;
    void round(floatP&, double&, double) const;
    float16 operator+(const float16&) const;
    float16 operator-(const float16&) const;
    float16 operator*(const float16&) const;
    float16 operator/(const float16&) const;
};
std::ostream& operator<<(std::ostream&, const float16&);
#endif // FLOAT16_H
