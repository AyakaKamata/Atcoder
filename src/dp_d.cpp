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
  for (int i = 0; i < n; ++i) {
    cin >> wv[i][0] >> wv[i][1] ;
  }
  // DP テーブル
  vector<vector<ll>> dp(n+1, vector<ll>(w+1, 0));

  // ループ
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= w; ++j) {
      if (j>=wv[i-1][0]){
        chmax(dp[i][j], dp[i - 1][j - wv[i-1][0]] + wv[i-1][1]);
      }
        chmax(dp[i][j], dp[i - 1][j]);

    }
  }

  // 解を得て出力
  cout << dp[n][w] << endl;

  return 0;
}