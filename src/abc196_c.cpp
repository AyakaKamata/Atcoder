#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using ll = long long;

using namespace std;

int main() {
  ll n;
  cin >> n;
  ll sum = 0;
  for (ll i = 1; i * i <= n; ++i) {
    string s = to_string(i) + to_string(i);
    if (stoll(s) <= n) {
      ++sum;
    }
  }
  cout << sum << endl;
  return 0;
}
