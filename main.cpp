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
  twosComp x = -32760, y="0000000010101010";
  //cout << x << ;
  for(int i=0; i<10; ++i)
    cout << --x << endl;
}
