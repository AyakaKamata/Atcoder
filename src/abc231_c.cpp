#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> A(n);
  for (auto &&a : A) {
    cin >> a;
  }
  sort(A.begin(), A.end());
  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;
    cout << n - (lower_bound(A.begin(), A.end(), x) - A.begin()) << "\n";
  }
  return 0;
}