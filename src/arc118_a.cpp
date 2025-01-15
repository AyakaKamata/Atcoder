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
ll f(ll x, ll t) { return floor((x * (100.0 + t) / 100.0)); }

int main() {
  ll t, n;
  cin >> t >> n;
  ll ok = 0; // 1円から探索するため
  ll ng = 100 * n;

  while (abs(ok - ng) > 1) {
    ll mid = (ok + ng) / 2;
    if (f(mid, t) - mid < n) {
      ok = mid;
    } else {
      ng = mid;
    }
  }
  cout << f(ok, t) + 1 << endl;
  return 0;
}
