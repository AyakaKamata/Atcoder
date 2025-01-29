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
typedef set<ll> iset;

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

  ll n;
  cin >> n;

  vector<ll> A(n);
  fore(a, A) cin >> a;
  sort(all(A));
  vector<ll> B(n);
  fore(a, B) cin >> a;
  sort(all(B));
  vector<ll> C(n);
  fore(a, C) cin >> a;
  sort(all(C));
  ll sum = 0;
  rep(i, 0, n) {
    ll x = B[i];

    ll idx = lower_bound(all(A), x) - A.begin();
    ll idx_ = upper_bound(all(C), x) - C.begin();
    sum += idx * (n - idx_);
  }
  cout << sum << endl;
  return 0;
}