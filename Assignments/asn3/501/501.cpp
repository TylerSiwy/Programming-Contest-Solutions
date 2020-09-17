// Author: Tyler Siwy
// Date: Jan 23, 2020
// Approach: I've used two heaps, one for all numbers larger than i, and a min
// heap for all numbers smaller than or equal to i. If the number being inserted
// is smaller than the top of the min heap, it gets put into the max heap, and
// the top of the max heap is shifted to the min heap. Else, we simply insert
// into the min heap. When we perform a get we return the top of the min heap
// and shift that value, which becomes the new top of the max heap.
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

void addToQueue(int input, priority_queue<int> &max,
                priority_queue<int, vector<int>, greater<int>> &min);
int get(priority_queue<int> &max,
        priority_queue<int, vector<int>, greater<int>> &min);

int main() {
  int numSets = 0;
  cin >> numSets;
  for (int i = 0; i < numSets; i++) {
    // Declaring variables
    // Top of this heap is the largest of the smaller numbers
    priority_queue<int> max;
    // Top of this heap is the smallest of the larger numbers
    priority_queue<int, vector<int>, greater<int>> min;
    int numElements = 0, numGetAt = 0;
    cin >> numElements;
    cin >> numGetAt;
    vector<int> elements;

    // Save our data for processing
    for (int j = 0; j < numElements; j++) {
      int temp;
      cin >> temp;
      elements.push_back(temp);
    }
    int iterator = 0;
    for (int j = 0; j < numGetAt; j++) {
      unsigned int getAt = 0;
      cin >> getAt;
      while (getAt > (min.size() + max.size())) {
        // Add until the sizes equal our get value
        addToQueue(elements.at(iterator), max, min);
        iterator++;
      }
      cout << get(max, min) << endl;
    }
    if (i < numSets - 1)
      cout << endl;
  }
  return 0;
}

int get(priority_queue<int> &max,
        priority_queue<int, vector<int>, greater<int>> &min) {
  max.push(min.top());
  min.pop();
  return max.top();
}

void addToQueue(int input, priority_queue<int> &max,
                priority_queue<int, vector<int>, greater<int>> &min) {
  if ((max.size() + min.size()) < 1) {
    min.push(input);
  } else if (input < min.top()) {
    max.push(input);
    min.push(max.top());
    max.pop();
  } else {
    min.push(input);
  }
}
