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

typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vector<vector<ll>> matrix;
typedef vector<vector<ld>> matrixld;
typedef vector<ll> onevec;
typedef vector<ld> onevecld;
typedef set<ll> lset;

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
template <typename T> ll llsize(const T &container) {
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
/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/
ll my_bin(ll ok, ll ng, function<bool(ll)> condition) {
  while (abs(ok - ng) > 1) {
    ll mid = (ok + ng) / 2;
    if (condition(mid)) {
      ok = mid;
    } else {
      ng = mid;
    }
  }
  return ok;
}

int main() {

  ll n, m;
  cin >> n >> m;
  onevec p(n + 1);
  p[0] = 0;
  rep(i, 1, n + 1) cin >> p[i];
  onevec points;
  rep(i, 0, n + 1) rep(j, i, n + 1) { points.push_back(p[i] + p[j]); }
  sort(all(points));
  ll res = 0;
  rep(i, 0, llsize(points)) {
    ll target = m - points[i];
    auto condition = [&](ll mid) { return points[mid] > target; };

    ll idx = my_bin(llsize(points), -1, condition);
    if (idx > 0) {
      chmax(res, (points[i] + points[idx - 1]));
    }
  }
  cout << res << endl;

  return 0;
}