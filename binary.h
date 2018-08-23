#ifndef BINARY_H
#define BINARY_H
#include <string>
class binary: public std::string {
public:
  binary(std::string ="");
  binary(const char*);
  binary(std::string::const_iterator,std::string::const_iterator);
  static bool checkSign(bool,bool);
  bool isNeg() const;
  void popZeroFront();
  void pushZeroBack(int);
  void complement();
  void shiftR();
  void shiftL();
  void conj();
  void setMant(const binary&, binary&) const;
  virtual binary& operator+(const binary&) =0;
  virtual binary& operator-(const binary&) =0;
  virtual binary& operator*(const binary&) =0;
  virtual binary& operator/(const binary&) =0;
};
#endif // BINARY_H
