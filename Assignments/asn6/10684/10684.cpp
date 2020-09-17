// Author: Tyler Siwy
// Date: Feb 14, 2020
// Approach: Keep a running total and a max, then add our input to the running
// total and check if it exceeds the total or is less than zero.

#include <iostream>
using namespace std;

int main() {
  int length;
  while (cin >> length && cin) {
    if (!length)
      break;
    int max = 0;
    int streak = 0;
    for (int i = 0; i < length; i++) {
      int temp;
      cin >> temp;
      streak += temp;
      if (streak < 0)
        streak = 0;
      if (streak > max)
        max = streak;
    }
    if (max > 0)
      cout << "The maximum winning streak is " << max << "." << endl;
    else
      cout << "Losing streak." << endl;
  }
  return 0;
}
