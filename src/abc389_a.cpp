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

int main() {
  string S;
  cin >> S;
  cout << (S[0] - '0') * (S[2] - '0') << endl;
  return 0;
}