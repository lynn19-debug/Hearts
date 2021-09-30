
#include <iostream>
#include <cassert>
#include <iomanip>
#include "Vector.h"


using namespace std;


int main(int argc, const char * argv[]) {

  
  
  Vector<int> intV;
  
  cout << "\nSquere Bracket Operator Setter and Getter Test:" << endl;
  cout << "(Retrieved using Getter) Vector[0] = " << intV[0] << " Before setter" << endl;
  intV[0] = 1;
  cout << "(Retrieved using Getter) Vector[0] = " << intV[0] << " After setter\n" << endl;
    assert( intV[0] == 1);
  
  cout << "Vector PushBack Test:" << endl;
  cout << "Size of Vector Before pushBack() = " << intV.size() << endl;
  cout << "Last value in Vector is = " << intV.back() << endl;
  cout << endl;
  cout << "pushBack(2)" << endl;
  cout << "pushBack(3)\n" << endl;
  intV.pushBack(2);
  intV.pushBack(3);
  cout << "Size of Vector Before pushBack() = " << intV.size() << endl;
  cout << "Last value in Vector is = " << intV.back() << endl;
    assert(intV.back() == 3 );
  
  cout << "\nVector Empty() Test:" << endl;\
  cout << "Expected empty(): False\n";
  string status;
  if ( intV.empty() == false)
    status = false;
  status = true;
  cout << "Actual: " << status << endl;
  assert(intV.empty() == false );
  

  cout << " \nVector popBack() Test:" << endl;
  cout << "Before popBack() -> Last value in vector is Vector[2] = " << intV.back() << endl;
  cout << left << setw(5) << "Size = " << intV.size() << endl;
    assert( intV.size() == 3 );
    assert (intV[2] == 3 );
    assert( intV.back() == 3 );
  intV.popBack();
 cout << "After popBack() -> Last value in vector is Vector[1] = " << intV.back() << endl;
  cout << left << setw(5) << "Size = " << intV.size() << endl;
    assert( intV.size() == 2);
    assert (intV[1] == 2 );
    assert(intV.back() == 2);
  intV.popBack();
  cout << "After popBack() -> Last value in vector is Vector[0] = " << intV.back() << endl;
  cout << left << setw(5) << "Size = " << intV.size() << endl;
    assert( intV.size() == 1);
    assert (intV[0] == 1 );
    assert(intV.back() == 1);
intV.popBack();
cout << "After popBack() -> Last value in vector is Vector[0] = " << intV.back() << endl;
cout << left << setw(5) << "Size = " << intV.size() << endl;
  assert( intV.size() == 0);
  assert(intV.back() == 0);
  //If intV[0] is called for assert it will create new value and increase siz by 1
  
  return 0;
}
