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
using ull = unsigned long long;
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
template <typename T> void outvec(vector<T> vec) {
  rep(i, 0, lsize(vec)) {
    cout << vec[i] << (i == lsize(vec) - 1 ? "\n" : " ");
  }
}
// 入力の1次元行列の累積和（プレフィックスサム）を計算する関数
// 0-index
template <typename T> vector<T> CumsumVector(const vector<T> &vec) {
  T n = vec.size(); // 行数
  vector<T> sum = vec;
  for (T i = 1; i < n; i++) {
    sum[i] += sum[i - 1];
  }
  return sum;
}
// 入力の2次元行列の累積和（プレフィックスサム）を計算する関数
// 1-indexになる
// ans=(c,d)-(a-1,d)-(c,b-1)+(a-1,b-1)
template <typename T>
vector<vector<T>> CumsumSquare(const vector<vector<T>> &mat) {
  T n = mat.size();                  // 行数
  T m = (n > 0 ? mat[0].size() : 0); // 列数
  vector<vector<T>> sum(n + 1, vector<T>(m + 1, 0));

  for (T i = 1; i < n + 1; i++) {
    for (T j = 1; j < m + 1; j++) {
      sum[i][j] = mat[i - 1][j - 1];
      sum[i][j] += sum[i - 1][j];
      sum[i][j] += sum[i][j - 1];
      sum[i][j] -= sum[i - 1][j - 1];
    }
  }

  return sum;
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
#include <atcoder/all>
using namespace atcoder;
// int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(nullptr);

//   ll m, n;
//   in(n, m);

//   onevec A(n);
//   rep(i, 0, n) {
//     ll a;
//     in(a);
//     A[i] = a;
//   }

//   // まず、Fenwick Tree を用いて A の転倒数（inversion count）を求める
//   // 転倒数とは、i < j でありながら A[i] > A[j] となるペアの総数のこと
//   ll res = 0;
//   fenwick_tree<ll> f(m); // Fenwick Tree の初期値は全て 0
//   // 配列 A の各要素 x に対して、
//   // すでに登録している要素の中から、x より大きい値の個数を数えて加算する
//   fore(x, A) {
//     // x+1 から m-1 までの範囲の個数を求める → これが A[i] > A[j]
//     のペアに対応 res += f.sum(x + 1, m);
//     // 現在の値 x を Fenwick Tree に登録する（出現回数を 1 増やす）
//     f.add(x, 1);
//   }

//   // ans 配列は k = 0,1,...,M-1 に対する最終答えを保持するための配列
//   // 長さ m+1 とし、ans[m] はダミーとして使う
//   onevec ans(m + 1, 0);
//   // 初期値として、転倒数 res を ans[0] に設定し、ans[m] に -res を設定する
//   ans[0] = res;
//   ans[m] = -res;

//   // 以下のループでは、imos 法を用いた更新のために
//   // 各 A[i] に対し、j < i で A[j] ≠ A[i] となる数を数えて、
//   // ans[M - A[i]] に加算する操作を行う
//   onevec cnt(0, m); // 各値の出現回数をカウントする配列（初期値はすべて 0）
//   rep(i, 0, n) {
//     ll v = A[i];
//     // i はこれまでに処理した要素数、cnt[v] はこれまでのうち v の個数
//     // よって i - cnt[v] は、j < i で A[j] が v でないものの個数となる
//     ans[m - v] += i - cnt[v];
//     cnt[v] += 1; // v の出現回数を更新
//   }

//   // ここで cnt を再初期化して、逆順で同様の処理を行う
//   cnt = onevec(0, m);
//   // 配列 rev は A の逆順バージョン
//   onevec rev = A;
//   reverse(all(rev));
//   rep(i, 0, n) {
//     ll v = rev[i];
//     // 逆順にすることで、今度は j > i に相当するペアに対する更新を行う
//     // i - cnt[v] は、これまでに出現した v 以外の要素の数
//     ans[m - v] -= i - cnt[v];
//     cnt[v] += 1;
//   }

//   // imos 法の累積和計算：
//   // ans 配列を前から順に累積して、最終的な各 k に対する答えにする
//   rep(i, 1, m + 1) { ans[i] += ans[i - 1]; }

//   // k = 0 から m - 1 までの答えを出力
//   rep(i, 0, m - 1) { out(ans[i]); }

//   return 0;
// }
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // 入力：配列の要素数 n と、値の上限 m
  int n, m;
  cin >> n >> m;

  // 配列 a の入力（各要素は 0 〜 m-1 の整数と仮定）
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  // 値ごとの出現位置リスト g を作成
  // g[x] には、配列 a において値 x が出現するインデックスが格納される
  vector<vector<int>> g(m);
  for (int i = 0; i < n; i++) {
    int val = a[i];
    g[val].push_back(i);
  }

  // inversion count（転倒数）を求める
  // 転倒数とは、i < j なのに a[i] > a[j] となるペアの総数
  ll ans = 0;
  fenwick_tree<ll> fenw(m); // Fenwick Tree を作成（初期は全 0）
  for (auto x : a) {
    // すでに出現した要素の中から、x より大きい値の個数を加算
    ans += fenw.sum(x + 1, m);
    // 現在の値 x を Fenwick Tree に登録
    fenw.add(x, 1);
  }
  // 最初の inversion count を出力
  cout << ans << "\n";

  // c = 1 から m-1 まで、各段階での更新を行う
  for (int c = 1; c < m; c++) {
    ll c1 = 0, c2 = 0;
    // 値が (m - c) である要素の位置リストを取得
    int sz = g[m - c].size();
    // Ai=m-cのとき、つまりg[m-c]たちが大小関係変わる=0
    // このときg[m-c]の要素は全部０であることに留意
    for (int idx = 0; idx < sz; idx++) {
      int pos = g[m - c][idx];
      // 同じ値だと変化しないから
      // 左側にあってAi!=Ajのもの
      c1 += pos - idx;
      // 右側にあってAi!=Ajのもの
      c2 += (n - 1 - pos) - ((sz - 1) - idx);
    }
    // 補正分 (c1 - c2) を ans に加算
    ans += c1 - c2;
    // 現在の ans を出力
    cout << ans << "\n";
  }

  return 0;
}