#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;

ll custom_binary_search(ll ok, ll ng, function<bool(ll)> condition) {
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

using i128 = __int128_t;


int main() {
    ll N, M;
    cin >> N >> M;

    vector<ll> P(N);
    for (auto &p : P) cin >> p;

    // 二分探索による最大 x の計算
    auto condition = [&](ll mid) {
        i128 sm = 0;
        for (ll p : P) {
            ll t = (mid / p + 1) / 2;
            sm += (i128)t * t * p;
            if (sm > M) return false;
        }
        return sm <= M;
    };

    ll ok = custom_binary_search(0, M + 1, condition);

    // 最大個数の計算
    ll cnt = 0;
    for (ll p : P) {
        ll t = (ok / p + 1) / 2;
        cnt += t;
        M -= t * t * p;
    }

    // 余った金額で追加購入
    cnt += M / (ok + 1);

    cout << cnt << endl;

    return 0;
}