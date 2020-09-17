// Author:Tyler Siwy
// Date: Feb 25, 2020
// Approach: Created a four dimensional array to store the grid, making nodes
// for each color and direction combination of each node. Iterated the array,
// connecting notes to their possible neighbours and setting the target node.
// Then performed a breadth first search on the resulting nodes to locate the
// target, updating the count of each node as we search through the graph

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
  set<Node *> connections;
  void connect(Node &x) { connections.insert(&x); }
  bool target = false;
  int count = -1;
};

// Checks the bounds conditions for setting up nodes
bool validLoc(int row, int col, int m, int n, vector<string> &temp);

int main() {
  int M, N; // M == Rows, N == Cols
  int caseNo = 0;
  while (cin >> M >> N) {
    if (!M && M == N)
      break;
    if (caseNo > 0)
      cout << endl;
    vector<string> temp;
    for (int m = 0; m < M; m++) {
      string line;
      cin >> line;
      temp.push_back(line);
    }
    int sR, sC;
    // Row, Col, Directions, Colours
    Node graph[25][25][4][5];
    for (int row = 0; row < M; row++) {
      for (int col = 0; col < N; col++) {
        if (temp[row][col] != '#') {
          for (int dir = 0; dir < 4; dir++) {
            for (int clr = 0; clr < 5; clr++) {
              if (temp[row][col] == 'S') {
                sR = row; // Start row
                sC = col; // Start column
              } else if (temp[row][col] == 'T' && clr == 0) {
                graph[row][col][dir][clr].target = true;
              }
              graph[row][col][dir][clr].connect(
                  graph[row][col][(dir + 1) % 4][clr]); // Connect Right
              graph[row][col][dir][clr].connect(
                  graph[row][col][(dir + 3) % 4][clr]); // Connect Left
              switch (dir) {
              case 0:
                if (validLoc(row - 1, col, M, N, temp)) { // Up
                  graph[row][col][dir][clr].connect(
                      graph[row - 1][col][dir][(clr + 1) % 5]);
                }
                break;
              case 1:
                if (validLoc(row, col + 1, M, N, temp)) { // Right
                  graph[row][col][dir][clr].connect(
                      graph[row][col + 1][dir][(clr + 1) % 5]);
                }
                break;
              case 2:
                if (validLoc(row + 1, col, M, N, temp)) { // Down
                  graph[row][col][dir][clr].connect(
                      graph[row + 1][col][dir][(clr + 1) % 5]);
                }
                break;
              case 3:
                if (validLoc(row, col - 1, M, N, temp)) { // Left
                  graph[row][col][dir][clr].connect(
                      graph[row][col - 1][dir][(clr + 1) % 5]);
                }
                break;
              }
            }
          }
        }
      }
    }
    queue<Node *> edges;
    edges.push(&graph[sR][sC][0][0]);
    edges.front()->count = 0;
    int count = 0;
    while (!edges.empty()) {
      for (auto c : edges.front()->connections) {
        // If the node has not been visited before, count < 0, process it
        if (c->count < 0) {
          c->count = edges.front()->count + 1;
          edges.push(c);
        }
      }

      // If we find the target, set the count to it's count for output
      if (edges.front()->target) {
        count = edges.front()->count; // Add 1 to account for final node
        break;
      }
      // Remove the node we just looked at
      edges.pop();
    }
    caseNo++;
    cout << "Case #" << caseNo << endl;
    (count > 0 ? cout << "minimum time = " << count << " sec" << endl
               : cout << "destination not reachable" << endl);
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
