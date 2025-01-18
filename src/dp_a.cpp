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
  int n;
  cin >> n;
  vector<int> h(n);
  for (int i = 0; i < n; ++i) {
    cin >> h[i];
  }
  // DP テーブル
  vector<ll> dp(n, INF);

  // 初期条件
  dp[0] = 0;

  // ループ
  for (int i = 1; i < n; ++i) {
    chmin(dp[i], dp[i - 1] + abs(h[i] - h[i - 1]));
    if (i > 1) {
      chmin(dp[i], dp[i - 2] + abs(h[i] - h[i - 2]));
    }
  }

  // 解を得て出力
  cout << dp[n - 1] << endl;

  return 0;
}