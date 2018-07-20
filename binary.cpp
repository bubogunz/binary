#include "binary.h"
#include <algorithm>
binary::binary(std::string s): std::string(s) { }
binary::binary(const char* s): std::string(s) { }
binary::binary(const binary& s): std::string(s) { }
binary binary::getBin() const{
  return *this;
}
bool binary::isNeg() const{
  return (*this)[0]=='1' ? true : false;
}
void binary::popZeroFront(){
  int i = 0;
  while((*this)[i] == '0')
    ++i;
  auto it = begin()+i;
  erase(begin(),it);
}
void binary::pushZeroBack(int length){
  int i = 0;
  while(i<length){
    this->append('0');
    i++;
  }
}
void binary::setBin(const std::string& s){
  *this = s;
}
void binary::append(char c){
  *this += c;
}
void binary::append(const char* c){
  binary d(c);
  *this += d;
}
void binary::append(std::string s){
  *this += s;
}
binary binary::complement() const{
  binary res;
  std::for_each(begin(),end(),[&res](char c){
      c == '1' ? res.append('0')
               : res.append('1');
  });
  return res;
}
binary& binary::operator++(int){
  binary& b = *this;
  if(b[length()-1]=='0')
    b[length()-1] = '1';
  else{
    b[length()-1] = '0';
    bool carry = true;
    for(int i=length()-2; (i>=0) || carry; --i){
      if(b[i]=='0'){
        if(carry){
          b[i] = '1';
          carry = false;
        }
      }else
        if(carry)
          b[i] = '0';
    }
  }
  return *this;
}
