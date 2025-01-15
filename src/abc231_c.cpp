#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

using ll = long long;
using namespace std;

// 汎用的なバイナリサーチ関数
ll binary_search(ll ok, ll ng, function<bool(ll)> condition) {
  while (abs(ok - ng) > 1) {
    ll mid = (ok + ng) / 2;
    if (condition(mid)) {
      ok = mid;
    } else {
      ng = mid;
    }
  }
  return ok;
}

int main() {
  ll n, q;
  cin >> n >> q;

  vector<int> A(n);
  for (auto &&a : A) {
    cin >> a;
  }
  sort(A.begin(), A.end());

  for (ll i = 0; i < q; i++) {
    int x;
    cin >> x;

    // 条件関数: A[mid] >= x を満たす最小の index を探す
    auto condition = [&](ll mid) { return A[mid] >= x; };

    // バイナリサーチで条件を満たす最小の index を探索
    ll idx = binary_search(n, -1, condition);

    // n - idx が答え（条件を満たす要素の個数）
    cout << n - idx << endl;
  }

  return 0;
}
