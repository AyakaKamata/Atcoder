#include <algorithm>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using i128 = __int128_t;

const ll INF = 1LL << 60;
template <class T> inline bool chmin(T &a, T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
template <class T> inline bool chmax(T &a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}
vector<long long> calc_divisors(long long N) {
 vector<long long> res;

 for (long long i = 1; i * i <= N; ++i) {
  if (N % i != 0) continue;

  res.push_back(i);

  if (N / i != i) res.push_back(N / i);
 }

 sort(res.begin(), res.end());
 return res;
}


int main() {
  int n;
  cin >> n;
  int sum = 0;


  for (int i = 105; i <= n; i += 2) {
    auto res = calc_divisors(i);
    if (res.size() == 8) {
      sum++;
    }
  }
  cout << sum << "\n";
  return 0;
}