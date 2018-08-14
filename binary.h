#ifndef BINARY_H
#define BINARY_H
#include <iostream>
#include <string>
class binary: public std::string {
public:
  binary(std::string ="");
  binary(const char*);
  //binary(const binary&);
  binary(std::string::const_iterator,std::string::const_iterator);
  //binary getBin() const;
  bool checkSign(bool,bool) const;
  bool isNeg() const;
  void popZeroFront();
  void pushZeroBack(int);
  void complement();
  void append(char);
  void append(const char*);
  void append(std::string);
  void shiftR();
  void shiftL();
  void setMant(const binary&, binary&) const;
  /*virtual binary& operator--();
  virtual binary& operator++();*/
};
#endif // BINARY_H
