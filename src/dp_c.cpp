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
  cin >> n;
  vector<vector<int>> abc(n, vector<int>(3));
  for (int i = 0; i < n; ++i) {
    cin >> abc[i][0] >> abc[i][1] >> abc[i][2];
  }
  // DP テーブル
  vector<vector<ll>> dp(n, vector<ll>(3, 0));

  // 初期条件
  for (int i = 0; i < 3; ++i) {
    dp[0][i] = abc[0][i];
  }

  // ループ
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < 3; ++j) {
      for (int k = 0; k < 3; ++k) {
        if (j != k) {
          chmax(dp[i][j], dp[i - 1][k] + abc[i][j]);
        }
      }
    }
  }

  // 解を得て出力
  cout << *max_element(dp[n - 1].begin(), dp[n - 1].end()) << endl;

  return 0;
}