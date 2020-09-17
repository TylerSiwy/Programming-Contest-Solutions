// Author: Tyler Siwy
// Date: January 9, 2019
// I chose to simply grab the country, then increment the counter, clear until
// the next new line character, and at the end, sort the vector
#include <algorithm> // std::sort
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

vector<pair<string, int>> results;
void addToCountryTotal(string country, int value);

int main() {
  int lines = 0;
  cin >> lines;
  string country;
  int loves;

  for (int i = 0; i < lines; i++) {
    string garbage;
    loves = 0;
    country = "";
    cin >> country;
    loves++;
    addToCountryTotal(country, loves);
    getline(cin, garbage);
  }
  std::sort(results.begin(), results.end());
  for (unsigned int i = 0; i < results.size(); i++) {
    cout << results.at(i).first << " " << results.at(i).second << endl;
  }
  return 0;
}

void addToCountryTotal(string country, int value) {
  bool newCountry = true;
  for (unsigned int i = 0; i < results.size(); i++) {
    if (results.at(i).first == country) {
      results.at(i).second += value;
      newCountry = false;
      break;
    }
  }
  if (newCountry == true)
    results.push_back(make_pair(country, value));
}
