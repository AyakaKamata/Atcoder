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
long long calculateItems(long long M, const vector<long long>& P) {
    long long totalItems = 0;
    for (long long p : P) {
        // 商品の購入可能な最大個数を二分探索
        long long left = 0, right = 1e9; // 商品の購入数の範囲
        while (left <= right) {
            long long mid = (left + right) / 2;
            if (mid * mid * p <= M) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        totalItems += right; // rightが最大の購入可能個数
    }
    return totalItems;
}

int main() {
    long long N, M;
    cin >> N >> M;
    vector<long long> P(N);
    for (long long i = 0; i < N; i++) {
        cin >> P[i];
    }

    // 二分探索で合計購入数を求める
    long long low = 0, high = M, answer = 0;
    while (low <= high) {
        long long mid = (low + high) / 2;
        long long totalCost = 0;

        for (long long p : P) {
            // 各商品について、購入可能な最大個数を計算
            long long k = sqrt(mid / p); // kを一旦計算
            if (k * k * p > mid) k--;   // 調整
            totalCost += k;
        }

        if (totalCost <= M) {
            answer = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << answer << endl;

    return 0;
}
