// Author: Tyler Siwy
// Date: Feb 5, 2020
// Approach: Add input values to a vector, only adding zeros if they are the
// last number in the list. Then output them in the same order.

#include <iostream>
using namespace std;
#include <vector>

int main() {
  int numValues = 0;
  while (cin >> numValues && cin) {
    vector<int> values;
    if (numValues == 0)
      break;
    for (int i = 0; i < numValues; i++) {
      int num;
      cin >> num;
      if (num != 0)
        values.push_back(num);
    }
    if (values.size() > 0) {
      for (unsigned int i = 0; i < values.size(); i++) {
        cout << values.at(i);
        if (i != values.size() - 1)
          cout << " ";
      }
    } else
      cout << 0;
    cout << endl;
  }
  return 0;
}
