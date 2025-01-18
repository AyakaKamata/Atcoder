#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
const long long INF = 1LL << 60;
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
using namespace std;
using ll = long long;
int main() {
  int n, w;
  cin >> n >> w;
  vector<vector<int>> wv(n, vector<int>(2));
  int max_v = 0;
  for (int i = 0; i < n; ++i) {
    int v;
    cin >> wv[i][0] >> v;
    wv[i][1] = v;
    max_v += v;
  }
  // DP テーブル
  vector<vector<ll>> dp(n + 1, vector<ll>(max_v+1, INF));
  dp[0][0] = 0;

  // ループ
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= max_v; ++j) {
      if (j >= wv[i - 1][1]) {
        chmin(dp[i][j], dp[i - 1][j - wv[i - 1][1]] + wv[i - 1][0]);
      }
      chmin(dp[i][j], dp[i - 1][j]);
    }
  }
  int res = 0;
  for (int i = 1; i <= max_v; ++i) {
    if (dp[n][i] <= w) {
      res = i;
    }
  }
  // 解を得て出力
  cout << res << endl;

  return 0;
}