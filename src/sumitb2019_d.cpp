#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
#define fore(i, a) for (auto &i : a)
#define all(x) (x).begin(), (x).end()
#pragma GCC optimize("-O3")

using namespace std;
using ll = long long;
using i128 = __int128_t;
const int INFI = INT_MAX / 2;
const ll INFL = 1LL << 60;
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
struct strmaster {
  string S;
  int N;
  strmaster() {}
  strmaster(string s) { init(s); }
  void init(string s) {
    S = s;
    N = S.length();
    init();
  }

  // get the nearest index for the char
  vector<int> left[26], right[26];
  inline void init() {
    rep(c, 0, 25) {
      right[c].resize(N);
      right[c][N - 1] = INFI;
    }
    rrep(i, N - 2, 0) {
      rep(c, 0, 25) right[c][i] = right[c][i + 1];
      right[S[i + 1]][i] = i + 1;
    }
    rep(c, 0, 25) {
      left[c].resize(N);
      left[c][0] = -1;
    }
    rep(i, 1, N - 1) {
      rep(c, 0, 25) left[c][i] = left[c][i - 1];
      left[S[i - 1]][i] = i - 1;
    }
  }
  inline int goright(int cu, int c) {
    if (cu == INFI)
      return INFI;
    if (cu < 0) {
      if (S[0] == c)
        return 0;
      cu = 0;
    }
    return right[c][cu];
  }
  inline int goleft(int cu, int c) {
    if (cu < 0)
      return cu;
    return left[c][cu];
  }
};

int N;
string S;
int main() {
  cin >> N >> S;

  fore(c, S) c -= '0';
  strmaster sm(S);

  int ans = 0;
  rep(x0, 0, 9) rep(x1, 0, 9) rep(x2, 0, 9) {
    int cu = -1;
    cu = sm.goright(cu, x0);
    cu = sm.goright(cu, x1);
    cu = sm.goright(cu, x2);
    if (cu < INFI)
      ans++;
  }
  cout << ans << endl;
}