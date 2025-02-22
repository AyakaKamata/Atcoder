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
/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/
class DFS {
public:
  vector<bool> seen;   // 頂点が訪問済みかどうかを記録する配列
  vector<ll> f_o, l_o; // 各頂点の最初の訪問順 (f_o) と最後の訪問順 (l_o)
  ll ptr;              // 訪問順をカウントする変数
  ll cnt;              // 連結成分の数をカウントする変数

  // コンストラクタ：グラフを受け取り、DFSを実行
  DFS(const matrix &G)
      : seen(G.size(), false), f_o(G.size(), 0), l_o(G.size(), 0), ptr(0),
        cnt(0) {
    for (ll i = 0; i < (ll)G.size(); i++) {
      if (!seen[i] &&
          (lsize(G[i]) == 1 || lsize(G[i]) == 4)) { // 未訪問の頂点からDFSを開始
        cnt++;                                      // 新しい連結成分を発見
        dfs(G, i);
      }
    }
  }

  // 深さ優先探索 (DFS)
  void dfs(const matrix &G, ll v) {
    seen[v] = true;       // 頂点 v を訪問済みにする
    f_o[v] = ++ptr;       // 最初の訪問順を記録
    for (ll n_v : G[v]) { // 頂点 v に隣接する各頂点について探索
      if (!seen[n_v] && lsize(G[n_v]) == 4)
        dfs(G, n_v);
    }
    l_o[v] = ++ptr; // 最後の訪問順を記録
  }

  // 結果を出力
  void output() const {
    ll res = 0;
    for (ll i = 0; i < (ll)f_o.size(); i++) {
      chmax(res, l_o[i] - f_o[i]);
      out(res);
    }
  }
};

int main() {
  ll n;
  cin >> n;
  matrix G(n);
  for (ll i = 0; i < n; i++) {
    ll u, k;
    cin >> u >> k;
    u--; // 0-indexed に変換
    for (ll j = 0; j < k; j++) {
      ll v;
      cin >> v;
      v--; // 0-indexed に変換
      G[u].push_back(v);
    }
  }

  DFS dfs_solver(G);   // DFSを実行
  dfs_solver.output(); // 結果を出力

  return 0;
}