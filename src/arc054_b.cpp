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

ld my_tri(ld ok, ld ng, function<ld(ld)> f) {
  while (abs(ok - ng) > 1e-11) {
    ld mid_l = (ok + ng * 2) / 3;
    ld mid_r = (ok * 2 + ng) / 3;
    if (f(mid_l) > f(mid_r)) {
      ng = mid_l;
    } else {
      ok = mid_r;
    }
  }
  return ok;
}

int main() {

  ld p;
  cin >> p;

  auto f = [&](ld mid) { return mid + p / pow(2, mid / 1.5); };

  ld idx = my_tri(INFL, 0, f);
  print(f(idx), 10);
  return 0;
}
