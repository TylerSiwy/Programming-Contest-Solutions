// Author: Tyler Siwy
// Date: Jan 30, 2020
// Approach: Starting at the first house, set our distance to the houses
// location plus 2 distance, then try it again until you have used all the
// available wifi hotspots. Then binary search on D until we find the smallest
// possible D that works for the layout of houses.

#include <iomanip>
#include <iostream>
#include <set>
using namespace std;

int AP(double d, set<int> &houses);

int main() {
  int cases = 0;
  cin >> cases;
  for (int i = 0; i < cases; i++) {
    set<int> houses;
    int points = 0, hNum = 0;
    cin >> points >> hNum;
    for (int j = 0; j < hNum; j++) {
      int houseNumber = 0;
      cin >> houseNumber;
      houses.insert(houseNumber);
    }
    double high, low, mid;
    high = *(--houses.end());
    low = 0;
    mid = low + ((high - low) / 2);
    while (high - low > 0.01) {
      mid = low + ((high - low) / 2);
      if (AP(mid, houses) >= points) {
        low = mid;
      } else {
        high = mid;
      }
    }
    cout << fixed << setprecision(1) << mid << endl;
  }
  return 0;
}

// Returns the number of access points for a particular street size d
int AP(double d, set<int> &houses) {
  double range = *houses.begin() + (2 * d);
  int count = 0;
  for (auto h : houses) {
    if (h > range) {
      range = h + (2 * d);
      count++;
    }
  }
  return count;
}
