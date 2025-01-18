#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>

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
    ll x;
    cin >> x;
    ll div =1;
    while (x !=1){
        x/=div;
        div++;
    }
    cout << div-1 << endl;
    return 0;
}