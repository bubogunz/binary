#include <iostream>
#include "binary.h"
#include "integer.h"
#include "sigMag.h"
#include "twosComp.h"
#include "floatP.h"
#include "float16.h"
#include "ofEx.h"
#include "ufEx.h"
#include <math.h>
using namespace std;

int main(){
  sigMag f = -16000;
  try {
    for(int i=0; i>=-10; --i)
      cout<<f*i<<endl;
  }
  catch(ofEx){ cout << "overflow" << endl;}
  //catch(...) {cout << "boh" << endl; }
 }
