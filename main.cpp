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
  twosComp x = -3, y = 327 , z = 2;
  cout << y*x << endl;
}
/*sigMag x = 32, y =65 , z = 2;
  cout << x+y << endl;
  x = 32; y= 32767;
  try { cout << x+y << endl; }
  catch(ofEx) { cout << "overflow" << endl; }
  x = 0; y= 0;
  cout << x+y << endl;
  x = 0; y= 31;
  cout << x+y << endl;
  x = 31; y= 0;
  cout << x+y << endl;
  x = 32; y= -32;
  cout << x+y << endl;
  x = 32; y= -3;
  cout << x+y << endl;
  x = 32; y= -33;
  cout << x+y << endl;
  x = 32; y= -32767;
  cout << x+y << endl;
  x = 32; y= -32;
  cout << x+y << endl;
  x = -32; y= 3;
  cout << x+y << endl;
  x = -32; y= 33;
  cout << x+y << endl;
  x = -32; y= 32;
  cout << x+y << endl;
  x = -32; y= 32767;
  cout << x+y << endl;
  x = -32; y= -3;
  cout << x+y << endl;
  x = -32; y= -32;
  cout << x+y << endl;
  x = -32; y= -32767;
  try { cout << x+y << endl; }
  catch(ofEx) { cout << "overflow" << endl; }
  */
