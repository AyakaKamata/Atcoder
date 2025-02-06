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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;
    vector<string> s(5);
    for (int i = 0; i < 5; i++) {
        cin >> s[i];
    }

    // costMat[i][c]: cost for column i if we assign color c
    // Color mapping: 0 -> R, 1 -> B, 2 -> W
    vector<vector<ll>> costMat(n, vector<ll>(3, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            char c = s[j][i];
            if (c == 'R') {
                // If cell is 'R', then no cost for R (index 0),
                // but cost 1 for B (index 1) and W (index 2).
                costMat[i][1]++;
                costMat[i][2]++;
            } else if (c == 'B') {
                // If cell is 'B', then no cost for B (index 1).
                // Cost 1 for R (index 0) and W (index 2).
                costMat[i][0]++;
                costMat[i][2]++;
            } else if (c == 'W') {
                // If cell is 'W', then no cost for W (index 2).
                // Cost 1 for R (index 0) and B (index 1).
                costMat[i][0]++;
                costMat[i][1]++;
            } else if (c == '#') {
                // For '#' add cost 1 for every color.
                costMat[i][0]++;
                costMat[i][1]++;
                costMat[i][2]++;
            }
        }
    }

    // dp[i][c]: minimum cost to paint columns 0..i with column i painted with color c
    vector<vector<ll>> dp(n, vector<ll>(3, INFL));
    // Base case: first column
    dp[0] = costMat[0];

    // DP transition: for each subsequent column,
    // choose a color and add the cost plus the minimum cost from the previous column
    // where a different color was used.
    for (int i = 1; i < n; i++) {
        dp[i][0] = costMat[i][0] + min(dp[i-1][1], dp[i-1][2]);
        dp[i][1] = costMat[i][1] + min(dp[i-1][0], dp[i-1][2]);
        dp[i][2] = costMat[i][2] + min(dp[i-1][0], dp[i-1][1]);
    }

    // The answer is the minimum cost for the last column over all colors.
    ll ans = min({dp[n-1][0], dp[n-1][1], dp[n-1][2]});
    cout << ans << "\n";

    return 0;
}