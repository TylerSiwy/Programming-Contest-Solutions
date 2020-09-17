// Author: Tyler Siwy
// Date: Feb 12, 2020
// Approach: Save the intitial table and then calculate the costs of all paths
// then check each case as we iterate recursively through the 2d vector to find
// the answer
#include <iostream>
#include <vector>
using namespace std;

int costCalc(const int row, const int col, const int val,
             vector<vector<int>> &table);

void pathFinder(int row, int column, vector<vector<int>> &costs);
bool minIsTie(int a, int b, int c);

int main() {
  int row = 0, column = 0;
  while (cin >> row >> column && cin) {
    vector<vector<int>> table(row, vector<int>(column));
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < column; j++)
        cin >> table.at(i).at(j);
    }
    vector<vector<int>> costs(row, vector<int>(column));
    for (int i = 0; i < row; i++) {
      costs.at(i).at(column - 1) = table.at(i).at(column - 1);
    }

    for (int j = column - 2; j >= 0; j--) {
      for (int i = 0; i < row; i++) {
        costs.at(i).at(j) = costCalc(i, j, table.at(i).at(j), costs);
      }
    }
    pathFinder(0, 0, costs);
    cout << endl;
  }
  return 0;
}

void pathFinder(int row, int col, vector<vector<int>> &costs) {
  int cs = costs.size();
  int current = costs.at(row).at(col);
  if (col == 0) {
    for (int i = costs.size() - 1; i >= 0; i--) {
      if (costs.at(i).at(col) <= current) {
        current = costs.at(i).at(col);
        row = i;
      }
    }
    cout << row + 1;
  } else {
    int upR = (row - 1 + cs) % cs;
    int up = costs[upR][col];
    int straight = costs[row][col];
    int downR = (row + 1) % cs;
    int down = costs[downR][col];
    // If at top row
    cout << " ";
    int minimum = min(up, min(straight, down));
    if (row == 0) {
      if (straight == minimum) {
        cout << row + 1;
      } else if (down == minimum) {
        row = downR;
        cout << downR + 1;
      } else {
        row = upR;
        cout << upR + 1;
      }
      // If at bottom row
    } else if (row == costs.size() - 1) {

      if (down == minimum) {
        row = downR;
        cout << downR + 1;
      } else if (up == minimum) {
        row = upR;
        cout << upR + 1;
      } else {
        cout << row + 1;
      }
    } else {
      if (up == minimum) {
        row = upR;
        cout << upR + 1;
      } else if (straight == minimum) {
        cout << row + 1;
      } else {
        row = downR;
        cout << downR + 1;
      }
    }
  }
  if (col < costs.at(row).size() - 1) {
    pathFinder(row, col + 1, costs);
  }
  if (col == 0)
    cout << endl << current;
}

int costCalc(const int row, const int col, const int val,
             vector<vector<int>> &costs) {
  int cost, p1, p2;
  p1 = (row - 1 + costs.size()) % costs.size();
  p2 = ((row + 1) % costs.size());
  cost = min(costs[p1][col + 1], costs[row][col + 1]);
  cost = min(cost, costs[p2][col + 1]);
  cost += val;
  return cost;
}
