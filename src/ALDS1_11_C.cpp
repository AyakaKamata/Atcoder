#include <bits/stdc++.h>
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define rrep(i, a, b) for (ll i = a; i >= b; i--)
#define fore(i, a) for (auto &i : a)
#define all(x) (x).begin(), (x).end()
#pragma GCC optimize("-O3")

using namespace std;
using ll = long long;
using ld = long double;
using i128 = __int128_t;
using pll = pair<ll, ll>;
using pld = pair<ld, ld>;
using matrix = vector<vector<ll>>;
using matrixld = vector<vector<ld>>;
using onevec = vector<ll>;
using onevecld = vector<ld>;
using lset = set<ll>;

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
template <typename T> ll lsize(const T &container) {
  return static_cast<ll>(container.size());
}
template <typename T> bool ifbit(T number, ll bit) {
  return (number & (1LL << bit)) != 0;
}
template <typename T> ll twice(const T &a) { return a * a; }
template <typename T> T bits_count(T v) { return __builtin_popcountll(v); }

template <typename T> T factorial(T n) {
  T result = 1;
  for (T i = 1; i <= n; ++i) {
    result *= i;
  }
  return result;
}

template <typename T> T pdistance(const vector<pair<T, T>> &xy, int i, int j) {
  return sqrt(twice(xy[i].first - xy[j].first) +
              twice(xy[i].second - xy[j].second));
}

template <typename T> void print(T value, int precision) {
  cout << fixed << setprecision(precision) << value << endl;
}

const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
const int dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};
/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/

template <typename... Args> void input(Args &...args) { (cin >> ... >> args); }

template <typename... Args> void output(const Args &...args) {
  constexpr size_t n = sizeof...(args);
  size_t i = 0;
  ((cout << args << (++i < n ? " " : "")), ...) << "\n";
}

void bfs(const matrix &G, ll start, vector<ll> &dist) {
  queue<ll> que;
  dist[start] = 0;
  que.push(start);

  while (!que.empty()) {
    ll v = que.front();
    que.pop();
    for (ll nv : G[v]) {
      if (dist[nv] != -1) {
        continue;
      } // Skip visited nodes
      dist[nv] = dist[v] + 1;
      que.push(nv);
    }
  }
}

int main() {

  ll N; // 頂点数と辺数
  input(N);

  matrix G(N);
  for (ll i = 0; i < N; ++i) { // 辺の入力
    ll u, k;
    input(u, k);
    u--;

    rep(i, 0, k) {
      ll v;
      input(v);
      v--; // 0-indexedに変換
      G[u].push_back(v);
    }
  }

  vector<ll> dist(N, -1); // 距離配列
  bfs(G, 0, dist);        // 頂点0を始点としてBFS実行

  for (ll v = 0; v < N; v++) {
    output(v + 1, dist[v]);
  }

  return 0;
}