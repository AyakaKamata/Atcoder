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
// int main() {

//   ll n;
//   cin >> n;
//   onevec four;
//   for (ll i = 1; i * (i + 1) * (i + 2) / 6 <= n; i++) {
//     four.push_back(i * (i + 1) * (i + 2) / 6);
//   }
//   while (n != 0) {
//     vector<ll> dp(n + 1, INFL);
//     dp[0] = 0;
//     vector<ll> dp_(n + 1, INFL);
//     dp_[0] = 0;
//     fore(f, four) {
//       if (f > n)
//         break;
//       rep(j, f, n + 1) {
//         // 後ろから更新する 重複ありなら前から、jをw[i]からWまで回す
//         chmin(dp[j], dp[j - f] + 1);
//         if (f % 2 == 1) {
//           // 後ろから更新する 重複ありなら前から、jをw[i]からWまで回す
//           chmin(dp_[j], dp_[j - f] + 1);
//         }
//       }
//     }

//     out(dp[n], dp_[n]);
//     in(n);
//   }

//   return 0;
// }
int main() {

  ll n = pow(10, 6);
  onevec four(200);
  rep(i, 1, 201) { four[i - 1] = (i * (i + 1) * (i + 2)) / 6; }
  vector<ll> dp(n + 1, INFL);
  dp[0] = 0;
  vector<ll> dp_(n + 1, INFL);
  dp_[0] = 0;
  fore(i, four) {
    rep(j, i, n + 1) {
      // 後ろから更新する 重複ありなら前から、jをw[i]からWまで回す
      chmin(dp[j], dp[j - i] + 1);
      if (i % 2 == 1) {
        // 後ろから更新する 重複ありなら前から、jをw[i]からWまで回す
        chmin(dp_[j], dp_[j - i] + 1);
      }
    }
  }
  in(n);

  while (n != 0) {

    out(dp[n], dp_[n]);
    in(n);
  }

  return 0;
}