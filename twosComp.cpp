#include "twosComp.h"
#include "opEx.h"
#include <math.h>
using namespace std;
int twosComp::min = -32768;
int twosComp::max = 32767;
twosComp twosComp::zero = "0000000000000000";
twosComp::twosComp(std::string s): integer(s) { }
twosComp::twosComp(const char* s): integer(s) { }
twosComp::twosComp(int i): integer(toBin(i)) { }
twosComp::twosComp(std::string::const_iterator first, std::string::const_iterator last):
  integer(first,last) { }
std::string twosComp::toBin(int x) const{
  twosComp res;
  switch(x){
    case 0:
      res = zero;
      break;
    default:
      if(x<min || x>max) throw ofEx();
      int i = zero.length()-1;
      if(x<0){
	x += pow(2,i);
	res.append("1");
      }else res.append("0");
      i--;
      while(i>=0){
	res.append(buildStr(x,i));
	--i;
      }
      break;
  }
  return res;
}
int twosComp::toVal() const{
  int i;
  unsigned int k;
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
  if(x=="1000000000000000") throw ofEx();
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
  std::string::const_iterator cit1 = res.end()-1;
  std::string::const_iterator cit2 = x.end()-1;
  bool of = false;
  for(; cit1!=res.begin(); --cit1, --cit2){
    twosComp tmp(res.begin(),cit1+1);
    if((*cit2) == '1'){
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
  int n = length(), x = n-1;
  while(n>0){
    if(Q[x]=='1' && Q1=='0')
      A = A - M;
    else if(Q[x]=='0' && Q1=='1')
      A = A + M;
    char c = A.arShiftR();
    Q1 = Q.arShiftR(c);
    --n;
  }
  bool sign = Q.isNeg() ? true : false;
  if(sign!=checkSign(isNeg(),r.isNeg())) throw ofEx();
  return *this = Q;
}
char twosComp::arShiftR(char c){
  binary& x = *this;
  char buffer;
  unsigned int i=0;
  if(c=='\0'){
    buffer = x[0];
    ++i;
  }
  else buffer = c;
  for(; i<length();++i){
    char tmp = x[i];
    x[i] = buffer;
    buffer = tmp;
  }
  return buffer;
}
void twosComp::shiftL(){
  replace(begin(),end()-1,begin()+1,end());
  *(end()-1) = '0';
}
twosComp& twosComp::operator/(const binary& r) {
  if(r==zero) throw zeroEx();
  if(*this==zero) return *this;
  bool neg;
  twosComp& b = *this;
  twosComp y(r);
  if(checkSign(isNeg(),y.isNeg())) // (+a)div(-b) or (-a)div(+b)
    neg = true;
  else neg = false;
  if(isNeg()){
    if(toVal()==min)
      insert(begin(),'0');
    else conj();
  }
  if(y.isNeg()){
    if(y.toVal()==min)
      y.insert(y.begin(),'0');
    else y.conj();
  }
  erase(0,find_first_of('1')-1);
  y.erase(0,y.find_first_of('1')-1);
  if(length()<y.length() || (length()==y.length() && b<y))
    return *this = zero;
  twosComp x = substr(0,y.length()-1);
  twosComp res;
  std::string::const_iterator cit = begin()+x.length();
  while(cit!=end()){
    x.insert(x.end(),*cit);
    y.insert(0,x.length()-y.length(),'0');
    if(x<y) res.append("0");
    else{
      res.append("1");
      x = x - y;
    }
    ++cit;
  }
  res.insert(0,16-res.length(),'0');
  if(neg) res.conj();
  return *this = res;
}
