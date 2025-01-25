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
int bits_count(int v) { return __builtin_popcount(v); }

/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/

int main() {
  int h, w;
  cin >> h >> w;
  vector<vector<char>> s(h, vector<char>(w));

  int min_h = INFI;
  int max_h = 0;
  int min_w = INFI;
  int max_w = 0;

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      cin >> s[i][j];
      if (s[i][j] == '#') {
        min_h = min(min_h, i);
        min_w = min(min_w, j);
        max_h = max(max_h, i);
        max_w = max(max_w, j);
      }
    }
  }
  for (int i = min_h; i <= max_h; ++i) {
    for (int j = min_w; j <= max_w; ++j) {
      if (s[i][j] == '.') {
        cout << "No" << endl;
        return 0;
      }
    }
  }

  cout << "Yes" << endl;
  return 0;
}