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

/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/
int main() {
  int n, m;
  cin >> n >> m;
  int x, y;
  bool prox[12][12] = {false};
  rep(i, 0, m) {
    cin >> x >> y;
    prox[x - 1][y - 1] = prox[y - 1][x - 1] = true;
  }
  int ans = 0;
  rep(i, 0, 1 << n) {
    int t = bitset<12>(i).count();
    bool f = true;
    rep(j, 0, n) rep(k, 0, j) {
      if ((i & (1 << j)) && (i & (1 << k)) && !prox[j][k]) {
        f = false;
      }
    }
    if (f) {
      chmax(ans, t);
    }
  }
  cout << ans << endl;
  return 0;
}
