#ifndef FLOATP_H
#define FLOATP_H
#include "binary.h"
#include "sigMag.h"
class floatP: public binary{
protected:
  static std::string buildStr(double&, int);
  static std::string buildStr(int&, int);
  static void inc(std::string&);
  static void dec(std::string&);
  static void round(std::string&, double&, double);
  virtual std::string toBin(double) const =0;
  virtual sigMag mul(const sigMag&, const sigMag&, sigMag&) const =0;
  virtual sigMag div(sigMag&, sigMag&, sigMag&) const =0;
  virtual sigMag checkExpMul(const sigMag, sigMag) const =0;
  virtual sigMag checkExpDiv(sigMag, const sigMag) const =0;
public:
  floatP(std::string ="");
  floatP(std::string::const_iterator,std::string::const_iterator);
  floatP(const char*);
  virtual double toVal() const =0;
};
#endif // FLOATP_H

