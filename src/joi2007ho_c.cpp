#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
#define fore(i, a) for (auto &i : a)
#define all(x) (x).begin(), (x).end()
#pragma GCC optimize("-O3")

using namespace std;
using ll = long long;
using i128 = __int128_t;

const int INFI = INT_MAX / 2;
const ll INFL = 1LL << 60;
template <class T> bool chmin(T &a, T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
template <class T> bool chmax(T &a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

/*--------------------------------------------------------
       \0w0/ Keep Calm!
                                        OwOkaomoji
                                    ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/

int main() {
  int n;
  cin >> n;
  vector<int> x(n), y(n);
  vector<vector<bool>> isin(5001, vector<bool>(5001, false));
  rep(i, 0, n) {
    cin >> x[i] >> y[i];
    isin[x[i]][y[i]] = true;
  }
  auto check = [&](int p, int q) -> bool {
    if (p < 0 || p > 5000 || q < 0 || q > 5000) {
      return false;
    } else {
      return isin[p][q];
    }
  };
  ll res = 0;
  rep(i, 0, n - 2) rep(j, i + 1, n - 1) {
    int dx = x[j] - x[i];
    int dy = y[j] - y[i];
    ll sq = dx * dx * 1LL + dy * dy * 1LL;

    int x3 = x[i] - dy;
    int y3 = y[i] + dx;
    int x4 = x3 + dx;
    int y4 = y3 + dy;
    if (check(x3, y3) && check(x4, y4)) {
      chmax(res, sq);
    }
    x3 = x[i] + dy;
    y3 = y[i] - dx;
    x4 = x3 + dx;
    y4 = y3 + dy;
    if (check(x3, y3) && check(x4, y4)) {
      chmax(res, sq);
    }
  }
  cout << res << endl;
  return 0;
}