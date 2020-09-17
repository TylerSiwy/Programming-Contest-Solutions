// Author: Tyler Siwy
// Date: Jan 9, 2020
// Approach: Padded the entire board with periods to simplify the checking
// process, then interated through the board and counted above, below, and to
// the sides of each space. Saved that to a vector and then outputted the
// results.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> board;
vector<string> result;

void padBoard(int length);
void saveBoard(int m, int n);
int checkAboveBelow(int x, int y);
int checkSides(int x, int y);
bool isMine(int x, int y);
void outputResult(int n, int fieldNumber);

int main() {
  int n, m, fieldNumber = 1;
  string line;
  while (cin >> n >> m && cin) {
    cin.ignore();
    if (n > 0 && m > 0) {
      saveBoard(m, n);
      // Check each space's neighbours to see how many mines are surrounding it.
      for (int j = 1; j <= m; j++) {
        string currentLine = "";
        for (int i = 1; i <= n; i++) {
          int total = 0;
          if (!isMine(i, j)) {
            total += checkAboveBelow(j, i);
            total += checkSides(j, i);
            currentLine += to_string(total);
          } else {
            // It is a mine
            currentLine += '*';
          }
        }
        result.push_back(currentLine);
      }
      board.clear();
      outputResult(n, fieldNumber);
      fieldNumber++;
      result.clear();
      cout << endl;
    }
  }
  return 0;
}

// Outputs the contents of the result
void outputResult(int n, int fieldNumber) {
  // Have to iterate by column first since we have stored things in a vector of
  // strings
  cout << "Field #" << fieldNumber << ":" << endl;
  for (int j = 0; j < n; j++) {
    for (unsigned int i = 0; i < result.size(); i++) {
      cout << result.at(i).at(j);
    }
    cout << endl;
  }
}

// Returns true if char x,y location is a mine
bool isMine(int x, int y) {
  if (board.at(x).at(y) == '*')
    return true;
  else
    return false;
}

// Check spaces on either side of coordinate to see if they are mines
int checkSides(int x, int y) {
  int total = 0;
  if (board.at(y)[x - 1] == '*')
    total++;
  if (board.at(y)[x + 1] == '*')
    total++;
  return total;
}

// Check three spaces above, and below, and tally the mines.
int checkAboveBelow(int x, int y) {
  int total = 0;
  for (int i = 0; i < 3; i++) {
    if (board.at(y - 1)[x - 1 + i] == '*')
      total++;
    if (board.at(y + 1)[x - 1 + i] == '*')
      total++;
  }
  return total;
}

// Saves and pads the outside of the board for easy comparison
void saveBoard(int m, int n) {
  string line;
  for (int i = 0; i <= n; i++) {
    if (i == 0) {
      padBoard(m);
    } else {
      getline(cin, line);
      line = "." + line + ".";
      board.push_back(line);
    }
  }
  padBoard(m);
}

// Adds a string of periods to the board to check, to pad it.
void padBoard(int length) {
  string target = "";
  for (int i = 0; i < length + 2; i++) {
    target += ".";
  }
  board.push_back(target);
}
