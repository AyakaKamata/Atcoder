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
using matrix = vector<vector<int>>;
using onevec = vector<int>;
using iset = set<int>;

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
template <typename T> int isize(const T &container) {
  return static_cast<int>(container.size());
}
template <typename T> bool ifbit(T number, int bit) {
  return (number & (1 << bit)) != 0;
}

/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/

int main() {
  int r, c;
  cin >> r >> c;
  matrix bins(r, onevec(c, 0));
  rep(i, 0, r) {
    rep(j, 0, c) { cin >> bins[i][j]; }
  }
  int ans = 0;
  rep(i, 0, 1 << r) {
    int tmp = 0;
    onevec col(c, 0);

    rep(j, 0, r) {
      if (ifbit(i, j)) {
        rep(k, 0, c) { col[k] += 1 - bins[j][k]; }
      } else {
        rep(k, 0, c) { col[k] += bins[j][k]; }
      }
    }
    rep(k, 0, c) { tmp += max(col[k], r - col[k]); }
    chmax(ans, tmp);
  }
  cout << ans << endl;
  return 0;
}