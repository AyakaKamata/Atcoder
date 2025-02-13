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
#define fail cout << -1 << endl
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
/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/
int N, A[200009], C[200009];
// A[l], A[l+1], ..., A[r－1] を小さい順に整列する関数
void MergeSort(int l, int r) {
  // r－l=1 の場合、すでにソートされているので何もしない
  if (r - l == 1)
    return;
  // 2 つに分割した後、小さい配列をソート
  int m = (l + r) / 2;
  MergeSort(l, m);
  MergeSort(m, r);
  // この時点で以下の 2 つの配列がソートされている：
  // 列 A' に相当するもの [A[l], A[l+1], ..., A[m－1]]
  // 列 B' に相当するもの [A[m], A[m+1], ..., A[r－1]]
  // 以下が Merge 操作となります。
  int c1 = l, c2 = m, cnt = 0;
  while (c1 != m || c2 != r) {
    if (c1 == m) {
      // 列 A' が空の場合
      C[cnt] = A[c2];
      c2++;
    } else if (c2 == r) {
      // 列 B' が空の場合
      C[cnt] = A[c1];
      c1++;
    } else {
      // そのいずれでもない場合
      if (A[c1] < A[c2]) {
        C[cnt] = A[c1];
        c1++;
      } else {
        C[cnt] = A[c2];
        c2++;
      }
    }
    cnt++;
  } // 列 A', 列 B' を合併した配列 C を A に移す
  // [C[0], ..., C[cnt－1]] －> [A[l], ..., A[r－1]]
  for (int i = 0; i < cnt; i++)
    A[l + i] = C[i];
}
int main() { // 入力
  cin >> N;
  for (int i = 1; i <= N; i++)
    cin >> A[i];
  // マージソート → 答えの出力
  MergeSort(1, N + 1);
  for (int i = 1; i <= N; i++)
    cout << A[i] << endl;
  return 0;
}