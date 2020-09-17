// Author: Tyler Siwy
// Date: January 8, 2019

#include <iostream>
using namespace std;

int main() {
  long x = 0, y = 0;
  while (cin >> x >> y && cin) {
    cout << abs(x - y) << endl;
  }
  return 0;
}
