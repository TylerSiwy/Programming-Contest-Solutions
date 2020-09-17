#include <iostream>
#include <vector>
using namespace std;

// Global variables aren't ideal, but in this case it is cheaper than passing it
// through function calls.
vector<int64_t> computed(100, -1);

int64_t fib(int64_t n);

int main() {
  unsigned long long int f;
  computed[0] = 1;
  computed[1] = 1;
  vector<int64_t> inputs;
  while (cin >> f && cin) {
    inputs.push_back(f);
  }
  for (auto i : inputs)
    cout << "fib(" << i << "):" << fib(i) << endl;
  for (auto c : computed)
    cout << c << " ";
  cout << endl;
  return 0;
}

int64_t fib(int64_t n) {
  // Base case is already in precomputed so no need for a basecase check
  if (computed[n - 1] != -1) {
    return computed[n - 1];
  }
  int64_t temp = fib(n - 1) + fib(n - 2);
  computed[n - 1] = temp;
  return temp;
}
