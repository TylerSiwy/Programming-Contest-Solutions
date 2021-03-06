// Author: Tyler Siwy
// Date: Jan 20, 2020
// Approach: Use a unionfind to find the neighbours and neighbours neighbours
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class UnionFind {
  struct UF {
    int p;
    int rank;
  };

public:
  UnionFind(int n) { // constructor
    howMany = n;
    uf = new UF[howMany];
    for (int i = 0; i < howMany; i++) {
      uf[i].p = i;
      uf[i].rank = 0;
    }
  }

  ~UnionFind() { delete[] uf; }

  int find(int x) { return find(uf, x); } // for client use

  bool merge(int x, int y) {
    int res1, res2;
    res1 = find(uf, x);
    res2 = find(uf, y);
    if (res1 != res2) {
      if (uf[res1].rank > uf[res2].rank) {
        uf[res2].p = res1;
      } else {
        uf[res1].p = res2;
        if (uf[res1].rank == uf[res2].rank) {
          uf[res2].rank++;
        }
      }
      return true;
    }
    return false;
  }

private:
  int howMany;
  UF *uf;

  int find(UF uf[], int x) { // recursive funcion for internal use
    if (uf[x].p != x) {
      uf[x].p = find(uf, uf[x].p);
    }
    return uf[x].p;
  }
};

// union find/disjoint sets, operation is O(1)

int main() {
  int quantity = 0, sets = 0; // quantity, number of input sets
  int c1 = 0, c2 = 0;         // values
  int successes = 0, failures = 0;
  char type; // query or connection
  cin >> sets;
  for (int i = 0; i < sets; i++) {
    if (i > 0)
      cout << endl;
    cin >> quantity;
    cin.ignore();
    UnionFind uf(quantity);
    while (true) {
      string input;
      getline(cin, input);
      if (input == "")
        break;
      istringstream s(input);
      s >> type >> c1 >> c2;
      if (type == 'c')
        uf.merge(c1 - 1, c2 - 1);
      else if (type == 'q') {
        if (uf.find(c1 - 1) == uf.find(c2 - 1))
          successes++;
        else
          failures++;
      }
    }
    cout << successes << "," << failures << endl;
    successes = 0;
    failures = 0;
  }
  return 0;
}
