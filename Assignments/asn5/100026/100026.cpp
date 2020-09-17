// Author: Tyler Siwy
// Date: Feb 6, 2020
// Approach: Save all values into a vector of structs. Then sort them based on
// their time/fine costs to determine what would be the best choice, using a
// greedy approach.
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
struct job {
  int fine;
  int time;
  int order;
};

int main() {
  int numCases;
  cin >> numCases;
  for (int i = 0; i < numCases; i++) {
    vector<job> jobs;
    int lines;
    cin >> lines;
    for (int j = 0; j < lines; j++) {
      job temp;
      temp.order = j + 1;
      cin >> temp.time >> temp.fine;
      jobs.push_back(temp);
    }

    sort(jobs.begin(), jobs.end(),
         [](job a, job b) { return a.fine * b.time > a.time * b.fine; });
    for (unsigned int j = 0; j < jobs.size(); j++) {
      cout << jobs[j].order;
      if (j != jobs.size() - 1)
        cout << " ";
    }

    cout << endl;
    if (i < numCases - 1)
      cout << endl;
  }
  return 0;
}
