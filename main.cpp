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
  float16 x = 98, y = 0.017;
  cout << x << endl << y << endl;
  cout << x/y << endl;
}
