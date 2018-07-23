#include "float16.h"
#include "opEx.h"
#include <math.h>
double float16::OF = 65504;
double float16::UF = pow(2,-24);
int float16::bias = 15;
float16::float16(std::string b): floatP(b){ }
float16::float16(const char* s): floatP(s){ }
float16::float16(double d) {
  toBin(d);
}
char float16::buildStr(double& x, int j) const{
  double y = pow(2,j);
  if(x>=y){
    x = x - y;
    return '1';
  }
  return '0';
}
char float16::buildStr(int& x, int j) const{
  int y = pow(2,j);
  if(x>=y){
    x = x - y;
    return '1';
  }
  return '0';
}
void float16::round(binary& res, double& x, double z) const{
  while(z<2*x){
    ++res;
    x -= z;
  }
}
void float16::toBin(double x){
  if(!x) setBin("0000000000000000");
  else{
    if(x>float16::OF || x<-(float16::OF)) throw ofEx();
    if(x>float16::UF && x<-(float16::UF)) throw ufEx();
    bool neg = false;
    if(x<0){
      x = x*(-1);
      neg = true;
    }
    float16 res;
    int e = 0, i = 15;
    while(!e && i>=-14){
      double y = pow(2,i);
      if(x>=y){
        e = i;
        x -= y;
        for(int j=e-1; j>e-11; --j)
          res.append(buildStr(x,j));
      }
      i--;
    }
    binary exp;
    int lsb; //least significative bit
    if(!e){ //number is lesser than 2^-14: MSB is explicit and exp bits are all 0s
      lsb = -24;
      exp = "00000";
      i = -1;
      while(i>=-10){
        res.append(buildStr(x,i-14));
        i--;
      }
    }else{ //number is goe than 2^-14: MSB is implicit and biased exp is at least 1
      lsb = e-10;
      e += float16::bias;
      i = 4;
      while(i>=0){
        exp.append(buildStr(e,i));
        i--;
      }
    }
    double z = pow(2,lsb);
    round(res,x,z);
    res.insert(0,exp);
    neg ? res.insert(0,"1") : res.insert(0,"0");
    setBin(res);
  }
}
double float16::toVal() const{
  binary exp = substr(1,5);
  binary mant = substr(6,10);
  double num = 0;
  if(exp!="00000")
    num = 1;
  for(int i=0, j=-1; i<10; ++i,--j)
    if(mant[i]=='1')
      num += pow(2,j);
  int e = 0;
  for(int i=0, j=4; i<5; ++i,--j)
    if(exp[i]=='1')
      e += pow(2,j);
  e ? e -= float16::bias : e = -14;
  return isNeg() ? -(num*pow(2,e)) : num*pow(2,e);
}
int float16::sumExp(const binary& bin, int start, int pwr, int end) const{
  int e = 0;
  for(int i=start, j=pwr; i<end; ++i,--j)
    if(bin[i]=='1')
      e += pow(2,j);
  return e;
}
int* float16::min(int& a, int& b){
  return a<b ? &a : &b;
}
int* float16::max(int& a, int& b){
  return !(a<b) ? &b : &a;
}
float16 float16::operator+(const float16& r) const{
  return (toVal()+r.toVal());
}
float16 float16::operator-(const float16& r) const{
  return (toVal()-r.toVal());
}
float16 float16::operator*(const float16& r) const{
  return (toVal()*r.toVal());
}
float16 float16::operator/(const float16& r) const{
  return (toVal()/r.toVal());
}
std::ostream& operator<<(std::ostream& os, const float16& p){
  return os << p.getBin() << ' ' << p.toVal();
}
