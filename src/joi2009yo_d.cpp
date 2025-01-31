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
template <typename T> ll llsize(const T &container) {
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

class DFS {
public:
  vector<vector<bool>> seen;
  ll max_depth;

  DFS(const matrix &G)
      : seen(G.size(), vector<bool>(G[0].size(), false)), max_depth(0) {
    for (ll i = 0; i < (ll)G.size(); i++) {
      for (ll j = 0; j < (ll)G[0].size(); j++) {
        if (G[i][j] == 1) {
          dfs(G, i, j, 1);
        }
      }
    }
  }

  void dfs(const matrix &G, ll h, ll w, ll d) {
    seen[h][w] = true;
    chmax(max_depth, d);

    rep(i, 0, 4) {
      ll nh = h + dx[i];
      ll nw = w + dy[i];
      if (nh >= 0 && nh < (ll)G.size() && nw >= 0 && nw < (ll)G[0].size()) {
        if (!seen[nh][nw] && G[nh][nw] == 1) {
          dfs(G, nh, nw, d + 1);
        }
      }
    }
    seen[h][w] = false;
  }

  void output() const { cout << max_depth << endl; }
};

int main() {
  ll W, H;
  cin >> W >> H;
  matrix G(H, vector<ll>(W));
  rep(i, 0, H) rep(j, 0, W) { cin >> G[i][j]; }
  DFS dfs_solver(G);
  dfs_solver.output();
  return 0;
}
