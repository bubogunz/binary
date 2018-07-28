#include "twosComp.h"
#include "opEx.h"
#include <math.h>
#include <iostream>
using namespace std;
int twosComp::minV = -32768;
int twosComp::maxV = 32767;
twosComp twosComp::minB = "1000000000000000";
twosComp twosComp::maxB = "0111111111111111";
twosComp twosComp::zero = "0000000000000000";
twosComp::twosComp(std::string s): integer(s){ }
twosComp::twosComp(const char* s): integer(s){ }
twosComp::twosComp(int i){
  toBin(i);
}
twosComp::twosComp(std::string::const_iterator first, std::string::const_iterator last):
      integer(first,last) { }
void twosComp::toBin(int x){
  switch(x){
    case 0:
      *this = zero;
      break;
    default:
      if(x<twosComp::minV || x>twosComp::maxV) throw ofEx();
      unsigned int i = zero.length()-1;
      twosComp res;
      if(x<0){
        x += pow(2,i);
        res.append('1');
      }else res.append('0');
      i--;
      while(i>=0){
        res.append(buildStr(x,i));
        --i;
      }
      *this = res;
      break;
  }
}
int twosComp::toVal() const{
  unsigned int i, k;
  i = k = length()-1;
  int num = 0;
  const twosComp& x = *this;
  if(isNeg()) num = -(pow(2,i));
  i--;
  while(i>=0){
    int y = pow(2,i);
    if(x[k-i] == '1') num += y;
    i--;
  }
  return num;
}
bool twosComp::checkSign(bool o1, bool o2) const{
  if(!o1){
    if(o2)
      return true;
    return false;
  }
  if(o2)
    return false;
  return true;
}
void twosComp::conj(){
  if(*this!=zero){
    if(isNeg()){
      try { --(*this); }
      catch(ofEx) { throw ofEx(); }
      complement();
    }else{
      complement();
      try { ++(*this); }
      catch(ofEx) { throw ofEx(); }
    }
  }
}
twosComp& twosComp::operator++(){
  bool carry = true; twosComp& x = *this;
  for(int i=length()-1; i>0 && carry; --i){
    if(x[i] == '0'){
      x[i] = '1';
      carry = false;
     }else
      x[i] = '0';
  }
  if(carry && x[0] == '1')
    return *this = zero;
  if(carry)
    throw ofEx();
  return *this;
}
twosComp& twosComp::operator--(){
  bool carry = true; twosComp& x = *this;
  if(x==minB) throw ofEx();
  for(int i=length()-1; i>=0 && carry; --i){
    if(x[i] == '1'){
      x[i] = '0';
      carry = false;
    }else{
      x[i] = '1';
    }
  }
 return *this;
}
void twosComp::plus(twosComp& res, twosComp x) const{
  auto it1 = res.end()-1;
  auto it2 = x.end()-1;
  bool of = false;
  for(; it1!=res.begin(); --it1, --it2){
    twosComp tmp(res.begin(),it1+1);
    if((*it2) == '1'){
        try { ++tmp; }
        catch(ofEx){ of = true; }
        res.replace(res.begin(),res.begin()+tmp.length(),
                  tmp.begin(),tmp.end());
    }
  }
  if(of) throw ofEx();
}
twosComp& twosComp::operator+(const binary& r){
  twosComp res = *this;
  if(res==zero) return *this = r;
  if(r==zero) return *this;
  twosComp op = r;
  if(!isNeg() && !r.isNeg()){ //(+a)+(+b)
    try { plus(res, op);}
    catch(ofEx) { throw ofEx(); }
    return *this = res;
  }
  if(!isNeg() && r.isNeg()){
    try {
      plus(res, op);
      res[0] = res[0]=='0' ? '1' : '0';
    }
    catch(ofEx){ }
    return *this = res;
  }
  if(isNeg() && !r.isNeg()){
    try {
      plus(op, res);
      op[0] = op[0]=='0' ? '1' : '0';
    }
    catch(ofEx){ }
    return *this = op;
  }
  //isNeg() && r.isNeg()
  res[0] = op[0] = '0';
  try { plus(res, op); }
  catch(ofEx) {
    res[0] = '1';
    return *this = res;
  }
  throw ofEx();
}
twosComp& twosComp::operator-(const binary& r){
  twosComp op = r;
  if(op!=zero){
    op.conj();
    return *this = (*this)+op;
  }
  return *this;
}
twosComp& twosComp::operator*(const binary& r){
  twosComp A = zero, Q = r, &M = *this; char Q1 = '0';
  unsigned int n = length(), x = n-1;
  while(n>0){
    if(Q[x]=='1' && Q1=='0')
      A = A - M;
    else if(Q[x]=='0' && Q1=='1')
      A = A + M;
    char c = A.arShiftR();
    Q1 = Q.arShiftR(c);
    --n;
  }
  return *this = Q;
}
twosComp& twosComp::operator/(const binary& r) {
  return zero;
}
std::ostream& operator<<(std::ostream& os, const twosComp& s){
    return os << s.getBin() << ' ' << s.toVal();
}
