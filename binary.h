#ifndef BINARY_H
#define BINARY_H
#include <iostream>
#include <string>
/*peche' non va incapsulata in un'altra classe come nested class? perche'
 * altrimenti floatP non puo' derivare da niente */
class binary: public std::string {
public:
  binary(std::string ="");
  binary(const char*);
  binary(const binary&);
  binary getBin() const;
  void setBin(const std::string&);
  bool isNeg() const;
  void popZeroFront();
  void pushZeroBack(int);
  binary complement() const;
  void append(char);
  void append(const char*);
  void append(std::string);
  binary& operator++(int);
};
#endif // BINARY_H
