#include "sigMag.h"
#include "opEx.h"
#include <math.h>
int sigMag::minV = -32767;
int sigMag::maxV = 32767;
sigMag sigMag::minB = "1111111111111111";
sigMag sigMag::maxB = "0111111111111111";
sigMag sigMag::zero = "0000000000000000";
sigMag::sigMag(std::string s): integer(s) { }
sigMag::sigMag(const char* s): integer(s) { }
sigMag::sigMag(int i): integer(toBin(i)) { }
sigMag::sigMag(std::string::const_iterator first, std::string::const_iterator last):
      integer(first,last) { }
std::string sigMag::toBin(int x) const{ // O(1)
  sigMag res = "";
  switch(x){
    case 0:
      res = zero;
      break;
    default:
      if(x<minV || x>maxV) throw ofEx();
      if(x<0){
        res.append("1");
        x = x*(-1);
      }else res.append("0");
      int i = 14;
      while(i>=0){
          res.append(buildStr(x,i));
          i--;
      }
      break;
  }
  return res;
}
int sigMag::toVal() const{
    int i = length()-2;
    int num = 0;
    const sigMag& b = *this;
    while(i>=0){
        if(b[length()-1-i] == '1')
            num += pow(2,i);
        i--;
    }
    return isNeg() ? -num : num;
}
void sigMag::twosComp(sigMag& s) const{
  if(s!=zero){
    s.complement();
    ++s;
  }
}
sigMag& sigMag::operator--(){
  bool carry = true; sigMag& x = *this;
  switch(x[0]){
    case '0': {
      for(int i=length()-1; i>0 && carry; --i){
        if(x[i] == '1'){
          x[i] = '0';
          carry = false;
        }else
          x[i] = '1';
      }
      if(carry){
        carry = false;
        x.complement();
        x[length()-1] = '1';
      }
    }
    break;
    case '1': {
      for(int i=length()-1; i>0 && carry; --i){
        if(x[i] == '0'){
          x[i] = '1';
          carry = false;
        }else
          x[i] = '0';
      }
      if(carry){
        x = zero;
        throw ofEx();
      }
    }
    break;
    default: break;
  }
  return *this;
}
sigMag& sigMag::operator++(){
  bool carry = true; sigMag& x = *this;
  switch(x[0]){
    case '0': {
      for(int i=length()-1; i>0 && carry; --i){
        if(x[i] == '0'){
          x[i] = '1';
          carry = false;
        }else
          x[i] = '0';
      }
      break;
    }
    case '1': {
      for(int i=length()-1; i>0 && carry; --i){
        if(x[i] == '1'){
          x[i] = '0';
          carry = false;
        }else
          x[i] = '1';
      }
      if(!toVal())
        x = zero;
      break;
    }
    default: break;
  }
  if(carry)
    throw ofEx();
  return *this;
}
void sigMag::plus(sigMag& res, sigMag x) const{
  auto it1 = res.end()-1;
  auto it2 = x.end()-1;
  bool of = false;
  for(; it1!=res.begin(); --it1, --it2){
    sigMag tmp(res.begin(),it1+1);
    if((*it2) == '1'){
        try { ++tmp; }
        catch(ofEx){ of = true; }
        res.replace(res.begin(),res.begin()+tmp.length(),
                  tmp.begin(),tmp.end());
    }
  }
  if(of)
    throw ofEx();
}
void sigMag::discord(sigMag& x, sigMag y) const{
  twosComp(y);
  y[0] = '1';
  bool of = false;
  try
    { plus(x,y);  }
  catch(ofEx)
    { of = true; }
  if(!of){
    x.complement();
    --x;
  }
}
bool sigMag::operator>=(const sigMag& r) const{
  if(isNeg() && !r.isNeg()) return true;
  if(!isNeg() && r.isNeg()) return false;
  std::string a = substr(1);
  std::string b = r.substr(1);
  if(a==b) return true;
  if(!isNeg()) return a>b ? true : false;
  return a>b ? false : true;
}
bool sigMag::operator<=(const sigMag& r) const{
  if(isNeg() && !r.isNeg()) return true;
  if(!isNeg() && r.isNeg()) return false;
  std::string a = substr(1);
  std::string b = r.substr(1);
  if(a==b) return true;
  if(!isNeg()) return a<b ? true : false;
  return a<b ? false : true;
}
bool sigMag::operator>(const sigMag& r) const{
  if(isNeg() && !r.isNeg()) return true;
  if(!isNeg() && r.isNeg()) return false;
  std::string a = substr(1);
  std::string b = r.substr(1);
  if(!isNeg()) return a>b ? true : false;
  return a>b ? false : true;
}
bool sigMag::operator<(const sigMag& r) const{
  if(isNeg() && !r.isNeg()) return true;
  if(!isNeg() && r.isNeg()) return false;
  std::string a = substr(1);
  std::string b = r.substr(1);
  if(!isNeg()) return a<b ? true : false;
  return a<b ? false : true;
}
sigMag& sigMag::operator+(const binary& r) {
  sigMag& res = *this;
  if(res==zero) return res = r;
  if(r==zero) return res;
  sigMag op = r;
  if(!isNeg() && !r.isNeg()){
    try { plus(res, op); }
    catch(ofEx) { throw ofEx(); }
    //return *this = res;
    return res;
  }
  if(!isNeg() && r.isNeg()){
    discord(res, op);
    //return *this = res;
    return res;
  }
  if(isNeg() && !r.isNeg()){
    discord(op, res);
    //return *this = op;
    return res = op;
  }
  //isNeg() && r.isNeg()
  res[0] = op[0] = '0';
  try { plus(res, op); }
  catch(ofEx) { throw ofEx(); }
  res[0] = '1';
  //return *this = res;
  return res;
}
sigMag& sigMag::operator-(const binary& r) {
  sigMag op = r;
  if(op!=zero){
    op[0] == '0' ? op[0] = '1' : op[0] = '0';
    return *this = (*this)+op;
  }
  return *this;
}
sigMag& sigMag::operator*(const binary& r) {
  if((*this)==zero || r==zero) return zero;
  sigMag res = zero, op = r; op[0] = '0';
  sigMag mant(begin(),end()); mant[0] = '0';
  auto it = op.end()-1;
  for(int i=0; it>=op.begin(); --it,++i){
    std::string b;
    if((*it)=='1'){
      b.insert(0,i,'0');
      b.insert(0,mant);
      auto x = b.begin()+(b.length()-(length()));
      std::string checkOf(b.begin(),x);
      if(checkOf.find('1')!=std::string::npos)
        throw ofEx();
      b.erase(b.begin(), x);
      sigMag buffer(b);
      res = res + buffer;
    }
  }
  if(checkSign(isNeg(),r.isNeg()))
    res[0] = '1';
  return *this = res;
}
sigMag& sigMag::operator/(const binary& r){
  if(r==zero) throw zeroEx();
  if(*this==zero) return *this;
  sigMag& b = *this;
  char sign = checkSign(isNeg(),r.isNeg()) ? '1' : '0';
  if(isNeg()) front() = '0';
  auto it=begin();
  while(*(it+1)!='1'/* && it!=end()*/)
    ++it;
  erase(begin(),it);
  sigMag y = r;
  y.front() = '0';
  it = y.begin();
  while(*(it+1)!='1'/* && it!=y.end()*/)
    ++it;
  y.erase(y.begin(),it);
  sigMag x = substr(0,y.length()-1), res;
  if(x<y && length()<y.length()) return zero;
  if(x<y) x.insert(x.end(),b[x.length()]);
  res.append("1");
  x = x - y;
  it = begin()+y.length();
  while(x.length()<length()){
    y.insert(0,"0");
    x.insert(x.end(),*it);
    if(x<y) res.append("0");
    else{
      res.append("1");
      x = x - y;
    }
    ++it;
  }
  res.insert(0,15-res.length(),'0');
  return b = sign+res;
}
std::ostream& operator<<(std::ostream& os, const sigMag& s){
  std::string x(s);
  return os << x << ' ' << s.toVal();
}
