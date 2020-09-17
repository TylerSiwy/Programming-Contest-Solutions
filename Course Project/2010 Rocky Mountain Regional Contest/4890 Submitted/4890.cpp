// Author:Tyler Siwy
// Date: Feb 17, 2020
// Approach: Use std find to find the index of the first t, then recursively use
// find again on the next spot. For each value computed, save it in a table
// instead of recomputing each time. Once our current has decremented to 0
// return the value we are at as a result.
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

map<int, string> hardOrdinalVals{
    {1, "first"},       {2, "second"},       {3, "third"},
    {4, "fourth"},      {5, "fifth"},        {6, "sixth"},
    {7, "seventh"},     {8, "eighth"},       {9, "ninth"},
    {10, "tenth"},      {11, "eleventh"},    {12, "twelfth"},
    {13, "thirteenth"}, {14, "fourteenth"},  {15, "fifteenth"},
    {16, "sixteenth"},  {17, "seventeenth"}, {18, "eighteenth"},
    {19, "nineteenth"}, {20, "twentieth"},   {30, "thirtieth"},
    {40, "fortieth"},   {50, "fiftieth"},    {60, "sixtieth"},
    {70, "seventieth"}, {80, "eightieth"},   {90, "ninetieth"}};

map<int, string> cardinalOnes{
    {1, "one"},        {2, "two"},       {3, "three"},    {4, "four"},
    {5, "five"},       {6, "six"},       {7, "seven"},    {8, "eight"},
    {9, "nine"},       {10, "ten"},      {11, "eleven"},  {12, "twelve"},
    {13, "thirteen"},  {14, "fourteen"}, {15, "fifteen"}, {16, "sixteen"},
    {17, "seventeen"}, {18, "eighteen"}, {19, "nineteen"}};

map<int, string> cardinalTens{
    {20, "twenty"},   {30, "thirty"},    {40, "forty"},  {50, "fifty"},
    {60, "sixty"},    {70, "seventy"},   {80, "eighty"}, {90, "ninety"},
    {100, "hundred"}, {1000, "thousand"}};

string cardToOrd(string val);
string cardinal(string val);
int recurse(string &aronson, int target);
vector<int> computed(100001, -1);

int main() {
  int in;
  string aronson = "*tisthe";
  while (cin >> in && cin) {
    if (in == 0)
      break;
    cout << recurse(aronson, in) << endl; // Make it 0-relative
  }
  return 0;
}

int recurse(string &aronson, int target) {
  if (target == 0) {
    return 0;
  }
  if (computed[target] != -1)
    return computed[target];
  int newLoc = aronson.find_first_of('t', recurse(aronson, target - 1) + 1);
  aronson += cardinal(to_string(newLoc));
  computed.at(target) = newLoc;
  return newLoc;
}

string cardinal(string val) {
  string num;
  vector<char> vec(7, '0');
  int j = 6;
  // Copy value into a 7 length vector so we can check each spot, R to L
  for (int i = val.length(); i > 0; i--) {
    vec.at(j) = val.at(i - 1);
    j--;
  }
  // If our first value is 1, we're at the max edge case, return onemillion
  if (vec.at(0) == '1')
    return "onemillion";

  bool thousands = false;
  // hundred thousand slot
  if (vec.at(1) != '0') {
    num += cardinalOnes[vec.at(1) - '0'] + "hundred";
    thousands = true;
  }

  if (vec.at(2) == '1') { // Number is 10-19 thousands, use cardinal ones, no
                          // need to add ones
    string temp;
    temp += vec.at(2);
    temp += vec.at(2 + 1);
    num += cardinalOnes[stoi(temp)];
    thousands = true;
  } else if (vec.at(2) != '0') { // Number is 20-99 thousands so use cardinal
                                 // ones and then add our one thousands
    num += cardinalTens[(vec.at(2) - '0') * 10];
    thousands = true;
    if (vec.at(3) != '0') { // If our one thousands are not empty, add them
      num += cardinalOnes[(vec.at(3) - '0')];
      thousands = true;
    }
  } else if (vec.at(3) != '0') { // vec[2] == '0', add ones only
    num += cardinalOnes[(vec.at(3) - '0')];
    thousands = true;
  }

  // If we have used one of the thousands slots, add the suffix
  if (thousands)
    num += "thousand";

  // Hundred ones slot
  if (vec.at(4) != '0')
    num += cardinalOnes[vec.at(4) - '0'] + "hundred";

  bool ordinal = false;
  if (vec.at(5) == '1') { // Grab both index 5 and 6 if it's a "teen" number
    string temp;
    temp += vec.at(5);
    temp += vec.at(5 + 1);
    num += hardOrdinalVals[stoi(temp)];
    ordinal = true;
  } else if (vec.at(5) != '0') { // If it's >19 use regular tens, add the ones
    num += cardinalTens[(vec.at(5) - '0') * 10];
  }
  if (vec.at(6) != '0' &&
      vec.at(5) != '1') { // add ordinal ones, already in ordinal
    ordinal = true;
    num += hardOrdinalVals[(vec.at(6) - '0')];
  }

  if (!ordinal)
    num = cardToOrd(num);

  return num;
}

string cardToOrd(string val) {
  if (val[val.length() - 1] == 'y') {
    val[val.length() - 1] = 'i';
    val += "eth";
  } else
    val += "th";
  return val;
}
