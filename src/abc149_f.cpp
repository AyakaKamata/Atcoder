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
template <typename T> T twice(const T &a) { return a * a; }
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
template <typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
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
// a^n mod を計算する
long long modpow(long long a, long long n, long long mod) {
  long long res = 1;
  while (n > 0) {
    if (n & 1)
      res = res * a % mod;
    a = a * a % mod;
    n >>= 1;
  }
  return res;
}
// Fermatの小定理を利用して a の逆元を求める (mod が素数の場合)
ll modinv(ll a, ll mod) { return modpow(a, mod - 2, mod); }

/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

vector<int> parent, subSize;

// DFS 関数: v を頂点、p をその親とし、subSize[v] と parent[v] を計算する
void dfs(const matrix &G, int v, int p) {
  parent[v] = p;
  subSize[v] = 1;
  for (int u : G[v]) {
    if (u == p)
      continue;
    dfs(G, u, v);
    subSize[v] += subSize[u];
  }
}
int main() {
  ios::sync_with_stdio(false); // 入出力の高速化
  cin.tie(nullptr);            // cinとcoutを同期しない

  ll N;
  cin >> N; // 頂点の数 N を入力

  // グラフの隣接リストを初期化
  matrix G(N + 1);
  parent.assign(N + 1, 0);  // 各頂点の親を保持する配列
  subSize.assign(N + 1, 0); // 各頂点の部分木のサイズを保持する配列

  // グラフの辺の情報を読み込み、隣接リストを作成
  for (int i = 1; i <= N - 1; i++) {
    int u, v;
    cin >> u >> v;     // 辺 u-v を読み込む
    G[u].push_back(v); // u から v への辺
    G[v].push_back(u); // v から u への辺（無向グラフ）
  }

  // 頂点 1 を根とした DFS を実行
  dfs(G, 1, 0); // DFS を実行して親ノードと部分木のサイズを計算

  // 2 の累乗を事前計算（pow2[i] = 2^i % MOD）
  vector<ll> pow2(N + 1, 1); // 2^i % MOD を格納する配列
  for (int i = 1; i <= N; i++) {
    pow2[i] = (pow2[i - 1] * 2) % MOD; // pow2[i] を計算
  }

  // 1/2 の値（modular inverse）と (1/2)^(N-1) を計算
  ll inv2 = modinv(2, MOD);               // 2 の逆元を計算
  ll inv2_pow = modpow(inv2, N - 1, MOD); // (1/2)^(N-1) を計算

  // 各頂点 v の貢献度を計算
  ll ans = 0; // 最終的な答え
  for (int v = 1; v <= N; v++) {
    ll sumTerm = 1; // 定数項 1（初期値として 1）

    // 頂点 v の各隣接ノード u について
    for (int u : G[v]) {
      int compSize;
      if (u == parent[v]) {
        // u が親ノードなら、v の部分木のサイズは N - subSize[v]
        compSize = N - subSize[v];
      } else {
        // u が子ノードなら、その部分木のサイズは subSize[u]
        compSize = subSize[u];
      }

      // (2^compSize - 1) % MOD を計算
      ll addVal = (pow2[compSize] - 1) % MOD;
      if (addVal < 0)
        addVal += MOD;                    // 負の値にならないように調整
      sumTerm = (sumTerm + addVal) % MOD; // sumTerm を更新
    }

    // 各頂点 v の貢献度を計算
    ll term = (inv2 * (1 - (inv2_pow * sumTerm) % MOD)) % MOD;
    if (term < 0)
      term += MOD;            // 負の値にならないように調整
    ans = (ans + term) % MOD; // 最終結果を更新
  }

  // 最終結果を出力
  cout << ans % MOD << "\n";
  return 0; // プログラム終了
}
