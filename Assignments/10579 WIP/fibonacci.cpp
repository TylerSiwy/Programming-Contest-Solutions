#include <iostream>
#include <vector>
using namespace std;

int64_t fib(int64_t n);

int main() {
  int64_t f;
  while (cin >> f && cin) {
    cout << "fib(" << f << "):" << fib(f) << endl;
  }
  return 0;
}

// Function can only computed up to n=92 due to overflow, use of external
// libraries or a class for storing larger values as strings would be required
// for larger values of n.
int64_t fib(int64_t n) {
  static vector<int64_t> computed(1000, -1);
  if (n <= 1)
    return n;
  if (computed[n - 1] != -1)
    return computed[n - 1];
  int64_t temp = fib(n - 1) + fib(n - 2);
  computed[n - 1] = temp;
  return temp;
}
