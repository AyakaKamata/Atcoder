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

int main() {
  int n, m;
  cin >> n >> m;
  int k;
  matrix s(m);
  rep(i, 0, m) {
    cin >> k;
    s[i].resize(k);
    int s_i;
    rep(j, 0, k) { cin >> s_i;
    s[i][j]=s_i-1; }
  }

  vector<int> p(m);
  rep(i, 0, m) { cin >> p[i]; }
  int res = 0;
  rep(i, 0, 1 << n) {
    int ok = 0;
    rep(j, 0, m) {
      int cnt = 0;
      fore(s_, s[j]){ if (i & (1 << s_)) { cnt++; }}
      if (cnt % 2 == p[j]) {
        ok += 1;
      }
    }
    if (ok == m) {
      res += 1;
    }
  }
  cout << res << endl;
  return 0;
}