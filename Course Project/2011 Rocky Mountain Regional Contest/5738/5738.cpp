#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Node {
  set<Node *> connections;
  void connect(Node &x) { connections.insert(&x); }
  bool target = false;
  int cost = -1;
  int count = 0;
};

// Checks the bounds conditions for setting up nodes
bool validLoc(int row, int col, int m, int n, vector<string> &temp);

int main() {
  int M, N, mod;
  int caseNo = 0;
  while (cin >> M >> N >> mod) {
    if (!M && M == N && M == mod)
      break;
    caseNo++;
    vector<string> temp;
    for (int m = 0; m < M; m++) {
      string line;
      cin >> line;
      temp.push_back(line);
    }
    int sR, sC, tR, tC;
    char direction;
    cin >> sR >> sC >> tR >> tC >> direction;
    // Row, Col, Directions

    vector<vector<vector<Node>>> graph(
        1000, vector<vector<Node>>(1000, vector<Node>(4)));
    for (int row = sR; row < M; row++) {
      for (int col = sC; col < N; col++) {
        if (temp[row][col] != '*') {
          for (int dir = 0; dir < 4; dir++) {
            if (row == sR && col == sC)
              graph[row][col][dir].target = true;

            graph[row][col][dir].connect(
                graph[row][col][(dir + 1) % 4]); // Connect Right
            graph[row][col][dir].connect(
                graph[row][col][(dir + 3) % 4]); // Connect Left
            switch (dir) {
            case 0:
              if (validLoc(row - 1, col, M, N, temp)) { // Up
                graph[row - 1][col][dir].connect(graph[row][col][dir]);
              }
              break;
            case 1:
              if (validLoc(row, col + 1, M, N, temp)) { // Right
                graph[row][col + 1][dir].connect(graph[row][col][dir]);
              }
              break;
            case 2:
              if (validLoc(row + 1, col, M, N, temp)) { // Down
                graph[row + 1][col][dir].connect(graph[row][col][dir]);
              }
              break;
            case 3:
              if (validLoc(row, col - 1, M, N, temp)) { // Left
                graph[row][col - 1][dir].connect(graph[row][col][dir]);
              }
              break;
            }
          }
        }
      }
    }
    queue<Node *> edges;
    for (int i = 0; i < 4; i++) {
      edges.push(&graph[tR][tC][i]);
      edges.front()->cost = 0;
      edges.front()->count = 1;
    }

    int answer = 0;
    while (!edges.empty()) {
      for (auto n : edges.front()->connections) {
        // If the node has not been visited before, cost < 0, process it
        if (n->cost < 0) {
          n->cost = edges.front()->cost + 1;
          n->count = edges.front()->count;
          edges.push(n);
        } else if (n->cost == edges.front()->cost) {
          n->count += edges.front()->count;
        }
      }
      // If we find the target, add it's count
      if (edges.front()->target) {
        answer += edges.front()->count;
      }
      // Remove the edge we just looked at
      edges.pop();
    }
    cout << "Case " << caseNo << ": " << mod << " ";
    (answer > 0 ? cout << answer % mod : cout << "-1");
    if (caseNo > 0)
      cout << endl;
  }
  return 0;
}

// Checks the bounds conditions for setting up nodes
bool validLoc(int row, int col, int m, int n, vector<string> &temp) {
  if (col >= 0 && col < n && row >= 0 && row < m)
    if (temp[row][col] != '#')
      return true;
  return false;
}
