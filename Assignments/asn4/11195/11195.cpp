// Author: Tyler Siwy
// Date: Jan 28, 2020
// Approach: Try squares one by one, checking below, and both angles below to
// ensure that a queen can go there, then recursively continue through the board
// column by column until we have the correct number of queens.
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct coord {
  coord(int xIn, int yIn) {
    x = xIn;
    y = yIn;
  }
  int x;
  int y;
  bool operator==(const coord &a) { return x == a.x && y == a.y; };
};

bool check(int x, int y, int n);
void recurse(int row, int n, int &count, vector<coord> &invalid);
void set(int x, int y, int n, int val);

vector<int> cols;
vector<int> diagR;
vector<int> diagL;

int main() {
  int n = 0, caseNo = 1;
  while (cin >> n && cin) {
    // Setup variables, save bad squares
    int count = 0;
    if (n == 0)
      break;
    cols.resize(n, 0);
    diagR.resize(2 * n, 0);
    diagL.resize(2 * n, 0);
    vector<coord> invalid;
    for (int i = 0; i < n; i++) {
      string line = "";
      cin >> line;
      for (int j = 0; j < n; j++) {
        if (line.at(j) == '*')
          invalid.emplace_back(i, j);
      }
    }

    // Call recursive function to find all possible spots
    recurse(0, n, count, invalid);
    cout << "Case " << caseNo << ": " << count << endl;
    caseNo++;
  }
  return 0;
}

void recurse(int row, int n, int &count, vector<coord> &invalid) {
  // Increment through number of columns n
  for (int j = 0; j < n; j++) {
    // If number of coords placed is n, we have a solution, increment counter,
    // treat as a step back and continue
    if (check(row, j, n)) {
      continue;
    }
    // If invalid, go back up a level
    if (std::find(invalid.begin(), invalid.end(), coord(row, j)) !=
        invalid.end())
      continue;
    // Otherwise it is a valid space, so set the reference vectors
    set(row, j, n, 1);
    // If we have reached our final total, increment our counter for the total
    if (row == n - 1) {
      count++;
    }
    // Otherwise start the check on the next row
    recurse(row + 1, n, count, invalid);
    set(row, j, n, 0); // reset reference vectors on exit part of recursion
  }
}

bool check(int x, int y, int n) {
  // If it collides, return true, compare against current columns, diagonals
  // below to the right and to the left.
  if (cols[y] == 1 || diagR[x + y] == 1 || diagL[x - y + n] == 1) {
    return true;
  }
  return false;
}

void set(int x, int y, int n, int val) {
  cols[y] = val;
  diagR[x + y] = val;
  diagL[x - y + n] = val;
}
