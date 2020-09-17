// Author: Tyler Siwy
// Date: Jan 28, 2020
// Approach: Keep a vector of pairs of the day a stock is on and then sort them
// by their prices. That way we can easily output the results in ascending and
// descending order.
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

void kLowHigh(vector<pair<int, int>> input, int k1, int k2);

int main() {
  int Case = 1;
  while (true) {
    vector<pair<int, int>> days;

    int noDays = 0, k1 = 0, k2 = 0;
    string input;
    cin >> noDays >> k1 >> k2;
    if (noDays == 0)
      break;
    cin.ignore();
    getline(cin, input);
    stringstream s(input);
    int price = 0, index = 1;
    while (s >> price) {
      days.push_back(make_pair(price, index));
      index++;
    }
    cout << "Case " << Case << endl;
    kLowHigh(days, k1, k2);
    Case++;
  }
  return 0;
}

// Outputs the k1 lowest and k2 highest values in the vector
void kLowHigh(vector<pair<int, int>> input, int k1, int k2) {
  vector<pair<int, int>> min;
  vector<pair<int, int>> max;
  sort(input.begin(), input.end());

  for (int i = 0; i < k1; i++)
    min.push_back(input.at(i));
  sort(min.begin(), min.end(),
       [](pair<int, int> x, pair<int, int> y) { return x.second < y.second; });
  for (auto c : min)
    cout << c.second << " ";
  cout << endl;

  reverse(input.begin(), input.end());
  for (int i = k2; i > 0; i--) {
    max.push_back(input.at(k2 - i));
  }
  sort(max.begin(), max.end(),
       [](pair<int, int> x, pair<int, int> y) { return x.second > y.second; });
  for (auto c : max)
    cout << c.second << " ";
  cout << endl;
}
