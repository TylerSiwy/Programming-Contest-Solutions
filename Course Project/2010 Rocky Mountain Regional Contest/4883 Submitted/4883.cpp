// Author: Tyler Siwy
// Date: Feb 8, 2020
// Approach: Determine number of climbers based on cases provided in pdf.

#include <iostream>
using namespace std;

int climbers(int pHeight, int rLen, int max);

int main() {
  int pitches;
  while (cin >> pitches && cin) {
    if (pitches == 0)
      break;
    int totalPitch = 0, max = 0;
    for (int i = 0; i < pitches; i++) {
      int temp;
      cin >> temp;
      totalPitch += temp;
      if (temp > max)
        max = temp;
    }
    cout << climbers(totalPitch, 50, max) << " "
         << climbers(totalPitch, 60, max) << " "
         << climbers(totalPitch, 70, max) << endl;
  }
  return 0;
}

int climbers(int pHeight, int rLen, int max) {
  // Descent Check, combined an extra check to save space
  if ((pHeight * 2 > rLen) || rLen < max)
    return 0;
  // Climb Check
  int count = rLen / max + 1;
  if (count < 2)
    return 0;
  return count;
}
