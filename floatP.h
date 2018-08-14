#ifndef FLOATP_H
#define FLOATP_H
#include "binary.h"
class floatP: public binary{
public:
  floatP(std::string ="");
  floatP(std::string::const_iterator,std::string::const_iterator);
  floatP(const char*);
  virtual double toVal() const =0;
};
#endif // FLOATP_H

