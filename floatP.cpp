#include "floatP.h"
#include "opEx.h"
#include <math.h>
floatP::floatP(std::string s): binary(s) { }
floatP::floatP(const char* s): binary(s) { }
//floatP::floatP(std::string::const_iterator first,std::string::const_iterator last):
  //binary(first, last) { }
std::string floatP::buildStr(double& x, int j){
  double y = pow(2,j);
  if(x>=y){
    x = x - y;
    return "1";
  }
  return "0";
}
std::string floatP::buildStr(int& x, int j){
  int y = pow(2,j);
  if(x>=y){
    x = x - y;
    return "1";
  }
  return "0";
}
void floatP::inc(std::string& res){
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
void floatP::dec(std::string& res){
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
void floatP::round(std::string& res, double& x, double z){
  while(z<2*x){
    inc(res);
    x -= z;
  }
}
