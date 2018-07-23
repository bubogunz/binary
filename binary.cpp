#include "binary.h"
#include "opEx.h"
binary::binary(std::string s): std::string(s) { }
binary::binary(const char* s): std::string(s) { }
binary::binary(const binary& s): std::string(s) { }
binary::binary(std::string::const_iterator first, std::string::const_iterator last):
        std::string(first,last) { }
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
void binary::complement(){
  unsigned int i = 0;
  for(;i<this->length(); ++i)
      (*this)[i] == '1' ? (*this)[i] = '0'
                        : (*this)[i] = '1';
}
binary& binary::operator--(){
  bool carry = true; binary& x = *this;
    for(int i=length()-1; i>=0 && carry; --i){
      if(x[i] == '1'){
        x[i] = '0';
        carry = false;
      }else
        x[i] = '1';
    }
  if(carry) throw ofEx();
  return *this;
}
binary& binary::operator++(){
  bool carry = true; binary& x = *this;
    for(int i=length()-1; i>=0 && carry; --i){
      if(x[i] == '0'){
        x[i] = '1';
        carry = false;
      }else
        x[i] = '0';
    }
  if(carry) throw ofEx();
  return *this;
}
