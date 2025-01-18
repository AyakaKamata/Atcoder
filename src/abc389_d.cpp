#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>


using namespace std;
using ll = long long;

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

int main() {
  double R;
  cin >> R;
  int count = 0;
  int n = floor(2*R/sqrt(2));
  if (n % 2 == 0) {
    --n;
  }
  // cout << n << endl;
  for (int i = -n/2; i <= n/2; ++i) {
    for (int j = n/2+1; j <= R; ++j) {
      if (sqrt((i + 0.5) * (i + 0.5) + (j + 0.5) * (j + 0.5)) <= R &&
          sqrt((i + 0.5) * (i + 0.5) + (j - 0.5) * (j - 0.5)) <= R &&
          sqrt((i - 0.5) * (i - 0.5) + (j + 0.5) * (j + 0.5)) <= R &&
          sqrt((i - 0.5) * (i - 0.5) + (j - 0.5) * (j - 0.5)) <= R) {
        ++count;
      }
    }
  }


  cout << count*4+n*n << endl;
  return 0;
}