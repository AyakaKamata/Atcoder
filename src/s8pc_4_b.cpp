#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
#define fore(i, a) for (auto &i : a)
#define all(x) (x).begin(), (x).end()
#pragma GCC optimize("-O3")

using namespace std;
using ll = long long;
using i128 = __int128_t;
using pint = pair<int, int>;
using matrix = vector<vector<int>>;
using onevec = vector<int>;
using iset = set<int>;

const int INFI = INT_MAX / 2;
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
template <typename T> int isize(const T &container) {
  return static_cast<int>(container.size());
}
template <typename T> bool ifbit(T number, int bit) {
  return (number & (1 << bit)) != 0;
}
// Function to count the number of set bits in an integer
int bits_count(int v) { return __builtin_popcount(v); }
/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/

int main() {
  int n, k;
  cin >> n >> k;
  onevec a(n);
  rep(i, 0, n) cin >> a[i];
  ll ans = INFL;
  rep(i, 0, 1 << n) {
    ll tmp = 0;
    if (bits_count(i) == k) {
      int max_v = 0;
      rep(j, 0, n) {
        if (ifbit(i, j)&& max_v>=a[j]) {
          tmp += max_v+1-a[j];
          max_v++;

        }
        chmax(max_v,a[j]);
      }
    chmin(ans, tmp);

    }
  }
  cout << ans << endl;
  return 0;
}