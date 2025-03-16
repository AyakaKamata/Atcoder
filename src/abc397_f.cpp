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


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> A(N+1);
    for (int i = 1; i <= N; i++){
        cin >> A[i];
    }

    // 前計算：prefix[i] = A[1..i] の中の種類数
    vector<int> prefix(N+1, 0), suffix(N+2, 0);
    vector<int> freq(N+1, 0);
    int distinct = 0;
    for (int i = 1; i <= N; i++){
        if(freq[A[i]] == 0) distinct++;
        freq[A[i]]++;
        prefix[i] = distinct;
    }
    // suffix[i] = A[i..N] の中の種類数
    fill(freq.begin(), freq.end(), 0);
    distinct = 0;
    for (int i = N; i >= 1; i--){
        if(freq[A[i]] == 0) distinct++;
        freq[A[i]]++;
        suffix[i] = distinct;
    }
    // suffix[N+1] = 0（右側は空集合）
    suffix[N+1] = 0;
 
    vector<int> M(N+2, 0); // M[L] を格納（L:2..N-1）
    vector<int> midFreq(N+1, 0);
    int midDistinct = 0;
    int R = 2; // 中間部分の右端。L の初期値は 2 (すなわち i=1 のときの中間部分)
    // 初期状態：L = 2, 窓は [2, R] = [2,2]
    midDistinct = 0;
    fill(midFreq.begin(), midFreq.end(), 0);
    // 初めての窓 [2,2]
    midFreq[A[2]] = 1;
    midDistinct = 1;

    // F(L, R) = midDistinct + suffix[R+1]
    for (int L = 2; L <= N-1; L++){
        // まず、R は必ず >= L, なので必要なら調整
        if(R < L) {
            R = L;
            fill(midFreq.begin(), midFreq.end(), 0);
            midFreq[A[L]] = 1;
            midDistinct = 1;
        }
        // 現在の窓 [L,R] の値
        int curF = midDistinct + suffix[R+1];
        // 右端 R を伸ばせるなら、右側で F(L, R+1) が改善するかチェック
        while(R < N && (midDistinct + suffix[R+2]) >= curF) {
            R++;
            // 窓 [L,R] に A[R] を加える
            if(midFreq[A[R]] == 0) {
                midDistinct++;
            }
            midFreq[A[R]]++;
            curF = midDistinct + suffix[R+1];
        }
        // 現在の最適値 F(L, *) は curF
        M[L] = curF;

        // 次、L を 1 つ進めるので、窓から A[L] を除く
        midFreq[A[L]]--;
        if(midFreq[A[L]] == 0) {
            midDistinct--;
        }
    }

    // 最終的に、i は 1..N-2 となり、中間部分は L = i+1 (2 ≤ L ≤ N-1)
    int ans = 0;
    for (int i = 1; i <= N-2; i++){
        ans = max(ans, prefix[i] + M[i+1]);
    }

    cout << ans << "\n";
    return 0;
}