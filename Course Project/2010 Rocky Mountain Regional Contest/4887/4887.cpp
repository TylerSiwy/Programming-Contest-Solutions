#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
using namespace std;

void numPossible(string t1, vector<pair<string, string>> &unplayed,
                 map<string, int> &points);
string place(int num);

int main() {
  while (true) {
    int t, m;
    cin >> t >> m;
    if (t == m && t == 0)
      break;
    vector<string> teams;
    teams.reserve(t);
    for (int i = 0; i < t; i++) {
      string team;
      cin >> team;
      teams.push_back(team);
    }
    map<string, int> points;
    for (auto t : teams) {
      points[t] = 0;
    }
    vector<pair<string, string>> unplayed;
    for (int i = 0; i < m; i++) {
      string t1, t2;
      int p1, p2;
      cin >> t1;
      for (int j = 0; j < 3; j++)
        cin.ignore();
      cin >> t2;
      t2.erase(t2.length() - 1);
      cin >> p1 >> p2;
      if (p1 == p2) {
        if (p1 == -1) {
          unplayed.push_back(make_pair(t1, t2));
        } else {
          points[t1] += 1;
          points[t2] += 1;
        }
      } else if (p1 > p2) {
        points[t1] += 3;
      } else {
        points[t2] += 3;
      }
    }
    for (auto u : unplayed) {
      cout << u.first << " vs " << u.second << endl;
    }
    for (auto c : points)
      cout << c.first << ":" << c.second << endl;
  }
  return 0;
}

void numPossible(string t1, vector<pair<string, string>> &unplayed,
                 map<string, int> &points) {
  map<string, int> possible = points;
  int high, low;
  for (auto g : unplayed) {
  }
  cout << "Team " << t1 << " can finish as high as " << place(high)
       << "place and as low as " << place(low) << "place.";
}

string place(int num) {
  switch (num) {
  case 1:
    cout << num << "st";
    break;
  case 2:
    cout << num << "nd";
    break;
  case 4:
    cout << num << "rd";
    break;
  default:
    cout << num << "th";
    break;
  }
}
