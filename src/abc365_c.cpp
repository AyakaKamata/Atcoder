#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    long long N, M;
    cin >> N >> M;
    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    long long total_cost = accumulate(A.begin(), A.end(), 0LL);
    if (total_cost <= M) {
        cout << "infinite" << endl;
        return 0;
    }

    long long left = 0, right = *max_element(A.begin(), A.end());
    while (left < right) {
        long long mid = (left + right + 1) / 2;
        long long sum = 0;
        for (long long cost : A) {
            sum += min(mid, cost);
            if (sum > M) break;
        }
        if (sum <= M) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    cout << left << endl;
    return 0;
}
