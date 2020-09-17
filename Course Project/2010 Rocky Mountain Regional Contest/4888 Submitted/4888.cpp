#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool checkCars(int t1I, const vector<int> &t1, int t2I, const vector<int> &t2,
               int oI, const vector<int> &order, vector<vector<int>> &values);
void fillVec(int numCars, vector<int> &t);

int main() {
  int t1Q, t2Q;
  while (true) {
    cin >> t1Q >> t2Q;
    vector<int> t1, t2;
    if (t1Q == t2Q && t1Q == 0)
      break;
    t1.reserve(t1Q);
    t2.reserve(t2Q);
    fillVec(t1Q, t1);
    fillVec(t2Q, t2);
    vector<int> order;
    order.reserve(t1Q + t2Q);
    // Get all the cars off of the line.
    fillVec(t1Q + t2Q, order);
    vector<vector<int>> values(t1Q + 1, vector<int>(t2Q + 1, -1));
    // Recursively check each case, use dynnamic programming to save results
    if (checkCars(0, t1, 0, t2, 0, order, values))
      cout << "possible" << endl;
    else
      cout << "not possible" << endl;
  }
  return 0;
}

// t1I, t2I, oI are the indices of our current location within the vectors
bool checkCars(int t1I, const vector<int> &t1, int t2I, const vector<int> &t2,
               int oI, const vector<int> &order, vector<vector<int>> &values) {
  if (oI == order.size())
    return true;

  // Check if this combination has already been processed.
  if (values[t1I][t2I] != -1)
    return values[t1I][t2I];

  if (t1I < t1.size() && t1.at(t1I) == order.at(oI)) {
    if (checkCars(t1I + 1, t1, t2I, t2, oI + 1, order, values)) {
      values[t1I][t2I] = 1;
      return true;
    }
  }

  if (t2I < t2.size() && t2.at(t2I) == order.at(oI)) {
    if (checkCars(t1I, t1, t2I + 1, t2, oI + 1, order, values)) {
      values[t1I][t2I] = 1;
      return true;
    }
  }

  values[t1I][t2I] = 0;
  return false;
}

void fillVec(int numCars, vector<int> &t) {
  for (int i = 0; i < numCars; i++) {
    int c;
    cin >> c;
    t.push_back(c);
  }
}
