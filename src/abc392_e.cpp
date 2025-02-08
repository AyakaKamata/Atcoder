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

#define UFLIMIT (2 << 17)
int unicnt[UFLIMIT];
vector<vector<array<int, 3>>> amari; // add
void ufinit(int n) {
  for (int i = 0; i < n; i++)
    unicnt[i] = 1;
  amari.resize(n); // add
}
int ufroot(int x) {
  return unicnt[x] <= 0 ? -(unicnt[x] = -ufroot(-unicnt[x])) : x;
}
int ufsame(int x, int y) { return ufroot(x) == ufroot(y); }
void uni(int x, int y) {
  if ((x = ufroot(x)) == (y = ufroot(y)))
    return;
  if (unicnt[x] < unicnt[y])
    swap(x, y);
  unicnt[x] += unicnt[y];
  unicnt[y] = -x;
  amari[x].insert(amari[x].end(), amari[y].begin(), amari[y].end()); // add
  amari[y].clear();                                                  // add
}
#undef UFLIMIT

int main() {
  int n, m;
  cin >> n >> m;

  ufinit(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    x--, y--;
    if (ufsame(x, y)) {
      amari[ufroot(x)].push_back({x, y, i});
    } else {
      uni(x, y);
    }
  }

  vector<pair<int, int>> cc;
  for (int i = 0; i < n; i++)
    if (ufroot(i) == i)
      cc.push_back({amari[i].size(), i});
  sort(cc.rbegin(), cc.rend());

  cout << cc.size() - 1 << endl;

  int pos = 1;
  for (auto [_, root] : cc) {
    for (auto [x, y, i] : amari[root]) {
      if (pos < cc.size()) {
        cout << i + 1 << ' ' << x + 1 << ' ' << cc[pos++].second + 1 << endl;
      }
    }
  }
}