// Author: Tyler Siwy
// Date: Jan 30, 2020
// Approach:
// Determine if our current guess is correct by comparing it to each clue, if
// the number of correct/misplaced is the same as all the clues for the current
// case then we have an acceptable solution. Should we end up with more than one
// solution then we know that is indeterminate. If there are no solutions then
// we know that it is impossible.
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

bool isAnswer(string attempt, const vector<pair<string, string>> &guesses);

int main() {
  int cases = 0;
  cin >> cases;
  for (int i = 0; i < cases; i++) {
    string attempt = "";
    vector<pair<string, string>> guesses;
    int count = 0;
    string clue, code;
    int noGuesses = 0;
    cin >> noGuesses;
    for (int j = 0; j < noGuesses; j++) {
      cin >> code;
      cin >> clue;
      guesses.push_back(make_pair(code, clue));
    }
    string solution = "";
    for (int j = 0; j < 10000; j++) {
      attempt = "";
      if (j < 1000)
        attempt += "0";
      if (j < 100)
        attempt += "0";
      if (j < 10)
        attempt += "0";
      attempt += to_string(j);
      if (isAnswer(attempt, guesses)) {
        count++;
        solution = attempt;
      }
    }
    if (count > 1)
      cout << "indeterminate" << endl;
    else if (count == 1)
      cout << solution << endl;
    else
      cout << "impossible" << endl;
  }
  return 0;
}

// Determine if our current guess is correct by comparing it to each clue.
// Ensure that you erase checked letters to ensure we don't find the same
// character twice.
bool isAnswer(string attempt, const vector<pair<string, string>> &guesses) {
  unsigned int count = 0;
  for (auto g : guesses) {
    int c1 = g.second[0] - '0';
    int m1 = g.second[2] - '0';
    // Correct loop
    int c2 = 0;
    string temp = g.first;
    string temp2 = attempt;
    for (int i = 0; i < 4; i++) {
      if (temp[i] == temp2[i]) {
        c2++;
        temp[i] = '*'; // Replace checked chars so they aren't counted twice
        temp2[i] = '^';
      }
    }
    int m2 = 0;
    // Misplaced loop
    for (int i = 0; i < 4; i++) {
      int index = temp.find(temp2[i]);
      if (index >= 0) {
        m2++;
        temp[index] = '&';
      }
    }
    // If the clues are the same then increment our count of correct clues.
    if (c1 == c2 && m1 == m2)
      count++;
  }
  if (count == guesses.size())
    return true;
  return false;
}
