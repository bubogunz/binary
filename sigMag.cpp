#include "sigMag.h"
#include "opEx.h"
#include <math.h>
int sigMag::min = -32767;
int sigMag::max = 32767;
sigMag sigMag::zero = "0000000000000000";
sigMag::sigMag(std::string s): integer(s) {
   toVal();
}
sigMag::sigMag(const char* s): integer(s) {
   toVal();
}
sigMag::sigMag(int i){
  toBin(i);
}
sigMag::sigMag(std::string::const_iterator first, std::string::const_iterator last):
      integer(first,last) { }
void sigMag::toBin(int x){ // O(1)
  switch(x){
    case 0:
      setBin(sigMag::zero);
      break;
    default:
      if(x<sigMag::min || x>sigMag::max) throw ofEx();
      sigMag res;
      if(x<0){
        res.append('1');
        x = x*(-1);
      }else res.append('0');
      int i = 14;
      while(i>=0){
          res.append(buildStr(x,i));
          i--;
      }
      setBin(res);
      break;
  }
}
int sigMag::toVal() const{
    int i = length()-2;
    int num = 0;
    binary b = getBin();
    while(i>=0){
        if(b[length()-1-i] == '1')
            num += pow(2,i);
        i--;
    }
    return isNeg() ? -num : num;
}
void sigMag::twosComp(sigMag& s) const{
  if(s!=sigMag::zero){
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
      break;
    }
    case '1': {
      for(int i=length()-1; i>0 && carry; --i){
        if(x[i] == '0'){
          x[i] = '1';
          carry = false;
        }else
          x[i] = '0';
      }
      if(carry){
        x = sigMag::zero;
        throw ofEx();
      }
      break;
    }
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
        x = sigMag::zero;
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
bool sigMag::checkSign(bool o1, bool o2) const{
  if(!o1){
    if(o2)
      return true;
    return false;
  }
  if(o2)
    return false;
  return true;
}
bool sigMag::operator<=(const sigMag& r) const{
  if(isNeg() && !r.isNeg()) return true;
  if(!isNeg() && r.isNeg()) return false;
  std::string a(begin()+1,end());
  std::string b(r.begin()+1,r.end());
  if(!isNeg()){
    if(a<b || a==b) return true;
    else return false;
  }
  if(a>b || a==b) return true;
  else return false;
}
bool sigMag::operator<(const sigMag& r) const{
  if(isNeg() && !r.isNeg()) return true;
  if(!isNeg() && r.isNeg()) return false;
  std::string a(begin()+1,end());
  std::string b(r.begin()+1,r.end());
  if(!isNeg()) return a<b ? true : false;
  return a<b ? false : true;
}
bool sigMag::operator>(const sigMag& r) const{
  if(isNeg() && !r.isNeg()) return false;
  if(!isNeg() && r.isNeg()) return true;
  std::string a(begin()+1,end());
  std::string b(r.begin()+1,r.end());
  if(!isNeg()) return a>b ? true : false;
  return a>b ? false : true;
}
bool sigMag::operator>=(const sigMag& r) const{
  if(isNeg() && !r.isNeg()) return false;
  if(!isNeg() && r.isNeg()) return true;
  std::string a(begin()+1,end());
  std::string b(r.begin()+1,r.end());
  if(!isNeg()){
    if(a>b || a==b) return true;
    else return false;
  }
  if(a<b || a==b) return true;
  else return false;
}
sigMag& sigMag::operator+(const binary& r) {
  sigMag& x = *this;
  sigMag res = *this;
  if(res!=sigMag::zero){
    if(r!=sigMag::zero){
      sigMag op = r;
      switch(x[0]){
        case '0':{
          switch (r[0]) {
            case '0': { //(+a)+(+b)
              plus(res, op);
                if(res[0] == '1')
                  throw ofEx();
              break;
            }
            case '1': { //(+a)+(-b)
              discord(res, op);
            }
            default: break;
          }
          break;
        }
        case '1': {
          switch(r[0]){
            case '0': { //(-a)+(+b)
              discord(op, res);
              res = op;
              break;
            }
            case '1': { //(-a)+(-b)
              plus(res, r.getBin());
              if(res[0] == '0')
                throw ofEx();
              break;
            }
            default: break;
            }
          break;
        }
      default: break;
      }
    return *this = res;
    }else
      return *this = res;
  }else
    return *this = r;
}
sigMag& sigMag::operator-(const binary& r) {
  sigMag op = r;
  if(op!=sigMag::zero){
    op[0] == '0' ? op[0] = '1' : op[0] = '0';
    return *this = (*this)+op;
  }
  return *this;
}
sigMag& sigMag::operator*(const binary& r) {
  if((*this)==sigMag::zero || r==sigMag::zero) return sigMag::zero;
  sigMag res = sigMag::zero, op = r; op[0] = '0';
  sigMag mant(this->begin(),this->end()); mant[0] = '0';
  auto it = op.end()-1;
  for(int i=0; it>=op.begin(); --it,++i){
    std::string b;
    if((*it)=='1'){
      b.insert(0,i,'0');
      b.insert(0,mant);
      auto x = b.begin()+(b.length()-(this->length()));
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
  bool wasNeg = (*this)[0] =='0' ? false : true;
  if(wasNeg) (*this)[0] = '0';
  auto it=begin();
  while(*(it+1)!='1' && it!=end())
    ++it;
  erase(begin(),it);
  sigMag y = r;
  y[0] = '0';
  it = y.begin();
  while(*(it+1)!='1' && it!=y.end())
    ++it;
  y.erase(y.begin(),it);
  sigMag x(begin(),begin()+y.length()), res;
  if(x<y && length()<y.length()) return zero;
  if(x<y) x.append((*this)[x.length()]);
  res.append('1');
  x = x - y;
  y.insert(0, "0");
  it = begin()+y.length();
  while(x.length()<length()){
    x.append(*it);
    if(x<y) res.append('0');
    else{
      res.append('1');
      x = x - y;
    }
    y.insert(0, "0");
    ++it;
  }
  while(res.length()<zero.length())
    res.insert(0,"0");
  if(checkSign(wasNeg,r.isNeg())) res.insert(0, "1");
  else res.insert(0,"0");
  return *this = res;
}
std::ostream& operator<<(std::ostream& os, const sigMag& s){
    return os << s.getBin() << ' ' << s.toVal();
}
