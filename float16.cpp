#include "float16.h"
#include "opEx.h"
#include <math.h>
using namespace std;
double float16::OF = 65504;
double float16::UF = pow(2,-24);
int float16::bias = 15;
float16 float16::zero = "0000000000000000";
float16::float16(std::string b): floatP(b){ }
float16::float16(const char* s): floatP(s){ }
float16::float16(std::string::const_iterator first,std::string::const_iterator last):
  floatP(first, last) { }
float16::float16(double d): floatP(toBin(d)) { }
float16::float16(int d): floatP(toBin(d)) { }
void float16::conj(){
  front() = isNeg() ? '0' : '1';
}
void float16::inc(std::string& res){
  int it = res.length()-1;
  bool carry = true;
  while(it>=0 && carry){
    if(res[it]=='0'){
      res[it] = '1';
      carry = false;
    }
    else res[it] = '0';
    --it;
  }
  if(carry) throw ofEx();
}
sigMag float16::checkExpOF(const sigMag exp1, sigMag exp2){
  exp2 = exp2 - sigMag(bias);
  try{ exp2 = exp2+exp1; }
  catch(ofEx){ throw ofEx(); }
  if(exp2=="011111") throw ofEx();
  if(exp2.isNeg()) throw ufEx();
  return exp2;
}
sigMag float16::mul(const sigMag& mant1, const sigMag& mant2){
  auto it = mant2.end()-1;
  sigMag res = zero;
  //cout << mant1 << endl << mant2 << endl;
  for(int i=0; it>=mant2.begin(); --it,++i){
    std::string b;
    if((*it)=='1'){
      //cout << i << endl;
      b.insert(0,i,'0');
      b.insert(0,mant1);
      sigMag buffer(b);
      //cout << res << " +" << endl << buffer << " =" << endl;
      while(res.length()!=buffer.length()) res.insert(0,"0");
      res = res + buffer;
      //cout << res << endl;
    }
  }
  res.erase(12);
  return res;
}
void float16::dec(std::string& res){
  bool carry = true;
    for(int i=res.length()-1; i>=0 && carry; --i){
      if(res[i] == '1'){
        res[i] = '0';
        carry = false;
      }else
        res[i] = '1';
    }
  if(carry) throw ofEx();
}
void float16::round(std::string& res, double& x, double z){
  while(z<2*x){
    inc(res);
    x -= z;
  }
}
std::string float16::buildStr(double& x, int j){
  double y = pow(2,j);
  if(x>=y){
    x = x - y;
    return "1";
  }
  return "0";
}
std::string float16::buildStr(int& x, int j){
  int y = pow(2,j);
  if(x>=y){
    x = x - y;
    return "1";
  }
  return "0";
}
std::string float16::toBin(double x){
  if(!x) return zero;
  else{
    if(x>OF || x<-(OF)) throw ofEx();
    if(x>UF && x<-(UF)) throw ufEx();
    bool neg = false;
    if(x<0){
      x = x*(-1);
      neg = true;
    }
    std::string res;
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
    std::string exp;
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
      e += bias;
      i = 4;
      while(i>=0){
        exp.append(buildStr(e,i));
        i--;
      }
    }
    double z = pow(2,lsb);
    try { round(res,x,z); }
    catch(ofEx) { inc(exp); }
    res.insert(0,exp);
    neg ? res.insert(0,"1") : res.insert(0,"0");
    return res;
  }
}
double float16::toVal() const{
  std::string exp = substr(1,5);
  std::string mant = substr(6,10);
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
  e ? e -= bias : e = -14;
  return isNeg() ? -(num*pow(2,e)) : num*pow(2,e);
}
void float16::normalize(binary& mant, binary& exp) const{
  int i = mant.find_first_of('1');
  if(exp!="000000"){
    while(i!=2){
      if(i<2){
        mant.shiftR();
        //inc(exp);
        ++i;
      }else{
        mant.shiftL();
        dec(exp);
        --i;
      }
      //cout << mant << ' ' << exp << endl;
    }
    if(exp.isNeg()) throw ufEx();
  }
  mant.erase(0,3);
  exp.erase(0,1);
}
float16& float16::operator+(const binary& r){
  if(*this==zero) return *this = r;
  if(r==zero) return *this;
  std::string tmp;
  sigMag exp1 = substr(1,5); exp1.insert(0,"0");
  sigMag exp2 = r.substr(1,5); exp2.insert(0,"0");
  tmp = (exp1=="000000") ? "00" : "01";
  sigMag mant1 = substr(6,10); mant1.insert(0,tmp);
  tmp = (exp2=="000000") ? "00" : "01";
  sigMag mant2 = r.substr(6,10); mant2.insert(0,tmp);
  bool out = false;
  while(exp1!=exp2 && !out){
    if(exp1>exp2){
      ++exp2;
      mant2.shiftR();
      if(mant2=="000000000000")
        out = true;
    }
    else{
      ++exp1;
      mant1.shiftR();
      if(mant1=="000000000000")
        out = true;
    }
  }
  if(out) return mant1=="000000000000" ? *this = r : *this;
  tmp = isNeg() ? "1" : "0";
  mant1.insert(0,tmp);
  tmp = r.isNeg() ? "1" : "0";
  mant2.insert(0,tmp);
  sigMag mant = mant1+mant2;
  sigMag exp = exp1;
  if(mant.isNeg()){
    tmp = "1";
    mant.front() = '0';
  }
  else tmp = "0";
  if(mant=="0000000000000") return zero;
  if(mant[1]=='1'){
    mant.shiftL();
    ++exp;
    if(exp=="011111") throw ofEx();
  }
  normalize(mant, exp);
  return *this = tmp+exp+mant;
}
float16& float16::operator-(const binary& r){
  float16 s = r; s.conj();
  return *this = (*this)+s;
}
float16& float16::operator*(const binary& r){
  if(*this==zero) return *this;
  if(r==zero) return *this = zero;
  std::string tmp;
  sigMag exp1 = substr(1,5); exp1.insert(0,"0");
  sigMag exp2 = r.substr(1,5); exp2.insert(0,"0");
  sigMag mant1 = substr(6,10);
  sigMag mant2 = r.substr(6,10);
  char sign = checkSign(isNeg(),r.isNeg()) ? '1' : '0';
  setMant(exp1,mant1); r.setMant(exp2,mant2);
  sigMag exp;
  try{ exp = checkExpOF(exp1,exp2); }
  catch(ofEx){ throw ofEx(); }
  catch(ufEx) { throw ufEx(); }
  sigMag mant = mul(mant1,mant2);
  if(exp=="000000" || exp=="100000") mant.shiftR();
  mant.erase(0,2);
  exp.erase(0,1);
  return *this = sign+exp+mant;
}
float16& float16::operator/(const binary& r){
  //return (toVal()/r.toVal());
}
std::ostream& operator<<(std::ostream& os, const float16& p){
  std::string x(p);
  return os << x << ' ' << p.toVal();
}
