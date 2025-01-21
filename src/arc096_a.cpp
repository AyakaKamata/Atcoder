#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
#define fore(i, a) for (auto &i : a)
#define all(x) (x).begin(), (x).end()
#pragma GCC optimize("-O3")

using namespace std;
using ll = long long;
using i128 = __int128_t;

const ll INF = 1LL << 60;
template <class T> inline bool chmin(T &a, T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
template <class T> inline bool chmax(T &a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

int main() {
  int a, b, c, x, y;
  cin >> a >> b >> c >> x >> y;
  ll cst = INF;
  int max_xy = max(x, y) * 2;
  rep(i, 0, max_xy + 1) {
    ll tmp = i * c + a * max(0, x - i / 2) + b * max(0, y - i / 2);
    chmin(cst, tmp);
  }
  cout << cst << endl;
  return 0;
}