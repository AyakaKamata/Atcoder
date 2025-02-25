#include <bits/stdc++.h>
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define rrep(i, a, b) for (ll i = a; i >= b; i--)
#define fore(i, a) for (auto &i : a)
#define all(x) (x).begin(), (x).end()
#define YES cout << "Yes" << endl
#define NO cout << "No" << endl
#define YN                                                                     \
  {                                                                            \
    cout << "Yes" << endl;                                                     \
  }                                                                            \
  else {                                                                       \
    cout << "No" << endl;                                                      \
  } // if(a==b)YN;
#define FAIL cout << -1 << endl
#pragma GCC optimize("-O3")

using namespace std;
using ll = long long;
using ld = long double;
using i128 = __int128_t;
using pll = pair<ll, ll>;
using pld = pair<ld, ld>;
using matrix = vector<vector<ll>>;
using matrixld = vector<vector<ld>>;
using matrixb = vector<vector<bool>>;
using onevec = vector<ll>;
using onevecld = vector<ld>;
using onevecb = vector<bool>;
using lset = set<ll>;

const ll INFL = 1LL << 60;
template <class T> T chmin(T &a, T b) {
  if (a > b) {
    a = b;
  }
  return a;
}
template <class T> T chmax(T &a, T b) {
  if (a < b) {
    a = b;
  }
  return a;
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
template <typename T>
int isperp(const vector<pair<T, T>> &xyz, int i, int j, int k) {
  T dx1 = xyz[i].first - xyz[j].first, dy1 = xyz[i].second - xyz[j].second;
  T dx2 = xyz[k].first - xyz[j].first, dy2 = xyz[k].second - xyz[j].second;

  T dot = dx1 * dx2 + dy1 * dy2;

  return (dot > 0) ? 0 : (dot == 0) ? 1 : -1;
}

template <typename T>
T crossp(const vector<pair<T, T>> &xyz, int i, int j, int k) {
  T dx1 = xyz[i].first - xyz[j].first, dy1 = xyz[i].second - xyz[j].second;
  T dx2 = xyz[k].first - xyz[j].first, dy2 = xyz[k].second - xyz[j].second;

  return dx1 * dy2 - dy1 * dx2;
}

template <typename T> T mod_exp(T base, T exp, T mod) {
  T result = 1;
  while (exp > 0) {
    if (exp & 1)
      result = (result * base) % mod;
    base = (base * base) % mod;
    exp >>= 1;
  }
  return result;
}

template <typename T> void print(T value, int precision) {
  cout << fixed << setprecision(precision) << value << endl;
}

template <typename... Args> void in(Args &...args) { (cin >> ... >> args); }

template <typename... Args> void out(const Args &...args) {
  constexpr size_t n = sizeof...(args);
  size_t i = 0;
  ((cout << args << (++i < n ? " " : "")), ...) << "\n";
}

const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
const int dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};
string strrep(const string &s, const string &from, const string &to) {

  unordered_map<char, char> trans;
  for (size_t i = 0; i < from.size(); ++i) {
    trans[from[i]] = to[i];
  }

  string res = s;
  for (char &c : res) {
    if (trans.count(c)) {
      c = trans[c];
    }
  }
  return res;
}
template <typename T> bool isprime(T N) {
  if (N < 2)
    return false;
  for (T i = 2; i * i <= N; i++) {
    if (N % i == 0)
      return false;
  }
  return true;
}
vector<pair<char, int>> rle(const string &s) {
  vector<pair<char, int>> res;
  for (int i = 0, cnt; i < s.size(); i += cnt) {
    cnt = 1;
    while (i + cnt < s.size() && s[i] == s[i + cnt])
      cnt++;
    res.emplace_back(s[i], cnt);
  }
  return res;
}
template <typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/
ll N, M, K, S, P, Q; // 頂点数と辺数とスタート地点
onevecb C, D;
matrix G;
void bfs(const matrix &G, ll start, vector<ll> &dist) {
  ll n = G.size();
  queue<ll> que;
  rep(i, 0, N) {
    if (C[i]) {
      dist[i] = 0; // 初期ノード
      que.push(i);
    }
  }

  while (!que.empty()) {
    ll v = que.front();
    que.pop();

    for (ll nv : G[v]) {
      if (dist[nv] != -1)
        continue; // 訪問済み
      dist[nv] = dist[v] + 1;
      que.push(nv);
    }
  }
}
void bfs_weight(const matrix &G, ll start, vector<ll> &dist) {
  ll n = G.size();
  min_priority_queue<pll> que;

  dist[start] = 0; // 初期ノード
  que.push({0, start});

  while (!que.empty()) {
    ll v = que.top().second;
    ll d = que.top().first;
    que.pop();
    if (dist[v] < d) {
      continue;
    }

    for (ll nv : G[v]) {
      if (C[nv]) {
        continue;
      }
      ll new_d;
      if (D[nv]) {
        new_d = d + Q;
      } else {
        new_d = d + P;
      }

      if (dist[nv] <= new_d)
        continue; // 訪問済み
      dist[nv] = new_d;
      que.push({new_d, nv});
    }
  }
}

int main() {

  in(N, M, K, S, P, Q);
  C.assign(N, false);
  rep(i, 0, K) {
    ll c;
    in(c);
    C[c - 1] = true;
  }
  G.resize(N);
  for (ll i = 0; i < M; ++i) { // 辺の入力
    ll u, v;
    cin >> u >> v;
    u--;
    v--; // 0-indexedに変換
    G[u].push_back(v);
    G[v].push_back(u); // 無向グラフ
  }

  vector<ll> dist(N, -1); // 距離配列
  bfs(G, 0, dist);        // 頂点0を始点としてBFS実行
  D.assign(N, false);
  rep(i, 0, N) {
    if (dist[i] > 0 && dist[i] <= S) {
      D[i] = true;
    }
  }
  dist = onevec(N, INFL); // 距離配列
  bfs_weight(G, 0, dist); // 頂点0を始点としてBFS実行

  if (D[N - 1])
    out(dist[N - 1] - Q);
  else
    out(dist[N - 1] - P);

  return 0;
}
