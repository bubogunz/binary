#ifndef INTEGER_H
#define INTEGER_H
#include "binary.h"
class integer: public binary {
protected:
  static std::string buildStr(int&, int);
  virtual std::string toBin(int) const =0;
  virtual int toVal() const =0;
public:
  integer(std::string ="");
  integer(const char*);
  integer(std::string::const_iterator, std::string::const_iterator);
  virtual integer& operator++() =0;
  virtual integer& operator--() =0;
 };
#endif // INTEGER_H
