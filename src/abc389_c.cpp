#include <algorithm>
#include <cmath>
#include <deque>
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
  int q;
  cin >> q;
  deque<pair<ll, ll>> snake; // pair<ヘビの長さ, ヘビの頭の位置>
  ll offset = 0;             // ヘビの頭の位置のオフセット
  int flag=0;
  for (int i = 0; i < q; i++) {
    int j;
    cin >> j;
    if (j == 1) {
      ll l;
      cin >> l;
      ll head_position =
          (snake.empty() ? 0 : snake.back().second + snake.back().first);
      snake.push_back({l, head_position});
    } else if (j == 2) {
      if (!snake.empty()) {
        offset += snake.front().first;
        snake.pop_front();
      }
    } else if (j == 3) {
      int k;
      cin >> k;
      cout << snake[k - 1].second - offset << endl;
      flag=1;
    }
  }
  if(flag==0){
    cout << endl;
  }
  return 0;
}