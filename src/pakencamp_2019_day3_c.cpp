#include <algorithm>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using i128 = __int128_t;

const ll INF = 1LL << 60;
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

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> a(n, vector<int>(m));
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < m; i++) {
      cin >> a[j][i];
    }
  }
  ll cnt = 0;
  ll ans = 0;
  for (int i = 0; i < m - 1; i++) {
    for (int j = i + 1; j < m; j++) {
      cnt = 0;
      for (int k = 0; k < n; k++) {
        cnt += max(a[k][i], a[k][j]);
      }
      chmax(ans, cnt);
    }
  }
  cout << ans << "\n";
  return 0;
}