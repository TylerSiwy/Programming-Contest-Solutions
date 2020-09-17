// Author: Tyler Siwy
// Date: March 7, 2020
// Approach: Create the graph with 100 nodes for each city, one for each tank
// size, connecting each node to its above and below node with that city's
// price. Then connect each node to it's neighbouring city with a cost of zero.
// Then use dijkstra's to search for the shortest path, but have it modified to
// mark all nodes that are outside of the fuel capacity to be aready used so
// that the search doesn't use those nodes.
#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int to;
  int weight; // can be double or other numeric type
  Edge(int t, int w) : to(t), weight(w) {}
};

typedef vector<Edge>::iterator EdgeIter;

struct Graph {
  vector<Edge> *nbr;
  int num_nodes;
  Graph(int n) : num_nodes(n) { nbr = new vector<Edge>[num_nodes]; }

  ~Graph() { delete[] nbr; }

  // note: There is no check on duplicate edge, so it is possible to
  // add multiple edges between two vertices
  //
  // If this is an undirected graph, be sure to add an edge both
  // ways
  void add_edge(int u, int v, int weight) { nbr[u].push_back(Edge(v, weight)); }
};

/* assume that D and P have been allocated */
void dijkstra(const Graph &G, int src, vector<int> &D, vector<int> &P,
              int gas) {
  typedef pair<int, int> pii;

  int n = G.num_nodes;
  vector<bool> used(n, false);
  priority_queue<pii, vector<pii>, greater<pii>> fringe;

  // Set all nodes which are too large of cost so that they aren't used.
  for (int i = 0; i < G.num_nodes; i += 101) {
    for (int j = gas + 1; j < 101; j++) {
      used[i + j] = true;
    }
  }
  D.resize(n);
  P.resize(n);
  fill(D.begin(), D.end(), -1);
  fill(P.begin(), P.end(), -1);

  D[src] = 0;
  fringe.push(make_pair(D[src], src));

  while (!fringe.empty()) {
    pii next = fringe.top();
    fringe.pop();
    int u = next.second;
    if (used[u])
      continue;
    used[u] = true;

    for (EdgeIter it = G.nbr[u].begin(); it != G.nbr[u].end(); ++it) {
      int v = it->to;
      int weight = it->weight + next.first;
      if (used[v])
        continue;
      if (D[v] == -1 || weight < D[v]) {
        D[v] = weight;
        P[v] = u;
        fringe.push(make_pair(D[v], v));
      }
    }
  }
}

int get_path(int v, const vector<int> &P, vector<int> &path) {
  path.clear();
  path.push_back(v);
  while (P[v] != -1) {
    v = P[v];
    path.push_back(v);
  }
  reverse(path.begin(), path.end());
  return path.size();
}

int main(void) {
  int n, m;
  cin >> n >> m;
  Graph G(n * 101);
  // I is city, city 0 being 0-100, city 2 being 101-201, 202-303 etc.
  for (int i = 0; i < n; i++) {
    int price;
    cin >> price;
    for (int j = 0; j < 100; j++) {
      // Add edges with their price between nodes of the two connected cities
      G.add_edge(i * 101 + j, i * 101 + j + 1, price);
    }
  }
  int u, v, d;
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> d;
    for (int j = d; j < 101; j++) {
      // Create bi-directional 0-cost edges between each city
      G.add_edge(u * 101 + j, v * 101 + j - d, 0);
      G.add_edge(v * 101 + j, u * 101 + j - d, 0);
    }
  }
  int q;
  cin >> q;
  // Perform the search for each case
  for (int k = 0; k < q; k++) {
    int gas, s, e;
    cin >> gas >> s >> e;
    vector<int> D, P; // D is distance, P is path
    dijkstra(G, s * 101, D, P, gas);
    cout << (D[e * 101] >= 0 ? to_string(D[e * 101]) : "impossible") << endl;
  }
  return 0;
}
