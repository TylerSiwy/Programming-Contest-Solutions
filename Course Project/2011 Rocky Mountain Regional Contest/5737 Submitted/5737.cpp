// Author: Tyler Siwy
// Date: Feb 8, 2020
// Approach: Use int64_t to avoid overflow. Check if the case has already been
// solved in a lookup table. Then recursively check each case, saving the result
// if we haven't already calculated the step.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int64_t choosePill(int whole, int half,
                   vector<vector<int64_t>> &computedValues);

int main() {
  int value;
  vector<vector<int64_t>> computedValues(31, vector<int64_t>(31, -1));
  while (cin >> value && cin) {
    if (value == 0)
      break;
    else {
      cout << choosePill(value, 0, computedValues) << endl;
    }
  }
  return 0;
}

int64_t choosePill(int whole, int half,
                   vector<vector<int64_t>> &computedValues) {
  int64_t count = 0;
  if (computedValues.at(whole).at(half) != -1)
    return computedValues.at(whole).at(half);
  if (half > 0)
    count += choosePill(whole, half - 1, computedValues);
  if (whole > 0)
    count += choosePill(whole - 1, half + 1, computedValues);
  if (whole + half == 1)
    return 1;
  computedValues.at(whole).at(half) = count;
  return count;
}
