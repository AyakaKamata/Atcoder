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

typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vector<vector<ll>> matrix;
typedef vector<vector<ld>> matrixld;
typedef vector<ll> onevec;
typedef vector<ld> onevecld;
typedef set<ll> lset;

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
/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/
ll n;
vector<bool> seen;
onevec f_o;
onevec l_o;

void dfs(const matrix &G, ll v, ll &ptr) {
  seen[v] = true;
  f_o[v] = ++ptr;
  fore(n_v, G[v]) {
    if (!seen[n_v]) {
      dfs(G, n_v, ptr);
    }
  }
  l_o[v] = ++ptr;
}
int main() {
  cin >> n;
  matrix G(n, vector<ll>());
  rep(i, 0, n) {
    ll u, k;
    cin >> u >> k;
    u--;
    rep(j, 0, k) {
      ll v;
      cin >> v;
      v--;
      G[u].push_back(v);
    }
  }
  ll ptr = 0;
  seen.resize(n, false);
  f_o.resize(n, 0);
  l_o.resize(n, 0);

  for (int i = 0; i < n; i++)
    if (! f_o[i]) dfs(G, i, ptr);
  rep(i, 0, n) { printf("%d %d %d\n", i + 1, f_o[i], l_o[i]); }
  return 0;
}