#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
#define fore(i, a) for (auto &i : a)
#define all(x) (x).begin(), (x).end()
#pragma GCC optimize("-O3")

using namespace std;
using ll = long long;
using i128 = __int128_t;
using pint = pair<int, int>;

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
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/
int max_this = 1000000;
int main() {
  int m;
  cin >> m;
  vector<int> x_m(m);
  vector<int> y_m(m);
  rep(i, 0, m) { cin >> x_m[i] >> y_m[i]; }
  int n;
  cin >> n;
  vector<int> x_n(n);
  vector<int> y_n(n);
  set<pint> isin;
  rep(i, 0, n) {
    cin >> x_n[i] >> y_n[i];
    isin.insert(pair(x_n[i], y_n[i]));
  }

  auto check = [&](int x, int y) -> bool {
    if (x < 0 || x >= max_this + 1 || y < 0 || y >= max_this + 1) {
      return false;
    }
    return isin.count(pair(x, y));
  };

  int dist_x = 0, dist_y = 0;
  rep(i, 0, n) {
    dist_x = x_n[i] - x_m[0];
    dist_y = y_n[i] - y_m[0];

    bool valid = true;
    rep(k, 0, m) {
      if (!check(x_m[k] + dist_x, y_m[k] + dist_y)) {
        valid = false;
        break;
      }
    }
    if (valid) {
      cout << dist_x << " " << dist_y << endl;
      return 0;
    }
  }

  return 0;
}