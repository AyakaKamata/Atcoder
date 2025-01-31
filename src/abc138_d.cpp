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
  vector<bool> seen;
  onevec depth;
  const matrix &G;

  DFS(const matrix &G, const onevec &p, const onevec &x)
      : G(G), seen(G.size(), false), depth(G.size(), 0) {
    rep(i, 0, p.size()) { depth[p[i]] += x[i]; }
    dfs(0, -1);
  }

  void dfs(ll v, ll parent) {
    seen[v] = true;
    for (auto &u : G[v]) {
      if (u == parent)
        continue;
      depth[u] += depth[v];
      dfs(u, v);
    }
  }

  void output() const {
    rep(i, 0, depth.size()) {
      cout << depth[i];
      if (i < depth.size() - 1) {
        cout << ' ';
      } else {
        cout << endl;
      }
    }
  }
};

int main() {
  ll n, q;
  cin >> n >> q;
  matrix G(n);
  rep(i, 0, n - 1) {
    ll u, k;
    cin >> u >> k;
    u--, k--;
    G[u].push_back(k);
    G[k].push_back(u);
  }

  onevec p(q), x(q);
  rep(i, 0, q) {
    cin >> p[i] >> x[i];
    p[i]--;
  }

  DFS dfs_solver(G, p, x);
  dfs_solver.output();

  return 0;
}
