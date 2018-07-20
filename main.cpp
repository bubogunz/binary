#include <iostream>
#include "binary.h"
#include "integer.h"
#include "sigMag.h"
#include "twosComp.h"
#include "floatP.h"
#include "float16.h"
#include <math.h>
using namespace std;

int main(){
  float16 z = pow(2,-5);
  cout << z << endl;
  float16 f = -0.00056894564654;
  cout << f << endl;
  cout << z/f << endl;
}
