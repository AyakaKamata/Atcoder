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
/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/
const long long MOD = 998244353;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> par(
        n + 1, 0); // parent for each vertex (1-indexed); vertex 1 is the root.
    for (int i = 2; i <= n; i++) {
      cin >> par[i];
    }

    // Compute level for each vertex: level[1] = 0, level[i] = level[par[i]]+ 1.
    vector<int> level(n + 1, 0);
    level[1] = 0;
    int maxLevel = 0;
    for (int i = 2; i <= n; i++) {
      level[i] = level[par[i]] + 1;
      maxLevel = max(maxLevel, level[i]);
    }

    // Group vertices by level.
    vector<vector<int>> levels(maxLevel + 1);
    for (int i = 1; i <= n; i++) {
      levels[level[i]].push_back(i);
    }

    // dp[v] will count valid sequences ending at vertex v.
    vector<long long> dp(n + 1, 0);
    // T[L] = sum of dp[v] for vertices v in level L.
    vector<long long> Tlevel(maxLevel + 1, 0);

    // Base case: the sequence [1].
    dp[1] = 1;
    Tlevel[0] = 1;

    // For level 1, from the root any vertex is allowed.
    if (maxLevel >= 1) {
      for (int v : levels[1]) {
        dp[v] = 1;
        Tlevel[1] = (Tlevel[1] + dp[v]) % MOD;
      }
    }

    // For levels 2 and beyond, use the recurrence:
    // dp[v] = Tlevel[L-1] - dp[parent(v)] (ensuring we subtract the forbidden
    // move).
    for (int L = 2; L <= maxLevel; L++) {
      long long sumPrev =
          Tlevel[L - 1]; // total sequences ending in previous level
      for (int v : levels[L]) {
        long long ways = sumPrev - dp[par[v]];
        ways %= MOD;
        if (ways < 0)
          ways += MOD;
        dp[v] = ways;
        Tlevel[L] = (Tlevel[L] + dp[v]) % MOD;
      }
    }

    // The answer is the sum of valid sequences ending at any level.
    long long ans = 0;
    for (int L = 0; L <= maxLevel; L++) {
      ans = (ans + Tlevel[L]) % MOD;
    }

    cout << ans % MOD << "\n";
  }
  return 0;
}