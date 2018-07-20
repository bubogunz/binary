#include "twosComp.h"
#include "ofEx.h"
#include <math.h>
int twosComp::min = -32768;
int twosComp::max = 32767;
twosComp::twosComp(std::string s): integer(s){ }
twosComp::twosComp(const char* s): integer(s){ }
twosComp::twosComp(int i){
  toBin(i);
}
void twosComp::toBin(int x){
  if(!x) setBin("0000000000000000");
  else{
    if(x<twosComp::min || x>twosComp::max) throw ofEx();
    int i = 15;
    binary res;
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
  }
}
int twosComp::toVal() const{
  int i = 15;
  int num = 0;
  binary b = getBin();
  if(isNeg()) num = -(pow(2,i));
  i--;
  while(i>=0){
    int y = pow(2,i);
    if(b[15-i] == '1') num += y;
    i--;
  }
  return num;
}
std::ostream& operator<<(std::ostream& os, const twosComp& s){
    return os << s.getBin() << ' ' <<s.toVal();
}
