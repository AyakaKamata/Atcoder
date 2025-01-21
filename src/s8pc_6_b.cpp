#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define rrep(i, a, b) for (int_least16_t i = a; i >= b; i--)
#define fore(i, a) for (auto &i : a)
#define all(x) (x).begin(), (x).end()
#pragma GCC optimize("-O3")

using namespace std;
using ll = long long;
using i128 = __int128_t;

const int INFI = INT_MAX / 2;
const ll INFL = 1LL << 60;
template <class T> inline bool chmin(T &a, T b) {
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
/*--------------------------------------------------------
                         \0w0/
                        OwOkaomoji
                     ｡˚ (¦3ꇤ )3 ⋆｡˚✩
----------------------------------------------------------*/

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  vector<int> b(n);
  vector<int> dist(n, 0);
  rep(i, 0, n - 1) { cin >> a[i] >> b[i]; }
  sort(all(a));
  sort(all(b));
  int med = n / 2 - 1;
  if(n%2==1){med+=1;}
  int start = a[med];
  int end = b[med];
  ll total_distance = 0;
  rep(i, 0, n-1) {
    total_distance += abs(start - a[i]) + abs(a[i] - b[i]) + abs(b[i] - end);
  }

  cout << total_distance << endl;
  return 0;
}