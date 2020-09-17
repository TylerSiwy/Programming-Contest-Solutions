#include <iostream>
#include <vector>
// Author: Tyler Siwy
// Date: January 7, 2019
// Question 305

// This function finds the solution to a set of size k
int findM(int k);

int main() {
  // k is the number of good guys and the number of bad guys
  int answers[12];
  for (int i = 1; i < 14; i++) {
    answers[i - 1] = findM(i);
  }
  int k = 0;
  while (true) {
    std::cin >> k;
    if (k == 0)
      break;
    std::cout << answers[k - 1] << "\n";
  }
  return 0;
}

// This function finds the solution to a set of size k
int findM(int k) {
  bool found = false;
  // Start at k+1 since we don't need to check the good guys
  int m = k;
  int current;
  while (!found) {
    m++;
    current = 0;
    int total = 2 * k;
    for (int i = 0; i < k; i++) {
      // Update our current player
      current = (current - 1 + m) % total;
      if (current < k)
        break;
      // Subtract one guy since he has been killed
      total--;
    }
    // If we have successfully removed k bad guys, end the loop
    if (total == k)
      break;
  }
  return m;
}
