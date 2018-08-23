#include "binary.h"
#include "opEx.h"
binary::binary(std::string s): std::string(s) { }
binary::binary(const char* s): std::string(s) { }
binary::binary(std::string::const_iterator first, std::string::const_iterator last):
	std::string(first,last) { }
bool binary::checkSign(bool o1, bool o2) const{
  if(!o1){
    if(o2)
      return true;
    return false;
  }
  if(o2)
    return false;
  return true;
}
bool binary::isNeg() const{
  return front() == '1' ? true : false;
}
void binary::popZeroFront(){
  int i = 0;
  while((*this)[i] == '0')
    ++i;
  std::string::const_iterator cit = begin()+i;
  erase(begin(),cit);
}
void binary::pushZeroBack(int length){
  int i = 0;
  while(i<length){
    this->append("0");
    i++;
  }
}
void binary::conj(){
  front() = isNeg() ? '0' : '1';
}
void binary::complement(){
  unsigned int i = 0;
  for(;i<this->length(); ++i)
      (*this)[i] == '1' ? (*this)[i] = '0'
                        : (*this)[i] = '1';
}
void binary::setMant(const binary& exp, binary& mant) const{
  if(exp=="000000"){
    if(!isNeg()) mant.insert(0,"00");
    else mant.insert(0,"10");
  }else{
    if(!isNeg()) mant.insert(0,"01");
    else mant.insert(0,"11");
  }
}
void binary::shiftR(){
  replace(begin()+1,end(),begin(),end()-1);
  front() = '0';
}
void binary::shiftL(){
  replace(begin(),end()-1,begin()+1,end());
  back() = '0';
}
