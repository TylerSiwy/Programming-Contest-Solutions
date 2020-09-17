// Author: Tyler Siwy
// Date: Jan 21, 2020
// Approach: Using a multiset to easily access the front and back of an ordered
// set, removing them on each iteration. Ensured that the payout would be large
// enough using int64_t.
#include <iostream>
#include <set>
#include <string>
using namespace std;

multiset<int> receipts;

int main() {
  int days = 0;
  while (cin >> days && cin) {
    int64_t payout = 0;
    if (days == 0)
      break;
    for (int i = 0; i < days; i++) {
      int numIns = 0;
      cin >> numIns;
      for (int j = 0; j < numIns; j++) {
        int val = 0;
        cin >> val;
        receipts.insert(val);
      }
      multiset<int>::iterator it1, it2;
      it1 = --receipts.end();
      it2 = receipts.begin();
      payout += abs(*it1 - *it2);
      receipts.erase(it1);
      receipts.erase(it2);
    }
    receipts.clear();
    cout << payout << endl;
  }
  return 0;
}
