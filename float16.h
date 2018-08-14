#ifndef FLOAT16_H
#define FLOAT16_H
#include "floatP.h"
#include "sigMag.h"
class float16: public floatP{
  static double OF; //overflow
  static double UF; //underflow
  static int bias;
  static float16 zero;
  static std::string toBin(double);
  static std::string buildStr(double&, int);
  static std::string buildStr(int&, int);
  static void inc(std::string&);
  static void dec(std::string&);
  static sigMag mul(const sigMag&, const sigMag&);
  static sigMag checkExpOF(const sigMag, sigMag);
  static void round(std::string&, double&, double);
  void normalize(binary&, binary&) const;
  void conj();
public:
  float16(std::string ="");
  float16(const char*);
  float16(double);
  float16(int);
  float16(std::string::const_iterator,std::string::const_iterator);
  double toVal() const;
  float16& operator+(const binary&);
  float16& operator-(const binary&);
  float16& operator*(const binary&);
  float16& operator/(const binary&);
};
std::ostream& operator<<(std::ostream&, const float16&);
#endif // FLOAT16_H
