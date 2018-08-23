#ifndef FLOAT16_H
#define FLOAT16_H
#include "floatP.h"
#include "sigMag.h"
class float16: public floatP{
  static double OF; //overflow
  static double UF; //underflow
  static int bias;
  static float16 zero;
  std::string toBin(double) const override;
  sigMag mul(const sigMag&, const sigMag&, sigMag&) const override;
  sigMag div(sigMag&, sigMag&, sigMag&) const override;
  sigMag checkExpMul(const sigMag, sigMag) const override;
  sigMag checkExpDiv(sigMag, const sigMag) const override;
  static void normPlus(binary&, binary&);
  static void norm(sigMag&, sigMag&);
public:
  float16(std::string ="");
  float16(const char*);
  float16(double);
  float16(int);
  double toVal() const override;
  float16& operator+(const binary&) override;
  float16& operator-(const binary&) override;
  float16& operator*(const binary&) override;
  float16& operator/(const binary&) override;
};
#endif // FLOAT16_H
