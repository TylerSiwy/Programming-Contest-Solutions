// Author: Tyler Siwy
// Date: March 10,2020
// Approach: Set up graph in following order, source to clubs, clubs to people,
// people to party's. Where the people party's edges are 1-1. The run maximum
// flow on the graph. Use the maximum flow result to check all nodes at people
// for edges which have flow, this gives us the people and the party's which
// they represent.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Edge;
typedef list<Edge>::iterator EdgeIter;

struct Edge {
  int to;
  int cap;
  int flow;
  bool is_real;
  EdgeIter partner;

  Edge(int t, int c, bool real = true)
      : to(t), cap(c), flow(0), is_real(real){};

  int residual() const { return cap - flow; }
};

struct Graph {
  list<Edge> *nbr;
  int num_nodes;
  Graph(int n) : num_nodes(n) { nbr = new list<Edge>[num_nodes]; }

  ~Graph() { delete[] nbr; }

  // note: this routine adds an edge to the graph with the specified capacity,
  // as well as a residual edge.  There is no check on duplicate edge, so it
  // is possible to add multiple edges (and residual edges) between two
  // vertices
  void add_edge(int u, int v, int cap) {
    nbr[u].push_front(Edge(v, cap));
    nbr[v].push_front(Edge(u, 0, false));
    nbr[v].begin()->partner = nbr[u].begin();
    nbr[u].begin()->partner = nbr[v].begin();
  }
};

void push_path(Graph &G, int s, int t, const vector<EdgeIter> &path, int flow) {
  for (int i = 0; s != t; i++) {
    if (path[i]->is_real) {
      path[i]->flow += flow;
      path[i]->partner->cap += flow;
    } else {
      path[i]->cap -= flow;
      path[i]->partner->flow -= flow;
    }
    s = path[i]->to;
  }
}

// the path is stored in a peculiar way for efficiency: path[i] is the
// i-th edge taken in the path.
int augmenting_path(const Graph &G, int s, int t, vector<EdgeIter> &path,
                    vector<bool> &visited, int step = 0) {
  if (s == t) {
    return -1;
  }
  for (EdgeIter it = G.nbr[s].begin(); it != G.nbr[s].end(); ++it) {
    int v = it->to;
    if (it->residual() > 0 && !visited[v]) {
      path[step] = it;
      visited[v] = true;
      int flow = augmenting_path(G, v, t, path, visited, step + 1);
      if (flow == -1) {
        return it->residual();
      } else if (flow > 0) {
        return min(flow, it->residual());
      }
    }
  }
  return 0;
}

// note that the graph is modified
int network_flow(Graph &G, int s, int t) {
  vector<bool> visited(G.num_nodes);
  vector<EdgeIter> path(G.num_nodes);
  int flow = 0, f;

  do {
    fill(visited.begin(), visited.end(), false);
    if ((f = augmenting_path(G, s, t, path, visited)) > 0) {
      push_path(G, s, t, path, f);
      flow += f;
    }
  } while (f > 0);

  return flow;
}

struct Person {
  string name;
  string party;
  vector<string> clubs;
};

int main() {
  int t;
  cin >> t;
  cin.ignore();
  cin.ignore();
  for (int h = 0; h < t; h++) {
    int index = 1;
    if (h > 0)
      cout << endl;
    vector<Person> input;
    input.reserve(1000);
    map<string, int> people;
    map<string, int> parties;
    map<string, int> clubs;
    map<int, string> reverseClub;
    while (true) {
      string line;
      getline(cin, line);
      if (line == "")
        break;
      stringstream ss(line);
      Person p;
      ss >> p.name;
      string temp;
      ss >> temp;
      p.party = temp;
      while (ss >> temp) {
        p.clubs.push_back(temp);
      }
      input.push_back(p);
      people[p.name] = index++;
      if (!parties.count(p.party)) {
        parties[p.party] = index++;
      }
      // Save clubs
      for (unsigned int i = 0; i < p.clubs.size(); i++) {
        if (!clubs.count(p.clubs.at(i))) {
          reverseClub[index] = p.clubs.at(i);
          clubs[p.clubs.at(i)] = index++;
        }
      }
    }
    // Create 1-1 relation between parties and people
    Graph G(index + 1);
    for (unsigned int i = 0; i < input.size(); i++) {
      G.add_edge(parties[input.at(i).party], people[input.at(i).name], 1);
      for (unsigned int j = 0; j < input.at(i).clubs.size(); j++) {
        G.add_edge(people[input.at(i).name], clubs[input.at(i).clubs.at(j)], 1);
      }
    }
    // Connect source
    for (auto p : parties)
      G.add_edge(0, p.second, (clubs.size() - 1) / 2);
    // Connect sink
    for (auto c : clubs)
      G.add_edge(c.second, index, 1);

    int flow = network_flow(G, 0, index);
    if (flow == clubs.size()) {
      for (auto p : people) {
        for (auto n : G.nbr[p.second]) {
          if (n.is_real && n.flow) {
            cout << p.first << " " << reverseClub[n.to] << endl;
          }
        }
      }
    } else {
      cout << "Impossible." << endl;
    }
  }
  return 0;
}
