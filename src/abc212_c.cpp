#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;

int main() {

  int n, m;
  cin >> n >> m;

  vector<int> A(n);
  for (auto &&a : A) {
    cin >> a;
  }
  vector<int> B(m);
  for (auto &&b : B) {
    cin >> b;
  }

  // 配列をソート
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());
  int smaller = min(n, m);
  int bigger = max(n, m);
  vector<int> target(smaller);
  vector<int> an_target(bigger);
  if (smaller == n) {
    target = A;
    an_target = B;
  } else {
    target = B;
    an_target = A;
  }
  int ans = pow(10, 9);
  for (int i = 0; i < smaller; i++) {
    int x;
    x = target[i];
    // 二分探索による計算
    int upper =
        lower_bound(an_target.begin(), an_target.end(), x) - an_target.begin();
    ans = min(ans, abs(x - an_target[upper]));
    if (upper - 1 >= 0) {
      ans = min(ans, abs(x - an_target[upper - 1]));
    }
  }
  cout << ans << "\n";
  return 0;
}