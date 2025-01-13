#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> A(m);
  for (auto &&a : A) {
    cin >> a;
  }

  long ans = 0;
  for (int i = 0; i < n; i++) {
    cout << A[upper_bound(A.begin(), A.end(), i) - A.begin()]-i-1 << "\n";
  }

  return 0;
}
