#ifndef INTEGER_H
#define INTEGER_H
#include "binary.h"
class integer: public binary {
protected:
  virtual void toBin(int) =0;
  static char buildStr(int&, int);
public:
  integer(std::string ="0000000000000000");
  integer(const char*);
  virtual int toVal() const =0;
 };
#endif // INTEGER_H
