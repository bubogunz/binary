#include <iostream>
#include "binary.h"
#include "integer.h"
#include "sigMag.h"
#include "twosComp.h"
#include "floatP.h"
#include "float16.h"
#include "opEx.h"
#include <math.h>
using namespace std;

int main(){
  twosComp x = -32766, y = -3, z = -32750;
  cout << x << ' ' << y <</* ' ' << z << */endl;
  cout << x+y<< endl;
}
