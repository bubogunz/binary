#include "sigMag.h"
#include "opEx.h"
#include <math.h>
int sigMag::min = -32767;
int sigMag::max = 32767;
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
      if(x<min || x>max) throw ofEx();
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
  std::string::const_iterator cit1 = res.end()-1;
  std::string::const_iterator cit2 = x.end()-1;
  bool of = false;
  for(; cit1!=res.begin(); --cit1, --cit2){
    sigMag tmp(res.begin(),cit1+1);
    if((*cit2) == '1'){
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
    return res;
  }
  if(!isNeg() && r.isNeg()){
    discord(res, op);
    return res;
  }
  if(isNeg() && !r.isNeg()){
    discord(op, res);
    return res = op;
  }
  //isNeg() && r.isNeg()
  res[0] = op[0] = '0';
  try { plus(res, op); }
  catch(ofEx) { throw ofEx(); }
  res[0] = '1';
  return *this = res;
}
sigMag& sigMag::operator-(const binary& r) {
  sigMag op = r;
  if(op!=zero){
    op.front() == '0' ? op.front() = '1' : op.front() = '0';
    return *this = (*this)+op;
  }
  return *this;
}
sigMag& sigMag::operator*(const binary& r) {
  if((*this)==zero || r==zero) return zero;
  sigMag res = zero;
  sigMag op = r; op.front() = '0';
  sigMag mant = *this; mant.front() = '0';
  mant.erase(0,mant.find_first_of('1')-1);
  op.erase(0,op.find_first_of('1')-1);
  std::string::const_iterator cit = op.end()-1;
  bool of = false;
  for(int i=0; cit>=op.begin() && !of; --cit,++i){
    sigMag b;
    if((*cit)=='1'){
      b.insert(0,i,'0');
      b.insert(0,mant);
      if(b.length()>16) of = true;
      else{
	b.insert(0,res.length()-b.length(),'0');
	try { res = res + b; }
	catch(ofEx){ of = true; }
      }
    }
  }
  if(of) throw ofEx();
  if(checkSign(isNeg(),r.isNeg()))
    res.front() = '1';
  return *this = res;
}
sigMag& sigMag::operator/(const binary& r){
  if(r==zero) throw zeroEx();
  if(*this==zero) return *this;
  sigMag& b = *this;
  sigMag y(r);
  char sign;
  if(checkSign(isNeg(),y.isNeg())) // (+a)div(-b) or (-a)div(+b)
    sign = '1';
  else sign = '0';
  front() = y.front() = '0';
  erase(0,find_first_of('1')-1);
  y.erase(0,y.find_first_of('1')-1);
  if(length()<y.length() || (length()==y.length() && b<y))
    return *this = zero;
  sigMag x = substr(0,y.length()-1);
  std::string res="";
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
  res.insert(0,15-res.length(),'0');
  return b = sign+res;
}
