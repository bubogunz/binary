#include "integer.h"
#include "sigMag.h"
#include "twosComp.h"
#include <math.h>
integer::integer(std::string s): binary(s) { }
integer::integer(const char* s): binary(s) { }
integer::integer(std::string::const_iterator first, std::string::const_iterator last):
  binary(first,last) { }
std::string integer::buildStr(int& x, int j){
  int y = pow(2,j);
  if(x>=y){
    x = x - y;
    return "1";
  }
  return "0";
}
