#ifndef FLOATP_H
#define FLOATP_H
#include "binary.h"
class floatP: public binary{
protected:
  virtual void toBin(double) =0;
public:
  floatP(std::string ="0000000000000000");
  floatP(const char*);
  virtual double toVal() const =0;
};
#endif // FLOATP_H

