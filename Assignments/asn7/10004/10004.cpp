// Author: Tyler Siwy
// Date: Feb 25, 2020
// Approach: Create a graph using a vector of structs then use breadth first
// search to check every node, ensuring they can be colored.

#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

struct Node {
  set<int> connections;
  int colour = 0; // 0 is unvisited
};

void connect(int a, int b, vector<Node> &nodes);
bool colour(vector<Node> &nodes);

int main() {
  int nodeNo, edges;
  while (true) {
    cin >> nodeNo;
    if (!nodeNo)
      break;
    vector<Node> nodes(nodeNo);

    cin >> edges;
    for (int i = 0; i < edges; i++) {
      int a, b;
      cin >> a >> b;
      connect(a, b, nodes);
    }
    cout << (colour(nodes) ? "BICOLORABLE." : "NOT BICOLORABLE.") << endl;
  }
  return 0;
}

void connect(int a, int b, vector<Node> &nodes) {
  nodes.at(a).connections.insert(b);
  nodes.at(b).connections.insert(a);
}

bool colour(vector<Node> &nodes) {
  queue<Node> q;
  nodes.at(0).colour = 1;
  q.push(nodes.at(0));
  while (!q.empty()) {
    for (auto n : q.front().connections) {
      if (nodes.at(n).colour) {
        if (nodes.at(n).colour == q.front().colour)
          return false;
        else
          continue;
      }
      (q.front().colour == 1 ? nodes.at(n).colour = 2 : nodes.at(n).colour = 1);
      if (nodes.at(n).colour)
        q.push(nodes.at(n));
    }
    q.pop();
  }
  return true;
}
