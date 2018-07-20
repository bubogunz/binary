#ifndef SIGMAG_H
#define SIGMAG_H
#include "integer.h"
#include <string> //include Qstring e sul .pro QT += core
class sigMag : public integer { //[-32767, +32767]
  static int min;
  static int max;
  void toBin(int);
public:
  sigMag(std::string ="0000000000000000");
  sigMag(const char*);
  sigMag(int);
  int toVal() const;
};
std::ostream& operator<<(std::ostream&, const sigMag&); //os.str() ritorna cio' che contiene lo stream sotto forma di stringa
#endif // SIGNUM_H
