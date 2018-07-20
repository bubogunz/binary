#include "sigMag.h"
#include "ofEx.h"
#include <math.h>
int sigMag::min = -32767;
int sigMag::max = 32767;
sigMag::sigMag(std::string s): integer(s) {
   toVal();
}
sigMag::sigMag(const char* s): integer(s) {
   toVal();
}
sigMag::sigMag(int i){
  toBin(i);
}
void sigMag::toBin(int x){ // O(1)
    if(!x) setBin("0000000000000000");
    else{
      if(x<sigMag::min || x>sigMag::max) throw ofEx();
      binary res;
      int i = 14;
      if(x<0){
        res.append('1');
        x = x*(-1);
      }else res.append('0');
      while(i>=0){
          res.append(buildStr(x,i));
          i--;
      }
      setBin(res);
    }
}
int sigMag::toVal() const{
    int i = 14;
    int num = 0;
    binary b = getBin();
    while(i>=0){
        if(b[15-i] == '1')
            num += pow(2,i);
        i--;
    }
    return isNeg() ? -num : num;
}
std::ostream& operator<<(std::ostream& os, const sigMag& s){
    return os << s.getBin() << ' ' << s.toVal();
}
