// Author: Tyler Siwy
// Date: Jan 28, 2020

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

bool isAttained(vector<int> values);

int main() {
  int quantity = 0, caseNo = 0, ssInt = 0, initial = 0;
  string input;
  while (cin >> quantity && cin) {
    // Case by case setup
    caseNo++;
    if (quantity == 0)
      break;
    vector<int> values;
    cin.ignore();
    getline(cin, input);
    stringstream ss(input);
    while (ss >> ssInt) {
      values.push_back(ssInt);
    }

    // Begin processing the case
    cout << "Case " << caseNo << ": ";
    for (int i = 0; i <= 1000; i++) { // Max 1000 iterations allowed before fail
      if (isAttained(values)) {
        cout << i << " iterations" << endl;
        break;
      }
      initial = values.at(0);       // Save initial value of first element
      int temp = values.size() - 1; // Used to check if its the wrap-around case
      for (int j = 0; j < quantity; j++) {
        if (j != temp)
          values.at(j) = abs(values.at(j) - values.at(j + 1));
        else
          values.at(j) = abs(values.at(j) - initial);
      }
      if (i == 1000)
        cout << "not attained" << endl;
    }
  }
  return 0;
}

// Checks if the condition for current input is attained (all items eqiuivalent)
bool isAttained(vector<int> values) {
  for (unsigned int i = 0; i < values.size(); i++) {
    if (values.at(i) != values.at((i - 1) % values.size()))
      return false;
  }
  return true;
}
