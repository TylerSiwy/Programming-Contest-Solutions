// Author:Tyler Siwy
// Date: Feb 26, 2020
// Approach: Use minimum spanning tree to store the graph then count the rails
// and roads depending on the weight of each edge of the graph

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
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

  int find(UF uf[], int x) { // for internal use
    if (uf[x].p != x) {
      uf[x].p = find(uf, uf[x].p);
    }
    return uf[x].p;
  }
};

class Edge {

public:
  Edge(int i = -1, int j = -1, double weight = 0) {
    v1 = i;
    v2 = j;
    w = weight;
  }
  bool operator<(const Edge &e) const { return w < e.w; }

  int v1, v2; /* two endpoints of edge                */
  int w;      /* weight, can be double instead of int */
};

double mst(int n, int m, Edge elist[], int index[], int &size) {
  UnionFind uf(n);

  sort(elist, elist + m);

  double w = 0.0;
  size = 0;
  for (int i = 0; i < m && size < n - 1; i++) {
    int c1 = uf.find(elist[i].v1);
    int c2 = uf.find(elist[i].v2);
    if (c1 != c2) {
      index[size++] = i;
      w += elist[i].w;
      uf.merge(c1, c2);
    }
  }

  return w;
}

int main() {
  int noCases = 0;
  cin >> noCases;
  for (int a = 1; a <= noCases; a++) {
    int cities, threshold;
    cin >> cities >> threshold;
    double *x = new double[cities];
    double *y = new double[cities];
    int *index = new int[cities];
    for (int j = 0; j < cities; j++)
      cin >> x[j] >> y[j];
    Edge *elist = new Edge[cities * cities];
    int k = 0;
    for (int i = 0; i < cities; i++)
      for (int j = i + 1; j < cities; j++)
        elist[k++] =
            Edge(i, j,
                 (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
    int t; // number of edges in the mst
    mst(cities, k, elist, index, t);
    double rails = 0, roads = 0, states = 1;
    for (int i = 0; i < t; i++) {
      if (elist[index[i]].w > threshold * threshold) {
        states++;
        rails += sqrt(elist[index[i]].w);
      } else {
        roads += sqrt(elist[index[i]].w);
      }
    }
    cout << fixed << setprecision(0) << "Case #" << a << ": " << states << " "
         << roads << " " << rails << endl;
  }
  return 0;
}
