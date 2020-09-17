// Author:Tyler Siwy
// Date: Feb 12, 2020
// Approach: Recursively check through each denomination, checking all of its
// possibilities, saving all sub results in a lookup table in order to save
// time. Then check the next smallest denomination and so on.
#include <iostream>
#include <vector>
using namespace std;
vector<int> coinTypes{50, 25, 10, 5, 1};
vector<vector<int>> values(7490, vector<int>(5, -1));

int calculate(int num, int curDenom);

int main() {
  int num = 0;
  while (cin >> num && cin)
    cout << calculate(num, 0) << endl;
  return 0;
}

int calculate(int num, int curDenom) {
  if (num == 0)
    return 1;
  if (curDenom == 4)
    return 1;
  if (values[num][curDenom] != -1)
    return values[num][curDenom];
  int total = 0;
  for (int i = 0; i <= num / coinTypes[curDenom]; i++)
    total += calculate(num - coinTypes[curDenom] * i, curDenom + 1);
  values[num][curDenom] = total;
  return total;
}
