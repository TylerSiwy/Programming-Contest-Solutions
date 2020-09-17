// Author: Tyler Siwy
// Date: Feb 8, 2020
// Approach: Grab the first letter of the first name, then use find_last_of to
// grab the last name, and append it using the rules provided in the pdf
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

string getUsername(int maxlen, const string name);
string goodChars(const string target, int length);
bool nameExists(const string username, const vector<string> &userNames);
void findAlternative(string username, int max, vector<string> &userNames);

int main() {
  int caseNo = 1;
  int names = 0, maxlen = 0;
  while (true) {
    cin >> names >> maxlen;
    if (names == 0 && maxlen == 0)
      break;
    vector<string> userNames;
    cin.ignore();
    for (int i = 0; i < names; i++) {
      string name = "";
      getline(cin, name);
      string username = getUsername(maxlen, name);
      if (nameExists(username, userNames))
        findAlternative(username, maxlen, userNames);
      else
        userNames.push_back(username);
    }
    cout << "Case " << caseNo << endl;
    caseNo++;
    for (auto c : userNames)
      cout << c << endl;
  }
  return 0;
}

// If the current username is taken, this func will find an alternative based on
// the rules provided
void findAlternative(string username, int max, vector<string> &userNames) {
  int i = 1;
  while (i < 100) {
    string temp = username;
    if (temp.length() >= max) {
      // Username is not small enough to start appending characters, remove
      // chars to make it fit depening on i-size
      if (i < 10)
        temp.pop_back();
      else {
        temp.pop_back();
        temp.pop_back();
      }
    } else if (temp.length() >= max - 1 && i >= 10)
      temp.pop_back();
    temp += to_string(i);
    if (!nameExists(temp, userNames) && temp.length() <= max) {
      userNames.push_back(temp);
      break;
    }
    i++;
  }
}

bool nameExists(const string username, const vector<string> &userNames) {
  for (auto c : userNames) {
    if (username == c)
      return true;
  }
  return false;
}

// Removes all non-alphanumerics from a string and .
string getUsername(int maxlen, const string name) {
  string last = "";
  string username = "";
  username = tolower(name[0]);
  for (int i = name.find_last_of(" ") + 1; i < name.length(); i++)
    last += tolower(name[i]);
  maxlen -= username.length();
  username += goodChars(last, maxlen);
  return username;
}

// Checks that all characters are from the accepted input types
string goodChars(const string target, int maxlen) {
  string val = "";
  int i = 0;
  while (val.length() < maxlen && i < target.length()) {
    // If input is good, append the char
    if (isalnum(target[i]))
      val += tolower(target[i]);
    i++;
  }
  return val;
}
