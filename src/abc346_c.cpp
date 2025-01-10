#include <iostream>
#include <vector>
#include <set>
#include <numeric>
using namespace std;

int main() {
  long long n, k;
  cin >> n >> k;
  long long res = k * (k + 1) / 2;
  set<long long> set_A;
  for (long long i = 0; i < n; i++) {
    long long a;
    cin >> a;
    if (a <= k) {
      set_A.insert(a);
    }
  }
  res -= accumulate(set_A.begin(), set_A.end(), 0LL);
  cout << res << '\n';
}
