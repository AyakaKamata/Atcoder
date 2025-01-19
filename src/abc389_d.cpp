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

const ll INF = 1LL << 60;

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
  ll r;
  cin >> r;
  auto in = [&](ll a, ll b) {
    return (2 * a + 1) * (2 * a + 1) + (2 * b + 1) * (2 * b + 1) <= 4 * r * r;
  };
  ll cnt = 0;
  ll up = r - 1;
  ll res = (r - 1) * 4 + 1;
  for (ll x = 1; in(x, 1); x++) {
    while (!in(x, up))
      --up;
    cnt += up;
  }
  res += cnt * 4;
  cout << res << endl;
}