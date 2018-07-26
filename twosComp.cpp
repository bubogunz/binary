#include "twosComp.h"
#include "opEx.h"
#include <math.h>
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
void twosComp::toBin(int x){
  switch(x){
    case 0:
      setBin(zero);
      break;
    default:
      if(x<twosComp::minV || x>twosComp::maxV) throw ofEx();
      int i = zero.length()-1;
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
      setBin(res);
      break;
  }
}
int twosComp::toVal() const{
  int i, k;
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
twosComp& twosComp::operator++(){
  bool carry = true; twosComp& x = *this;
  if(x==maxB) throw ofEx();
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
twosComp& twosComp::operator+(const binary& r){
  return zero;
}
twosComp& twosComp::operator-(const binary& r){
  return zero;
}
twosComp& twosComp::operator*(const binary& r){
  return zero;
}
twosComp& twosComp::operator/(const binary& r) {
  return zero;
}
std::ostream& operator<<(std::ostream& os, const twosComp& s){
    return os << s.getBin() << ' ' <<s.toVal();
}
