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
using matrixb = vector<vector<bool>>;
using onevec = vector<ll>;
using onevecld = vector<ld>;
using onevecb = vector<bool>;
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
/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/
const int MOD = 10000;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, k;
  cin >> n >> k;

  // 各日のパスタの予定。決まっていなければ -1
  vector<int> fix(n, -1);
  for (int i = 0; i < k; i++) {
    int a, b;
    cin >> a >> b;
    fix[a - 1] = b - 1; // 0-indexed にする
  }

  // dp[i][j][k] = (i-1 日目にパスタ j，i 日目にパスタ k を食べた場合の，
  // i 日目までのパスタの食べ方の数)
  // ※ dp[1] が初期状態 <- i-1 するから
  vector<matrix> dp(n, matrix(3, onevec(3, 0)));

  // 初期状態の設定（1日目、2日目）<- 0-index
  if (fix[0] != -1) {
    if (fix[1] != -1) {
      dp[1][fix[0]][fix[1]] = 1;
    } else {
      for (int j = 0; j < 3; j++) {
        dp[1][fix[0]][j] = 1; // 2日目は３通りの可能性がある
      }
    }
  } else {
    if (fix[1] != -1) {
      for (int i = 0; i < 3; i++) {
        dp[1][i][fix[1]] = 1; // 1日目は３通りの可能性がある
      }
    } else {
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          dp[1][i][j] = 1; // 1,2日目は３通りの可能性がある
        }
      }
    }
  }

  // DP の更新
  // i 日目（0-indexed）のパスタが決まっている場合は、それに従う
  // なお、3日連続で同じパスタを食べるケースは除外する
  for (int i = 2; i < n; i++) {     // 初期値はdp[1]
    for (int j = 0; j < 3; j++) {   // i-1 日目のパスタ
      for (int k = 0; k < 3; k++) { // i 日目のパスタ（候補）
        // もし i 日目が既に決まっていて候補と違うならスキップ
        if (fix[i] != -1 && fix[i] != k)
          continue;
        for (int l = 0; l < 3; l++) { // i-2 日目のパスタ
          // 3日連続同じパスタ（l, j, k(候補) がすべて同じ）は除外
          if (l == j && j == k)
            continue;
          dp[i][j][k] = (dp[i][j][k] + dp[i - 1][l][j]) % MOD;
        }
      }
    }
  }

  // 最終日の組み合わせの総和を答えとする
  int answer = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      answer = (answer + dp[n - 1][i][j]) % MOD;
    }
  }

  cout << answer << "\n";
  return 0;
}