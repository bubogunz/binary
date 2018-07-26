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
  sigMag x = "1101101110111000", y="0000000010101010";
  cout << x << ' ' << y << endl;
  cout << x/y << endl;
}
