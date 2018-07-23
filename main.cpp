#include <iostream>
#include "binary.h"
#include "integer.h"
#include "sigMag.h"
#include "twosComp.h"
#include "floatP.h"
#include "float16.h"
#include "ofEx.h"
#include "ufEx.h"
#include "zeroEx.h"
#include <math.h>
using namespace std;

int main(){
  sigMag f = 32767;
  try {
    cout << f/2 << endl;
  }
  catch(ofEx){ cout << "overflow" << endl;}
  catch(zeroEx) {cout << "division per zero occurred" << endl; }
 }
