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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int H, W, N, M;
  cin >> H >> W >> N >> M;

  // ランプとブロックの配置を記録するグリッド
  vector<vector<bool>> lamp(H, vector<bool>(W, false));
  vector<vector<bool>> block(H, vector<bool>(W, false));

  for (int i = 0; i < N; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--; // 0-indexed に変換
    lamp[a][b] = true;
  }

  for (int i = 0; i < M; i++) {
    int c, d;
    cin >> c >> d;
    c--;
    d--;
    block[c][d] = true;
  }

  // 各セルが光で照らされているかの判定
  vector<vector<bool>> light(H, vector<bool>(W, false));

  // 横方向の照射判定（左→右, 右→左）
  for (int i = 0; i < H; i++) {
    bool lit = false;
    for (int j = 0; j < W; j++) {
      if (block[i][j])
        lit = false; // ブロックに当たったらリセット
      if (lamp[i][j])
        lit = true; // ランプがあれば光が届く
      if (lit)
        light[i][j] = true;
    }
    lit = false;
    for (int j = W - 1; j >= 0; j--) {
      if (block[i][j])
        lit = false;
      if (lamp[i][j])
        lit = true;
      if (lit)
        light[i][j] = true;
    }
  }

  // 縦方向の照射判定（上→下, 下→上）
  for (int j = 0; j < W; j++) {
    bool lit = false;
    for (int i = 0; i < H; i++) {
      if (block[i][j])
        lit = false;
      if (lamp[i][j])
        lit = true;
      if (lit)
        light[i][j] = true;
    }
    lit = false;
    for (int i = H - 1; i >= 0; i--) {
      if (block[i][j])
        lit = false;
      if (lamp[i][j])
        lit = true;
      if (lit)
        light[i][j] = true;
    }
  }

  // ブロックがないセルで光が届いているセルの数をカウント
  long long ans = 0;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (!block[i][j] && light[i][j])
        ans++;
    }
  }

  cout << ans << "\n";
  return 0;
}
