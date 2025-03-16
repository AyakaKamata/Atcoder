#include <bits/stdc++.h>
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define rrep(i, a, b) for (ll i = a; i >= b; i--)
#define fore(i, a)                                                             \
  if (!(a).empty())                                                            \
    for (auto &i : a)
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

const ld PI = 3.14159265358979323846;
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
// #include <atcoder/all>
// using namespace atcoder;
struct UnionFind {
  vector<int> par;  // 各要素の親の番号
  vector<int> rank; // 各要素のランク
  vector<int> siz;  // 各要素の属する集合のサイズ

  // コンストラクタ：最初は全てが根で、ランクは1、サイズは1に初期化
  UnionFind(int N) : par(N), rank(N, 1), siz(N, 1) {
    for (int i = 0; i < N; i++) {
      par[i] = i;
    }
  }

  // データ x の根を求める (経路圧縮付き)
  int root(int x) {
    if (par[x] == x)
      return x;
    return par[x] = root(par[x]);
  }

  // x と y を同じ集合に統合（union-by-rank、サイズも更新）
  void unite(int x, int y) {
    int rx = root(x);
    int ry = root(y);
    if (rx == ry)
      return;
    if (rank[rx] < rank[ry]) {
      par[rx] = ry;
      siz[ry] += siz[rx];
    } else if (rank[rx] > rank[ry]) {
      par[ry] = rx;
      siz[rx] += siz[ry];
    } else {
      par[ry] = rx;
      rank[rx]++;
      siz[rx] += siz[ry];
    }
  }

  // x と y が同じ集合に属しているか判定
  bool same(int x, int y) { return root(x) == root(y); }

  // x の属する集合のサイズを返す
  int size(int x) { return siz[root(x)]; }
};
// int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(nullptr);

//   ll n;
//   in(n);
//   onevec A(n);
//   rep(i, 0, n) in(A[i]);
//   unordered_map<ll, ll> dict;
//   rep(i, 0, n) {
//     dict[A[i]]++;
//   }
//   unordered_map<ll,ll>dict2;
//   ll ans=0;
//   rep(i,0,n){
//     dict[A[i]]--;
//     dict[A[i]]++;
//     if(dict[A[i]]==0){
//       dict.erase(A[i]);
//     }
//     chmax(ans,lsize(dict)+lsize(dict2));
//   }
//   out(ans);

//   // ll ans=-1;
//   // rep(i, 1, n - 2) {
//   //   ll tmp=0;
//   //   UnionFind uf(3 * pow(10, 5) + 1);

//   //   rep(j, 0, i-1) {
//   //     uf.unite(A[j],A[j+1]);
//   //   }
//   //   tmp+=uf.size(A[0]);
//   //   UnionFind uf2(3 * pow(10, 5) + 1);
//   //   rep(j, i, n-1){
//   //     uf2.unite(A[j],A[j+1]);
//   //   }
//   //   tmp+=uf2.size(A[n-1]);
//   //   chmax(ans,tmp);
//   // }
//   // out(ans);
//   return 0;
// }
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n;
  cin >> n;
  vector<ll> A(n);
  for (ll i = 0; i < n; i++) cin >> A[i];

  unordered_map<ll, ll> right_count;
  unordered_set<ll> left_set;

  // 右側のカウントを初期化
  for (ll i = 0; i < n; i++) right_count[A[i]]++;

  ll max_unique = 0;

  // 左側に要素を追加しながら、右側から削除
  for (ll i = 0; i < n - 1; i++) {
      left_set.insert(A[i]);
      right_count[A[i]]--;
      if (right_count[A[i]] == 0) {
          right_count.erase(A[i]);
      }
      max_unique = max(max_unique, (ll)left_set.size() + (ll)right_count.size());
  }

  cout << max_unique << "\n";
  return 0;
}