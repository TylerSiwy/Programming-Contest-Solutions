// Author: Tyler Siwy
// Date: Jan 9, 2020
// Approach: Create a lookup table of all notes and their finger presses, along
// with an array of finger totals, and a list of previously held notes to
// compare again which gets updated on each iteration.
#include <iostream>
using namespace std;
#include <map>
#include <vector>

map<char, vector<int>> lookup;
vector<int> fPress(10);
bool isIn(int target, vector<int> input);
void fillLookup();
void countPresses(vector<int> currNote, vector<int> previousNote);
void outputPresses();

int main() {
  fillLookup();
  char previousNote = 'z', currNote;
  int t;
  string input = "";
  cin >> t;
  cin.ignore();
  for (int j = 0; j < t; j++) {
    getline(cin, input);
    for (unsigned int i = 0; i < input.length(); i++) {
      currNote = input.at(i);
      countPresses(lookup[currNote], lookup[previousNote]);
      previousNote = currNote;
    }
    outputPresses();
    previousNote = 'z';
  }
  return 0;
}

void countPresses(vector<int> currNote, vector<int> previousNote) {
  if (currNote != previousNote) {
    for (unsigned int i = 0; i < currNote.size(); i++) {
      if (!isIn(currNote.at(i), previousNote)) {
        fPress[currNote.at(i) - 1]++;
      }
    }
  }
}

void outputPresses() {
  for (unsigned int i = 0; i < fPress.size(); i++) {
    cout << fPress.at(i);
    if (i != fPress.size() - 1)
      cout << " ";
  }
  cout << endl;
  fPress.clear();
  fPress.resize(10);
}

// Search in a vector for an int
bool isIn(int target, vector<int> input) {
  for (int unsigned i = 0; i < input.size(); i++) {
    if (target == input.at(i)) {
      return true;
    }
  }
  return false;
}

void fillLookup() {
  lookup['c'] = vector<int>{2, 3, 4, 7, 8, 9, 10};
  lookup['d'] = vector<int>{2, 3, 4, 7, 8, 9};
  lookup['e'] = vector<int>{2, 3, 4, 7, 8};
  lookup['f'] = vector<int>{2, 3, 4, 7};
  lookup['g'] = vector<int>{2, 3, 4};
  lookup['a'] = vector<int>{2, 3};
  lookup['b'] = vector<int>{2};
  lookup['C'] = vector<int>{3};
  lookup['D'] = vector<int>{1, 2, 3, 4, 7, 8, 9};
  lookup['E'] = vector<int>{1, 2, 3, 4, 7, 8};
  lookup['F'] = vector<int>{1, 2, 3, 4, 7};
  lookup['G'] = vector<int>{1, 2, 3, 4};
  lookup['A'] = vector<int>{1, 2, 3};
  lookup['B'] = vector<int>{1, 2};
  lookup['z'] = vector<int>{0};
}
