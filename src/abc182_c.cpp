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

int main() {
  ll n;
  cin >> n;
  int sum_n = 0;
  vector<int> n_digit(3, 0);
  ll temp = n;
  int log_n = 0;
  while (temp > 0) {
    sum_n += temp % 10;
    n_digit[temp % 10 % 3]++;
    temp /= 10;
    log_n++;
  }
  if (sum_n % 3 == 0) {
    cout << 0 << endl;
  } else {
    int remain = sum_n % 3;
    if (n_digit[remain] != 0 && log_n != 1) {
      cout << 1 << endl;
    } else if (n_digit[3 - remain] >= 2 && log_n > 2) {
      cout << 2 << endl;
    } else {
      cout << -1 << endl;
    }
  }
  return 0;
}