// Author: Tyler Siwy
// Date: Feb 9, 2020
// Approach: Split the input up by commas, then check if it is a range or if it
// by itself. If it is a range, add all numbers of the range including the upper
// bounds to a vector of int values (0 or 1), which decides which pages to
// print.
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void addPage(int pageNo, vector<int> &pages);

int main() {
  int pageCount = 0;
  while (cin >> pageCount && cin) {
    if (pageCount == 0)
      break;
    vector<int> pages(pageCount, 0);
    cin.ignore();
    string rawStr;
    getline(cin, rawStr);
    istringstream iss(rawStr);
    vector<string> unprocessed;
    string s;
    while (getline(iss, s, ',')) {
      unprocessed.push_back(s);
    }
    for (auto c : unprocessed) {
      int min = -1, max = -1;
      string sMin, sMax;
      bool split = false;
      for (unsigned int i = 0; i < c.length(); i++) {
        if (!split && c[i] != '-')
          sMin += c[i];
        else if (split && c[i] != '-')
          sMax += c[i];
        else
          split = true;
      }
      min = stoi(sMin);
      if (split) {
        max = stoi(sMax);
        if (min > max)
          continue;
        for (int j = min; j <= max; j++)
          addPage(j, pages);
      } else
        addPage(min, pages);
    }
    int total = 0;
    for (unsigned int i = 0; i < pages.size(); i++) {
      if (pages.at(i) == 1)
        total++;
    }
    cout << total << endl;
  }
  return 0;
}

void addPage(int pageNo, vector<int> &pages) {
  if (pageNo <= pages.size() && pages.at(pageNo - 1) == 0)
    pages.at(pageNo - 1) = 1;
}
