// Author: Tyler Siwy
// Date: January 8, 2019
// I used the approach of parsing the string, adding all alpha characters to a
// string until I encounter a non alpha, then I process the current string,
// count the keyword occurances, and reset the string. Then continue parsing the
// sentence

#include <iostream>
#include <string>
#include <utility> // std::pair
#include <vector>
using namespace std;

vector<string> keywords;
vector<pair<string, int>> excuses;
int highestCount = 0;
int excuseSet = 0;

int occurances(string keyword, string sentence);
bool isWord(int target, int tLen, string sentence);
int keywordsInSentence(string sentence);
void printExcuses();
string toLower(string str);

int main() {
  int K = 0, E = 0;
  // Get sizes of arrays from the buffer
  while (cin >> K >> E && cin) {
    excuseSet++;
    keywords.clear();
    excuses.clear();
    // Get all keywords from the buffer
    for (int i = 0; i < K; i++) {
      string temp;
      cin >> temp;
      keywords.push_back(temp);
    }
    cin.ignore();

    // Get all excuses from the buffer
    for (int i = 0; i < E; i++) {
      string temp;
      getline(cin, temp);
      // Calculate the keyword number here
      int t = keywordsInSentence(temp);
      if (t > highestCount)
        highestCount = t;
      excuses.push_back(make_pair(temp, t));
    }
    printExcuses();
  }
  return 0;
}

// Find the occurances for each excuse
int keywordsInSentence(string sentence) {
  int total = 0;
  for (int i = 0; i < keywords.size(); i++) {
    total += occurances(keywords.at(i), sentence);
  }
  return total;
}

// Finds the number of occurances of a keyword within a string
int occurances(string keyword, string sentence) {
  int occurances = 0;
  string curWord;
  sentence += " ";
  for (int i = 0; i < sentence.size(); i++) {
    if (isalpha(sentence[i])) {
      curWord += sentence[i];
    } else {

      if (toLower(curWord) == keyword)
        occurances++;
      curWord = "";
    }
  }
  return occurances;
}

// Prints out the final answer
void printExcuses() {
  vector<int> indices;
  cout << "Excuse Set #" << excuseSet << endl;
  for (int i = 0; i < excuses.size(); i++) {
    if (excuses.at(i).second == highestCount)
      cout << excuses.at(i).first << endl;
  }
  cout << endl;
  highestCount = 0;
}

// Changes a string to all lowercase
string toLower(string str) {
  for (int i = 0; i < str.length(); i++) {
    str[i] = tolower(str[i]);
  }
  return str;
}
