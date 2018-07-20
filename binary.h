#ifndef BINARY_H
#define BINARY_H
#include <iostream>
#include <string>
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
