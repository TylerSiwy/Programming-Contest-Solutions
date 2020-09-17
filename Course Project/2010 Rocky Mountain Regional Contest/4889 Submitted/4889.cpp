// Author: Tyler Siwy
// Date: Feb 16, 2020
// Approach: Save values in a vector and sort them in ascending order, then
// perform checks to see which mail type they are, else, return not mailable
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string type(double length, double height, double thickness);

int main() {
  double val;
  vector<string> answers;
  while (true) {
    vector<double> vals;
    for (int i = 0; i < 3; i++) {
      cin >> val;
      vals.push_back(val);
    }
    // Ending condition l=h=t=0
    if (vals[0] == 0 && vals[1] == 0 && vals[2] == 0)
      break;
    sort(vals.begin(), vals.end());
    answers.push_back(type(vals[0], vals[1], vals[2]));
  }
  for (unsigned int i = 0; i < answers.size(); i++) {
    cout << answers[i];
    if (i < answers.size() - 1)
      cout << endl;
  }
  return 0;
}

string type(double thickness, double height, double length) {
  // Minimum check for letter
  if (length >= 125 && height >= 90 && thickness >= 0.25) {
    if (length <= 290 && height <= 155 && thickness <= 7)
      return "letter";
    else if (length <= 380 && height <= 300 && thickness <= 50)
      return "packet";
    else if (((2 * (height + thickness)) + length) <= 2100)
      return "parcel";
  }
  return "not mailable";
}
