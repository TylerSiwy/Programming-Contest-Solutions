// Author: Tyler Siwy
// Date: Feb 13, 2020
// Approach: Used the n^2 longest increasing subsequence algorithm, backtracking
// for each case
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
  int cases;
  cin >> cases;
  cin.ignore();
  cin.ignore();
  for (int i = 0; i < cases; i++) {
    vector<int> targets;
    while (true) {
      string line;
      getline(cin, line);
      if (line == "")
        break;
      targets.push_back(stoi(line));
    }
    vector<pair<int, int>> maxV(targets.size());
    int bEver = 0; // Best for all cases, global best
    for (unsigned int j = 0; j < targets.size(); j++) {
      int best = 1; // Best for the current case
      maxV.at(j).first = 1;
      maxV.at(j).second = j;
      for (int k = j - 1; k >= 0; k--) {
        if (targets.at(j) > targets.at(k) && maxV.at(k).first >= best) {
          maxV.at(j).first = maxV.at(k).first + 1;
          maxV.at(j).second = k; // Index of it's prev best
        }
        if (best < maxV.at(j).first)
          best = maxV.at(j).first;
      }
      if (maxV.at(bEver).first < best)
        bEver = j;
    }
    vector<int> vals(maxV.at(bEver).first);
    for (int x = 0; true; x++) {
      vals.at(x) = targets.at(bEver);
      if (bEver == maxV.at(bEver).second)
        break;
      bEver = maxV.at(bEver).second;
    }
    cout << "Max hits: " << vals.size() << endl;
    for (int w = vals.size() - 1; w >= 0; w--)
      cout << vals.at(w) << endl;
    if (i < cases - 1)
      cout << endl;
  }
  return 0;
}
