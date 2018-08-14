#include "floatP.h"
floatP::floatP(std::string s): binary(s) { }
floatP::floatP(const char* s): binary(s) { }
floatP::floatP(std::string::const_iterator first,std::string::const_iterator last):
  binary(first, last) { }

